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
#include "collision_mesh.h"
#include "line.h"

#include "object_polygon3d.h"
#include "enemy_manager.h"
#include "player_manager.h"

#include "utility.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CCollisionCylinder::CCollisionCylinder() : 
	m_length(0.0f),
	m_height(0.0f)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CCollisionCylinder::~CCollisionCylinder()
{
	for (int i = 0; i < 9; i++)
	{
		m_line[i] = nullptr;
	}
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CCollisionCylinder::Init()
{
	for (int i = 0; i < 9; i++)
	{
		m_line[i] = CLine::Create();
		SetEndChildren(m_line[i]);
		m_line[i]->SetColor(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f));
		m_line[i]->SetPosTarget(&GetPosWorld());
		m_line[i]->SetRotTarget(&GetRot());
	}
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CCollisionCylinder::Update()
{
	CCollision::Update();

	D3DXVECTOR3 pos = GetPosWorld();
	D3DXVECTOR3 size = GetSize();
	D3DXVECTOR3 rot = GetRot();
}

//--------------------------------------------------------------
// 円柱と円柱
//--------------------------------------------------------------
bool CCollisionCylinder::ToCylinder(CCollisionCylinder * inCyinder)
{
	D3DXVECTOR3 pos = GetPosWorld();
	float radius = GetLength();

	D3DXVECTOR3 pos2 = inCyinder->GetPosWorld();
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

	D3DXVECTOR3 boxPos = inBox->GetPosWorld();
	D3DXVECTOR3 boxRot = inBox->GetRot();
	D3DXVECTOR3 boxSize = inBox->GetSize();
	D3DXMATRIX boxMtxWorld, mtxTrans, mtxRot;

	D3DXMatrixIdentity(&boxMtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, boxRot.y, boxRot.x, boxRot.z);
	D3DXMatrixMultiply(&boxMtxWorld, &boxMtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, boxPos.x, boxPos.y, boxPos.z);
	D3DXMatrixMultiply(&boxMtxWorld, &boxMtxWorld, &mtxTrans);

	D3DXVECTOR3 cylinderPos = GetPosWorld();
	D3DXVECTOR3 cylinderPosOld = GetPosOld();
	float radius = GetLength();

	float left = -boxSize.x;		// 左
	float right = boxSize.x;		// 右
	float top = boxSize.y;		// 上
	float bottum = -boxSize.y;	// 下
	float back = boxSize.z;		// 奥
	float front = -boxSize.z;	// 前

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

	// 押出位置
	D3DXVECTOR3 extrusion(0.0f, 0.0f, 0.0f);

	SetIsTop(false);
	SetIsUnder(false);

	if (InOut[0] < 0.0f && InOut[1] < 0.0f && InOut[2] < 0.0f && InOut[3] < 0.0f)
	{
		if (!isExtrusion)
		{// 押出をしない場合
			isLanding = true;
			return isLanding;
		}

		if (cylinderPosOld.y >= boxPos.y + boxSize.y && cylinderPos.y < boxPos.y + boxSize.y)
		{// 上
			extrusion.x = cylinderPos.x;
			extrusion.y = boxPos.y + boxSize.y;
			extrusion.z = cylinderPos.z;

			SetPosParent(extrusion);
			SetIsTop(true);
			isLanding = true;
		}

		if (cylinderPosOld.y + m_height <= boxPos.y  && cylinderPos.y + m_height > boxPos.y)
		{// 下
			extrusion.x = cylinderPos.x;
			extrusion.y = boxPos.y - m_height;
			extrusion.z = cylinderPos.z; 

			SetIsUnder(true);
			SetPosParent(extrusion);
			isLanding = true;
		}

		if (cylinderPos.y < boxPos.y + boxSize.y && cylinderPos.y + m_height > boxPos.y)
		{// XZの押出
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{// どの方向から来たか判定
				D3DXVECTOR3 vecPosOld = cylinderPosOld - worldPos[nCnt];
				float leftPosOld = Vec2Cross(&vecLine[nCnt], &vecPosOld);

				if (leftPosOld > 0.0f)
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
						D3DXVECTOR3 nor;
						// 上方向のベクトル
						D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);
						// 正規化
						D3DXVec3Normalize(&vecLine[nCnt], &vecLine[nCnt]);
						// 面の法線を求める
						D3DXVec3Cross(&nor, &vecLine[nCnt], &vecUp);
						// 大きさを１にする
						D3DXVec3Normalize(&nor, &nor);

						// 逆方向
						D3DXVECTOR3 reverseVecMove = cylinderPosOld - cylinderPos;
						// (a)
						float difMove = Vec2Dot(&reverseVecMove, &nor);

						// 押し返し
						extrusion.x = (cylinderPosOld.x + vecMove.x * t1) + (nor.x * 0.1f) + (vecMove.x + difMove * nor.x);
						extrusion.y = cylinderPos.y;
						extrusion.z = (cylinderPosOld.z + vecMove.z * t1) + (nor.z * 0.1f) + (vecMove.z + difMove * nor.z);

						SetPosParent(extrusion);

						break;
					}
				}
			}
		}
	}
	return isLanding;
}

//--------------------------------------------------------------
// 円柱と球
//--------------------------------------------------------------
bool CCollisionCylinder::ToSphere(CCollisionSphere * inSphere)
{
	float lengthSphere = inSphere->GetLength();
	D3DXVECTOR3 posWorldSphere = inSphere->GetPosWorld();

	// 円柱の半径と球の半径を足した距離
	float addLength = m_length + lengthSphere;
	float addHeight = m_height + lengthSphere;

	// 円柱の中心値から球の中心値までの距離
	D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f,0.0f,0.0f);
	differenceX.x = GetPosWorld().x - posWorldSphere.x;

	D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceY.y = GetPosWorld().y - posWorldSphere.y;

	D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceZ.z = GetPosWorld().z - posWorldSphere.z;

	//x,y,zの絶対値の計算
	float differenceLengthX = D3DXVec3Length(&differenceX);
	float differenceLengthY = D3DXVec3Length(&differenceY);
	float differenceLengthZ = D3DXVec3Length(&differenceZ);

	if (differenceLengthX <= addLength
		&& differenceLengthY < addHeight
		&& differenceLengthZ <= addLength)
	{
		if (GetPosWorld().z + (m_length * 0.5f) > posWorldSphere.z - lengthSphere
			&& GetPosWorld().z - (m_length * 0.5f) < posWorldSphere.z + lengthSphere
			&& GetPosWorld().y + (m_height * 0.5f) > posWorldSphere.y - lengthSphere
			&& GetPosWorld().y - (m_height * 0.5f) < posWorldSphere.y + lengthSphere)
		{
			if (GetPosWorld().x + (m_length * 0.5f) > posWorldSphere.x - lengthSphere)
			{// 左の当たり判定
				return true;
			}

			if (GetPosWorld().x - (m_length * 0.5f) < posWorldSphere.x + lengthSphere)
			{// 右の当たり判定
 				return true;
			}
		}

		if (GetPosWorld().x + (m_length * 0.5f) > posWorldSphere.x - lengthSphere
			&& GetPosWorld().x - (m_length * 0.5f) < posWorldSphere.x + lengthSphere
			&& GetPosWorld().y + (m_height * 0.5f) > posWorldSphere.y - lengthSphere
			&& GetPosWorld().y - (m_height * 0.5f) < posWorldSphere.y + lengthSphere)
		{
			if (GetPosWorld().z + (m_length * 0.5f) > posWorldSphere.z - lengthSphere)
			{// 前の当たり判定
				return true;
			}

			if (GetPosWorld().z - (m_length * 0.5f) < posWorldSphere.z + lengthSphere)
			{// 奥の当たり判定
				return true;
			}
		}

		if (GetPosWorld().x + (m_length * 0.5f) > posWorldSphere.x - lengthSphere
			&& GetPosWorld().x - (m_length * 0.5f) < posWorldSphere.x + lengthSphere
			&& GetPosWorld().z + (m_length * 0.5f) > posWorldSphere.z - lengthSphere
			&& GetPosWorld().z - (m_length * 0.5f) < posWorldSphere.z + lengthSphere)
		{
			if (GetPosWorld().y + (m_height * 0.5f) < posWorldSphere.y - lengthSphere
				)
			{// 上の当たり判定
				return true;
			}

			if (GetPosWorld().y - (m_height * 0.5f) > posWorldSphere.y + lengthSphere)
			{// 下の当たり判定
				return true;
			}
		}
	}

	return false;
}

//--------------------------------------------------------------
// 円柱とメッシュ(等間隔)
//--------------------------------------------------------------
bool CCollisionCylinder::ToMesh(CCollisionMesh* inMesh)
{
	bool isLanding = false;
	int primitive = inMesh->GetPrimitive();
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = inMesh->GetVtxBuff();
	int vtxX = inMesh->GetVtxX();
	int vtxZ = inMesh->GetVtxZ();

	CObjectPolygon3D::VERTEX_3D* pVtx = nullptr;			// 頂点情報へのポインタ
	const int nTri = 3;
	D3DXVECTOR3 posPoly[nTri];
	D3DXVECTOR3 pos;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int aaaa = 0;

	posPoly[0] = pVtx[0].pos;

	pos = GetPosWorld();

	int x = (int)(pos.x - posPoly[0].x) / 100;
	int z = (int)(posPoly[0].z - pos.z) / 100 * vtxX;

	int answer = x + z;

	if (answer < 0 || (answer + vtxX + 1) > (vtxX * vtxZ) || x > vtxX || z > vtxX * 100)
	{
		return false;
	}

	posPoly[0] = pVtx[answer + vtxX].pos;
	posPoly[1] = pVtx[answer].pos;
	posPoly[2] = pVtx[answer + vtxX + 1].pos;

	isLanding = ToMeshSurface(posPoly, inMesh->GetMtxWorld(),true);

	if (!isLanding)
	{
		posPoly[0] = pVtx[answer].pos;
		posPoly[1] = pVtx[answer + vtxX + 1].pos;
		posPoly[2] = pVtx[answer + 1].pos;

		isLanding = ToMeshSurface(posPoly, inMesh->GetMtxWorld(), false);
	}
	// インデックスバッファのアンロック
	vtxBuff->Unlock();

	return isLanding;
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CCollisionCylinder* CCollisionCylinder::Create(const D3DXVECTOR3 & pos, const float length, const float height)
{
	CCollisionCylinder* collision = new CCollisionCylinder;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_length = length;
	collision->m_height = height;
	collision->SetLine();
	return collision;
}

void CCollisionCylinder::SetLine()
{
	float left = -m_length;	// x1
	float right = m_length;	// x2
	float top = m_height;		// z1
	float bot = 0.0f;	// z2

						// ４つの頂点
	D3DXVECTOR3 posLine[10];
	posLine[0] = D3DXVECTOR3(0.0f, bot, left);
	posLine[1] = D3DXVECTOR3(0.0f, bot, right);
	posLine[2] = D3DXVECTOR3(right, bot, 0.0f);
	posLine[3] = D3DXVECTOR3(left, bot, 0.0f);
	posLine[4] = D3DXVECTOR3(0.0f, top, 0.0f);
	posLine[5] = D3DXVECTOR3(0.0f, bot, 0.0f);

	posLine[6] = D3DXVECTOR3(0.0f, top, left);
	posLine[7] = D3DXVECTOR3(0.0f, top, right);
	posLine[8] = D3DXVECTOR3(right, top, 0.0f);
	posLine[9] = D3DXVECTOR3(left, top, 0.0f);

	m_line[0]->SetLine(posLine[0], posLine[1]);
	m_line[1]->SetLine(posLine[2], posLine[3]);
	m_line[2]->SetLine(posLine[8], posLine[2]);
	m_line[3]->SetLine(posLine[9], posLine[3]);
	m_line[4]->SetLine(posLine[6], posLine[0]);
	m_line[5]->SetLine(posLine[7], posLine[1]);
	m_line[7]->SetLine(posLine[6], posLine[7]);
	m_line[8]->SetLine(posLine[8], posLine[9]);
}

bool CCollisionCylinder::ToMeshSurface(D3DXVECTOR3 inPos[3],D3DXMATRIX inWorld,bool isLeft)
{
	D3DXVECTOR3 posPoly[3];
	posPoly[0] = inPos[0];
	posPoly[1] = inPos[1];
	posPoly[2] = inPos[2];

	D3DXMATRIX mtxWorld = inWorld;

	// ローカルからワールドに変換
	D3DXVec3TransformCoord(&posPoly[0], &posPoly[0], &mtxWorld);
	D3DXVec3TransformCoord(&posPoly[1], &posPoly[1], &mtxWorld);
	D3DXVec3TransformCoord(&posPoly[2], &posPoly[2], &mtxWorld);

	D3DXVECTOR3 vecLine[3];

	// 頂点座標の取得
	vecLine[0] = posPoly[1] - posPoly[0];
	vecLine[1] = posPoly[2] - posPoly[1];
	vecLine[2] = posPoly[0] - posPoly[2];

	D3DXVECTOR3 vecPlayer[3];

	D3DXVECTOR3 pos = GetPosWorld();

	// 頂点座標の取得
	vecPlayer[0] = pos - posPoly[0];
	vecPlayer[1] = pos - posPoly[1];
	vecPlayer[2] = pos - posPoly[2];

	float InOut[3];

	InOut[0] = Vec2Cross(&vecLine[0], &vecPlayer[0]);
	InOut[1] = Vec2Cross(&vecLine[1], &vecPlayer[1]);
	InOut[2] = Vec2Cross(&vecLine[2], &vecPlayer[2]);

	bool hit = false;

	if (((InOut[0] >= 0 && InOut[1] >= 0 && InOut[2] >= 0) ||
		(InOut[0] <= 0 && InOut[1] <= 0 && InOut[2] <= 0)))
	{
		D3DXVECTOR3 V1 = posPoly[1] - posPoly[0];
		D3DXVECTOR3 V2 = posPoly[2] - posPoly[0];

		// 結果の箱
		D3DXVECTOR3 vecNormal;
		// メッシュの法線を求める
		D3DXVec3Cross(&vecNormal, &V1, &V2);
		// 大きさを１にする
		D3DXVec3Normalize(&vecNormal, &vecNormal);

		if (!isLeft)
		{// 法線ベクトルの向きを正す
			vecNormal *= -1;
		}

		// 当たったオブジェクトの位置を設定
		float meshHeight = posPoly[0].y - (vecNormal.x * (pos.x - posPoly[0].x) + vecNormal.z * (pos.z - posPoly[0].z)) / vecNormal.y;

		if (pos.y < meshHeight)
		{// メッシュの高さよりプレイヤーの高さのほうが下のとき
			SetPosParent(D3DXVECTOR3(pos.x, meshHeight, pos.z));
			hit = true;
		}
	}
	return hit;
}
