//**************************************************************
// 
// utility.cpp
// Author  : katsuki mizuki
// Author  : Hamada Ryuuga
// Author  : Yuda Kaito
// 
//**************************************************************

//==============================================================
// include
//==============================================================
#include "utility.h"
#include "camera.h"
#include "task_group.h"
#include "application.h"

//--------------------------------------------------------------
// 角度の正規化
//--------------------------------------------------------------
float NormalizeAngle(float& pAngle)
{
	if (pAngle >= D3DX_PI)
	{// 3.14より大きい
		pAngle -= D3DX_PI * 2.0f;
	}
	else if (pAngle <= -D3DX_PI)
	{// -3.14より小さい
		pAngle += D3DX_PI * 2.0f;
	}

	return pAngle;
}

//--------------------------------------------------------------
// ホーミング
//--------------------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// 速さより長さが小さい時
		*pPosOut = posDest;
		return true;
	}
	else
	{// 速さより長さが大きい時
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------------------
// 小数点のランダム
//--------------------------------------------------------------
float FloatRandom(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------------------
// 整数のランダム
//--------------------------------------------------------------
int IntRandom(int nMax, int nMin)
{
	return (int)((rand() / (float)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------------------
// 角度と現在位置、離す距離で、外周にいる位置を算出
//--------------------------------------------------------------
D3DXVECTOR3 CalculatePerimeterPos(const D3DXVECTOR3 & center, const D3DXVECTOR3 & rot, const D3DXVECTOR3 & range)
{
	// 計算用マトリックス
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot, mtxTrans;

	D3DXMatrixIdentity(&mtxWorld);	// 行列初期化関数

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);		// 行列回転関数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);					// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, center.x, center.y, center.z);	// 行列移動関数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);	// 行列掛け算関数

	// D3DXVECTOR3に反映
	D3DXVECTOR3 targetPos = range;
	D3DXVec3TransformCoord(&targetPos, &targetPos, &mtxWorld);

	return targetPos;
}

//--------------------------------------------------------------
// 成功確率
//--------------------------------------------------------------
bool IsSuccessRate(float inRate)
{
	return ((rand() / (float)RAND_MAX)) < inRate;
}

int IntRateRandom(std::vector<float> inRate)
{
	float random = FloatRandom(0.0f, 1.0f);
	
	int size = inRate.size();
	float nowRate = 0.0f;
	for (int i = 0; i < size; i++)
	{
		nowRate = inRate[i];
		if (nowRate >= random)
		{
			return i;
		}
	}

	std::sort(inRate.begin(), inRate.end());
	return 0;
}

//--------------------------------------------------------------
// sinカーブの値が1.0f～0.0fで帰ってくる
//--------------------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------------------
// cosカーブの値が1.0f～0.0fで帰ってくる
//--------------------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------------------
// カーブの値が帰ってくる
//--------------------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}

//--------------------------------------------------------------
// スクリーン座標をワールド座標へのキャスト
//--------------------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,		// スクリーン座標
	D3DXVECTOR3 screenSize,								// スクリーンサイズ
	D3DXMATRIX* mtxView,								// ビューマトリックス
	D3DXMATRIX* mtxProjection)							// プロジェクションマトリックス
{
	// 変数宣言
	D3DXVECTOR3 ScreenPos;

	// 計算用マトリックスの宣言
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;

	// 各行列の逆行列を算出
	D3DXMatrixInverse(&InvView, NULL, mtxView);
	D3DXMatrixInverse(&InvPrj, NULL, mtxProjection);
	D3DXMatrixIdentity(&VP);
	VP._11 = screenSize.x * 0.5f; VP._22 = -screenSize.y * 0.5f;
	VP._41 = screenSize.x * 0.5f; VP._42 = screenSize.y * 0.5f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// ワールド座標へのキャスト
	D3DXMATRIX mtxWorld = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(&ScreenPos, screenPos, &mtxWorld);

	return ScreenPos;
}

//--------------------------------------------------------------
// スクリーン座標をワールド座標へのキャスト
//--------------------------------------------------------------
D3DXVECTOR3 ScreenCastWorld(const D3DXVECTOR3 &screenPos, D3DXVECTOR3 screenSize)
{
	D3DXVECTOR3 pos = screenPos;

	CCamera* camera = (CCamera*)CApplication::GetInstance()->GetTaskGroup()->SearchRoleTop(0, CTaskGroup::LEVEL_3D_1);
	D3DXVECTOR3 Camerapos = camera->GetPos();

	pos.y *= -1;

	pos -= (Camerapos - D3DXVECTOR3(screenSize.x * 0.5f, screenSize.y * 0.5f, 0.0f));

	return pos;
}

//=============================================================================
// ワールド座標へのキャスト処理
// Author : 唐﨑結斗
// 概要 : pos,rotの行列計算を行い、ローカル座標をワールド座標に変換する
//=============================================================================
D3DXVECTOR3 WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot)
{
	// 変数宣言
	D3DXMATRIX mtxWorldVtx; // ワールドマトリックス
	D3DXMATRIX mtxRot, mtxTrans; // 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&mtxWorldVtx);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, vtx.x, vtx.y, vtx.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans); // 行列掛け算関数

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, FormerRot.y, FormerRot.x, FormerRot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, FormerPos.x, FormerPos.y, FormerPos.z);
	D3DXMatrixMultiply(&mtxWorldVtx, &mtxWorldVtx, &mtxTrans); // 行列掛け算関数

	return D3DXVECTOR3(mtxWorldVtx._41, mtxWorldVtx._42, mtxWorldVtx._43);
}

//--------------------------------------------------------------
// マトリックスの計算
// Author : Hamada Ryuuga
//--------------------------------------------------------------
D3DXMATRIX * GiftMtx(D3DXMATRIX * pOut, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot)
{
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(pOut);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, inRot.y, inRot.x, inRot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, inPos.x, inPos.y, inPos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);

	return pOut;
}

//--------------------------------------------------------------
// 2Dベクトルの外積
// Author: Yuda Kaito
//--------------------------------------------------------------
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->z - v1->z * v2->x;
}

//--------------------------------------------------------------
// 2Dベクトルの内積
// Author: hamada ryuuga
//--------------------------------------------------------------
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->x + v1->z * v2->z;
}

//--------------------------------------------------------------
// クオータニオンをラジアンに変換する(挙動不安定)
// Author : Yuda Kaito
//--------------------------------------------------------------
D3DXVECTOR3 ConvertQuaternionfromRadian(const D3DXQUATERNION& inQuaternion)
{
	D3DXVECTOR3 rot;
	float z1 = 2 * (inQuaternion.x * inQuaternion.y + inQuaternion.z * inQuaternion.w);
	float z2 = inQuaternion.x * inQuaternion.x - inQuaternion.y * inQuaternion.y - inQuaternion.z * inQuaternion.z - inQuaternion.w * inQuaternion.w;
	float z3 = z1 / z2;
	rot.z = atanf(z3);

	float y1 = 2 * (inQuaternion.x * inQuaternion.z - inQuaternion.y * inQuaternion.w);
	rot.y = atanf(y1);

	float x1 = 2 * (inQuaternion.x * inQuaternion.w + inQuaternion.y * inQuaternion.z);
	float x2 = inQuaternion.x * inQuaternion.x + inQuaternion.y * inQuaternion.y - inQuaternion.z * inQuaternion.z - inQuaternion.w * inQuaternion.w;
	float x3 = x1 / x2;
	rot.x = atanf(x3);

	return rot;
}

//--------------------------------------------------------------
// 行列の逆行列を変換
// Author : Yuda Kaito
//--------------------------------------------------------------
const D3DXMATRIX InverseMatrixConversion(const D3DXMATRIX & inMtx)
{
	D3DXMATRIX mtx;

	mtx._11 = inMtx._11;
	mtx._12 = inMtx._21;
	mtx._13 = inMtx._31;
	mtx._21 = inMtx._12;
	mtx._22 = inMtx._22;
	mtx._23 = inMtx._32;
	mtx._31 = inMtx._13;
	mtx._32 = inMtx._23;
	mtx._33 = inMtx._33;

	return mtx;
}

bool IsSjisLeadByte(int c)
{
	return (((c & 0xffu) ^ 0x20u) - 0xa1) < 94u / 2;
}

//--------------------------------------------------------------
// イージング関数
// Author : Yuda Kaito
//--------------------------------------------------------------
namespace ease
{

// 正弦で算出
float InSine(float x) { return 1 - cosf((x * D3DX_PI) * 0.5f); }
float OutSine(float x) { return sinf((x * D3DX_PI) * 0.5f); }
float InOutSine(float x) { return -(cosf(D3DX_PI * x) - 1.0f) * 0.5f; }

// 2の累乗で算出
float InQuad(float x) { return x * x; }
float OutQuad(float x) { return 1.0f - (1.0f - x) * (1 - x); }
float InOutQuad(float x) { return x < 0.5f ? 2.0f * x * x : 1.0f - powf(-2.0f * x + 2.0f, 2) * 0.5f; }

// 3の累乗で算出
float InCubic(float x) { return x * x * x; }
float OutCubic(float x) { return 1 - powf(1.0f - x, 3.0f); }
float InOutCubic(float x) { return x < 0.5f ? 4.0f * x * x * x : 1.0f - powf(-2.0f * x + 2.0f, 3) * 0.5f; }

// 4の累乗で算出
float InQuart(float x) { return x * x * x * x; }
//float OutQuart(float x);
//float InOutQuart(float x);

// 5の累乗で算出
float InQuint(float x) { return x * x * x * x * x; }
//float OutQuint(float x);
//float InOutQuint(float x);

// 指数関数で算出
float InExpo(float x) { return x == 0.0f ? 0 : powf(2.0f, 10.0f * x - 10.0f); }
//float OutExpo(float x);
//float InOutExpo(float x);

float InCirc(float x) { return 1.0f - sqrtf(1.0f - powf(x, 2)); }
//float OutCirc(float x);
//float InOutCirc(float x);

float InBack(float x, float s) { return (s + 1.0f) * x * x * x - s * x * x; }
//float OutBack(float x);
//float InOutBack(float x);

float InElastic(float x, float c) { return x == 0 ? 0 : x == 1 ? 1 : -powf(2.f, 10.f * x - 10.f) * sinf((x * 10.f - 10.75f) * c); }
float OutElastic(float x, float c) { return x == 0 ? 0 : x == 1 ? 1 : powf(2.f, -10.f * x) * sinf((x * 10.f - 0.75f) * c) + 1.f; }
float InOutElastic(float x, float c) { return x == 0 ? 0 : x == 1 ? 1 : x < 0.5f ? -(powf(2.f, 20.f * x - 10.f) * sinf((x * 20.f - 11.125f) * c)) * 0.5f : (powf(2.f, -20.f * x + 10.f) * sinf((x * 20.f - 11.125f) * c)) * 0.5f + 1.f; }

float InBounce(float x, float n, float d) { return 1.0f - OutBounce(1 - x, n, d); }
float OutBounce(float x, float n, float d)
{
	if (x < 1.0f / d)
	{
		return n * x * x;
	}
	else if (x < 2.0f / d)
	{
		return n * (x -= 1.5f / d) * x + 0.75f;
	}
	else if (x < 2.5f / d)
	{
		return n * (x -= 2.25f / d) * x + 0.9375f;
	}
	else
	{
		return n * (x -= 2.625f / d) * x + 0.984375f;
	}
}
float InOutBounce(float x, float n, float d) { return x < 0.5f ? (1.0f - OutBounce(1.0f - 2.0f * x, n, d)) * 0.5f : (1.0f + OutBounce(2.0f * x - 1.0f, n, d)) * 0.5f; }

}