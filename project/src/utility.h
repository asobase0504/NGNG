//**************************************************************
//
// utility.h
// Author : katsuki mizuki
//
//**************************************************************
#ifndef _UTILITY_H_	// このマクロ定義がされてなかったら
#define _UTILITY_H_	// ２重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================

//--------------------------------------------------------------
// 出力にテキストを出力する。
//--------------------------------------------------------------
#ifdef _DEBUG
#define DEBUG_PRINT(...) _RPT_BASE(_CRT_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

//==============================================================
// プロトタイプ宣言
//==============================================================
//--------------------------------------------------------------
// 角度の正規化
// 引数  : pAngle / 角度
//--------------------------------------------------------------
float NormalizeAngle(float& pAngle);

//--------------------------------------------------------------
// ホーミング
// 引数1  : D3DXVECTOR3 *pPosOut / 位置
// 引数2  : D3DXVECTOR3 &posNow / 現在の位置
// 引数3  : D3DXVECTOR3 &posDest / 目的の位置
// 引数4  : float fSpeed / 速さ
// 返値  : bool / 目的の位置に着いたかどうか
//--------------------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed);

//--------------------------------------------------------------
// 角度と現在位置、離す距離で、外周にいる位置を算出
// 引数1  : D3DXVECTOR3 *center	/ 中心位置
// 引数2  : D3DXVECTOR3 &rot	/ 現在の向き
// 引数3  : D3DXVECTOR3 &range	/ 離す距離(rotが0の時の位置)
// 返値  : D3DXVECTOR3 / 外周位置
//--------------------------------------------------------------
D3DXVECTOR3 CalculatePerimeterPos(const D3DXVECTOR3 &center, const D3DXVECTOR3 &rot, const D3DXVECTOR3 & range);

//--------------------------------------------------------------
// 成功確率を渡して成功か否か判断
// 引数  : float inRate / 成功確率
// 返値  : bool / 成功
//--------------------------------------------------------------
bool IsSuccessRate(float inRate);

//--------------------------------------------------------------
// 小数点のランダム
// 引数1  : float fMax / 最大値
// 引数2  : float fMin / 最小値
// 返値  : float / ランダム値
//--------------------------------------------------------------
float FloatRandom(float fMax, float fMin);

//--------------------------------------------------------------
// 整数のランダム
// 引数1  : int nMax / 最大値
// 引数2  : int nMin / 最小値
// 返値  : int / ランダム値
//--------------------------------------------------------------
int IntRandom(int nMax, int nMin);

//--------------------------------------------------------------
// 成功確率を渡して成功か否か判断
// 引数  : float inRate / 成功確率
// 返値  : bool / 成功
//--------------------------------------------------------------
bool IsSuccessRate(float inRate);

//--------------------------------------------------------------
// 確率の違うランダム
// 引数1  : std::vector<float> / size = 個数 / value = 確率
// 返値  : int / ランダム値
//--------------------------------------------------------------
int IntRateRandom(std::vector<float>);

//--------------------------------------------------------------
// sinカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int nTime / タイム
// 引数2  : float fCycle / 周期
// 返値  : float / 1.0f〜0.0fのsinカーブ
//--------------------------------------------------------------
float SinCurve(int nTime, float fCycle);

//--------------------------------------------------------------
// cosカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int nTime / タイム
// 引数2  : float fCycle / 周期
// 返値  : float / 1.0f〜0.0fのcosカーブ
//--------------------------------------------------------------
float CosCurve(int nTime, float fCycle);

//--------------------------------------------------------------
// カーブの値が帰ってくる
// 引数1  : float fCurve / カーブ
// 引数2  : float fMax / 最大値
// 引数3  : float fMin / 最小値
// 返値  : float / カーブ
//--------------------------------------------------------------
float Curve(float fCurve, float fMax, float fMin);

//--------------------------------------------------------------
// WorldCastScreen
// 引数1  : D3DXVECTOR3 *screenPos // スクリーン座標
// 引数2  : D3DXVECTOR3 screenSize // スクリーンサイズ
// 引数3  : D3DXMATRIX* mtxView // ビューマトリックス
// 引数4  : D3DXMATRIX* mtxProjection // プロジェクションマトリックス
// 返値   : D3DXVECTOR3 2Dを3D
//--------------------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,			// スクリーン座標
	D3DXVECTOR3 screenSize,									// スクリーンサイズ
	D3DXMATRIX* mtxView,									// ビューマトリックス
	D3DXMATRIX* mtxProjection);								// プロジェクションマトリックス

//--------------------------------------------------------------
// ScreenCastWorld
// 引数1  : D3DXVECTOR3  *screenPos // スクリーン座標
// 引数2  : D3DXVECTOR3 screenSize
// 返値  : D3DXVECTOR3 / 3Dを2D
//--------------------------------------------------------------
D3DXVECTOR3 ScreenCastWorld(const D3DXVECTOR3 &screenPos,			// スクリーン座標
	D3DXVECTOR3 screenSize);

//=============================================================================
// ワールド座標へのキャスト処理
// Author : 唐�ｱ結斗
// 概要 : pos,rotの行列計算を行い、ローカル座標をワールド座標に変換する
//=============================================================================
D3DXVECTOR3 WorldCastVtx(D3DXVECTOR3 vtx, D3DXVECTOR3 FormerPos, D3DXVECTOR3 FormerRot);

//--------------------------------------------------------------
// ScreenCastWorld
// Author : Hamada Ryuuga
// 引数1  : D3DXMATRIX  *pOut // スクリーン座標
// 引数2  : D3DXVECTOR3 inPos
// 引数3  : D3DXVECTOR3 inRot
// 返値  : D3DXMATRIX / 計算したマトリックス
//--------------------------------------------------------------
D3DXMATRIX *GiftMtx(D3DXMATRIX *pOut, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot);

// 算出系統
//--------------------------------------------------------------
// 2Dの外積
// 引数1  : D3DXVECTOR3  *v1 // 
// 引数2  : D3DXVECTOR3*  v2
// 返値  : float/ 外積
//--------------------------------------------------------------
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);

//--------------------------------------------------------------
// 2Dの内積
// 引数1  : D3DXVECTOR3  *v1 // 
// 引数2  : D3DXVECTOR3*  v2
// 返値  : float / 内積
//--------------------------------------------------------------
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);

D3DXVECTOR3 ConvertQuaternionfromRadian(const D3DXQUATERNION& inQuaternion);

const D3DXMATRIX InverseMatrixConversion(const D3DXMATRIX& inMtx);

//=============================================================================
//1バイト文字をシフトJISかどうか判定する関数
//=============================================================================
bool IsSjisLeadByte(int c);

//--------------------------------------------------------------
// Author : Hamada Ryuuga
// Author : Yuda Kaito
// 引数1  : float X		// 時間
// 返値  : float		// 計算結果
//--------------------------------------------------------------
namespace ease
{
// 正弦で算出
float InSine(float x);
float OutSine(float x);
float InOutSine(float x);

// 2の累乗で算出
float InQuad(float x);
float OutQuad(float x);
float InOutQuad(float x);

// 3の累乗で算出
float InCubic(float x);
float OutCubic(float x);
float InOutCubic(float x);

// 4の累乗で算出
float InQuart(float x);
//float OutQuart(float x);
//float InOutQuart(float x);

// 5の累乗で算出
float InQuint(float x);
//float OutQuint(float x);
//float InOutQuint(float x);

// 指数関数で算出
float InExpo(float x);
//float OutExpo(float x);
//float InOutExpo(float x);

float InCirc(float x);
//float OutCirc(float x);
//float InOutCirc(float x);

float InBack(float x, float s = 1.70158f);
//float OutBack(float x);
//float InOutBack(float x);

float InElastic(float x, float c = (2.f * D3DX_PI) / 3.f);
float OutElastic(float x, float c = (2.f * D3DX_PI) / 3.f);
float InOutElastic(float x, float c = (2.f * D3DX_PI) / 4.5f);

float OutBounce(float x, float n = 7.5625f, float d = 2.75f);
float InBounce(float x, float n = 7.5625f, float d = 2.75f);
float InOutBounce(float x, float n = 7.5625f, float d = 2.75f);
}

#endif // !_UTILITY_H_
