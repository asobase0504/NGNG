//**************************************************************
//
// 円柱の当たり判定
// Author : 梶田大夢
// Author : Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "collision_cylinder.h"
#include "collision_sphere.h"
#include "collision_box.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "utility.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CCollisionCylinder::CCollisionCylinder() : 
	m_extrusion(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_length(0.0f),
	m_height(0.0f)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CCollisionCylinder::~CCollisionCylinder()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CCollisionCylinder::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CCollisionCylinder::Uninit()
{
}

//--------------------------------------------------------------
// 円柱と円柱
//--------------------------------------------------------------
bool CCollisionCylinder::ToCylinder(CCollisionCylinder * inCyinder)
{
	D3DXVECTOR3 pos = GetPos();
	float radius = GetLength();

	D3DXVECTOR3 pos2 = inCyinder->GetPos();
	float radius2 = inCyinder->GetLength();

	float pos3 = pos.x - pos2.x;
	float pos4 = pos.z - pos2.z;

	float radius3 = radius + radius2;

	if ((pos3 * pos3) + (pos4 * pos4) <= (radius3 * radius3))
	{
		return true;
	}

	return false;
}

//--------------------------------------------------------------
// 円柱と箱
// 引数：CCollisionBox* inBox (CCollisionBoxのポインタ), bool isExtrusion (押出をするかどうか)
//--------------------------------------------------------------
bool CCollisionCylinder::ToBox(CCollisionBox* inBox, bool isExtrusion)
{
	bool isLanding = false;

	D3DXVECTOR3 boxPos = inBox->GetPos();
	D3DXVECTOR3 boxSize = inBox->GetSize();
	D3DXMATRIX boxMtxWorld = inBox->GetMtxWorld();

	D3DXVECTOR3 cylinderPos = GetPos();
	D3DXVECTOR3 cylinderPosOld = GetPosOld();
	float radius = GetLength();

	float left = boxPos.x - boxSize.x * 0.5f;	// x1
	float right = boxPos.x + boxSize.x * 0.5f;	// x2
	float back = boxPos.z + boxSize.z * 0.5f;	// z1
	float front = boxPos.z - boxSize.z * 0.5f;	// z2

	// ４つの頂点
	D3DXVECTOR3 pos[4];
	pos[0] = D3DXVECTOR3(left - radius, 0.0f, back + radius);
	pos[1] = D3DXVECTOR3(right + radius, 0.0f, back + radius);
	pos[2] = D3DXVECTOR3(right + radius, 0.0f, front - radius);
	pos[3] = D3DXVECTOR3(left - radius, 0.0f, front - radius);

	D3DXVECTOR3 worldPos[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVec3TransformCoord(&worldPos[nCnt], &pos[nCnt], &boxMtxWorld);
	}

	D3DXVECTOR3 vecLine[4];
	vecLine[0] = worldPos[1] - worldPos[0];
	vecLine[1] = worldPos[2] - worldPos[1];
	vecLine[2] = worldPos[3] - worldPos[2];
	vecLine[3] = worldPos[0] - worldPos[3];

	D3DXVECTOR3 vec[4];
	vec[0] = cylinderPos - worldPos[0];
	vec[1] = cylinderPos - worldPos[1];
	vec[2] = cylinderPos - worldPos[2];
	vec[3] = cylinderPos - worldPos[3];

	float InOut[4];
	InOut[0] = Vec2Cross(&vecLine[0], &vec[0]);
	InOut[1] = Vec2Cross(&vecLine[1], &vec[1]);
	InOut[2] = Vec2Cross(&vecLine[2], &vec[2]);
	InOut[3] = Vec2Cross(&vecLine[3], &vec[3]);

	if ((InOut[0] < 0.0f && InOut[1] < 0.0f && InOut[2] < 0.0f && InOut[3] < 0.0f) ||
		InOut[0] > 0.0f && InOut[1] > 0.0f && InOut[2] > 0.0f && InOut[3] > 0.0f)
	{
		// XZの押出
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{// どの方向から来たか判定
			D3DXVECTOR3 vecPosOld = cylinderPosOld - worldPos[nCnt];
			float leftPosOld = Vec2Cross(&vecLine[nCnt], &vecPosOld);

			if (leftPosOld <= 0.0f)
			{// 方向が分かった時
				isLanding = true;

				// posOldから始点までの距離（V）
				D3DXVECTOR3 V = worldPos[nCnt] - cylinderPosOld;
				// プレイヤーのMOVE（V1）
				D3DXVECTOR3 vecMove = cylinderPos - cylinderPosOld;

				float t1 = Vec2Cross(&V, &vecLine[nCnt]) / Vec2Cross(&vecMove, &vecLine[nCnt]);
				float t2 = Vec2Cross(&V, &vecMove) / Vec2Cross(&vecMove, &vecLine[nCnt]);

				const float eps = 0.00001f;
				if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1)
				{// 交差していない
					continue;
				}
				else
				{// 押し出し用法線の格納用の箱
					//D3DXVECTOR3 nor;
					//// 上方向のベクトル
					//D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);
					//// 正規化
					//D3DXVec3Normalize(&vecLine[nCnt], &vecLine[nCnt]);
					//// メッシュの法線を求める
					//D3DXVec3Cross(&nor, &vecLine[nCnt], &vecUp);
					//// 大きさを１にする
					//D3DXVec3Normalize(&nor, &nor);

					//// 逆方向
					//D3DXVECTOR3 reverseVecMove = cylinderPosOld - cylinderPos;
					//// (a)
					//float difMove = Vec2Dot(&reverseVecMove, &nor);

					//// 押し返し
					//m_extrusion.x = (cylinderPosOld.x + vecMove.x * t1) + (nor.x * 0.1f) + (vecMove.x + difMove * nor.x);
					//m_extrusion.z = (cylinderPosOld.z + vecMove.z * t1) + (nor.z * 0.1f) + (vecMove.z + difMove * nor.z);

					break;
				}
			}
		}
	}
	//D3DXVECTOR3 v2(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 v(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 startPos(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 endPos(0.0f, 0.0f, 0.0f);

	//float triangleBase1 = left - cylinderPos.x;
	//float triangleBase2 = right - cylinderPos.x;
	//float triangleHeight1 = back - cylinderPos.z;
	//float triangleHeight2 = front - cylinderPos.z;

	//// 単位ベクトル
	//D3DXVECTOR3 unitVec(0.0f, 0.0f, 0.0f);

	//if ((cylinderPos.x > left) && (cylinderPos.x < right) &&
	//	(cylinderPos.z > front - radius) && (cylinderPos.z < back + radius))
	//{// 手前　奥
	//	if (boxPos.z < cylinderPos.z)
	//	{// 奥
	//		startPos = pos[0];
	//		endPos = pos[1];
	//		v2 = endPos - startPos;
	//		v = startPos - cylinderPosOld;
	//	}
	//	else
	//	{// 手前
	//		startPos = pos[2];
	//		endPos = pos[3];
	//		v2 = endPos - startPos;
	//		v = startPos - cylinderPosOld;
	//	}

	//	isLanding = true;
	//}
	//else if ((cylinderPos.x > left - radius) && (cylinderPos.x < right + radius) &&
	//	(cylinderPos.z > front) && (cylinderPos.z < back))
	//{// 左右
	//	if (boxPos.x < cylinderPos.x)
	//	{// 右
	//		startPos = pos[1];
	//		endPos = pos[2];
	//		v2 = endPos - startPos;
	//		v = startPos - cylinderPosOld;
	//	}
	//	else
	//	{// 左
	//		startPos = pos[3];
	//		endPos = pos[0];
	//		v2 = endPos - startPos;
	//		v = startPos - cylinderPosOld;
	//	}

	//	isLanding = true;
	//}
	//else if ((triangleBase1 * triangleBase1) + (triangleHeight1 * triangleHeight1) < radius * radius)
	//{// 左上
	//	unitVec = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
	//	D3DXVec3Normalize(&unitVec, &unitVec);
	//	m_extrusion = pos[0] + unitVec * radius;
	//	return true;
	//}
	//else if ((triangleBase2 * triangleBase2) + (triangleHeight1 * triangleHeight1) < radius * radius)
	//{// 右上
	//	unitVec = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	//	D3DXVec3Normalize(&unitVec, &unitVec);
	//	m_extrusion = pos[1] + unitVec * radius;
	//	return true;
	//}
	//else if ((triangleBase2 * triangleBase2) + (triangleHeight2 * triangleHeight2) < radius * radius)
	//{// 右下
	//	unitVec = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
	//	D3DXVec3Normalize(&unitVec, &unitVec);
	//	m_extrusion = pos[2] + unitVec * radius;
	//	return true;
	//}
	//else if ((triangleBase1 * triangleBase1) + (triangleHeight2 * triangleHeight2) < radius * radius)
	//{// 左下
	//	unitVec = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
	//	D3DXVec3Normalize(&unitVec, &unitVec);
	//	m_extrusion = pos[3] + unitVec * radius;
	//	return true;
	//}
	//else
	//{
	//	return isLanding;
	//}

	//if (isExtrusion && isLanding)
	//{// http://marupeke296.com/COL_2D_No10_SegmentAndSegment.html
	//	D3DXVECTOR3 v1 = cylinderPos - cylinderPosOld;
	//	float t2 = Vec2Cross(&v, &v1) / Vec2Cross(&v1, &v2);

	//	// intersection　交点
	//	D3DXVECTOR3 intersection = startPos + v2 * t2;

	//	// 垂直なベクトルをつくる
	//	D3DXVECTOR3 vertical(-v2.z, 0.0f, v2.x);
	//	// 大きさを正規化
	//	D3DXVec3Normalize(&vertical, &vertical);
	//	// 押出の位置
	//	m_extrusion = intersection + vertical * radius;
	//}

	return isLanding;
}

//--------------------------------------------------------------
// 円柱と球
//--------------------------------------------------------------
bool CCollisionCylinder::ToSphere(CCollisionSphere * inSphere)
{
	// 円柱の半径と球の半径を足した距離
	float addLength = m_length + inSphere->GetLength();
	float addHeight = m_height + inSphere->GetLength();

	// 円柱の中心値から球の中心値までの距離
	D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f,0.0f,0.0f);
	differenceX.x = GetPos().x - inSphere->GetPos().x;

	D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceY.y = GetPos().y - inSphere->GetPos().y;

	D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceZ.z = GetPos().z - inSphere->GetPos().z;

	//x,y,zの絶対値の計算
	float differenceLengthX = D3DXVec3Length(&differenceX);
	float differenceLengthY = D3DXVec3Length(&differenceY);
	float differenceLengthZ = D3DXVec3Length(&differenceZ);

	if (differenceLengthX <= addLength
		&& differenceLengthY < addHeight
		&& differenceLengthZ <= addLength)
	{
		if (GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength()
			&& GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength()
			&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y - inSphere->GetLength()
			&& GetPos().y - (m_height * 0.5f) < inSphere->GetPos().y + inSphere->GetLength())
		{
			if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength())
			{// 左の当たり判定
				return true;
			}

			if (GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength())
			{// 右の当たり判定
 				return true;
			}
		}

		if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
			&& GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength()
			&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y - inSphere->GetLength()
			&& GetPos().y - (m_height * 0.5f) < inSphere->GetPos().y + inSphere->GetLength())
		{
			if (GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
			{// 前の当たり判定
				return true;
			}

			if (GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength())
			{// 奥の当たり判定
				return true;
			}
		}

		if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
			&& GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength()
			&& GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength()
			&& GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength())
		{
			if (GetPos().y + (m_height * 0.5f) < inSphere->GetPos().y - inSphere->GetLength()
				)
			{// 上の当たり判定
				return true;
			}

			if (GetPos().y - (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength())
			{// 下の当たり判定
				return true;
			}
		}
	}

	return false;
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CCollisionCylinder * CCollisionCylinder::Create(const D3DXVECTOR3 & pos, const float length, const float height)
{
	CCollisionCylinder* collision = new CCollisionCylinder;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_length = length;
	collision->m_height = height;

	return collision;
}
