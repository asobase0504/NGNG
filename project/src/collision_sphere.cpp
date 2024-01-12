#include "collision_sphere.h"
#include "collision_mesh.h"
#include "collision_cylinder.h"
#include "object_polygon3d.h"
#include "utility.h"
#include "line.h"

CCollisionSphere::CCollisionSphere()
{
}

CCollisionSphere::~CCollisionSphere()
{
}

HRESULT CCollisionSphere::Init()
{
	for (int i = 0; i < 8; i++)
	{
		m_line[i] = CLine::Create();
		SetEndChildren(m_line[i]);
		m_line[i]->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		m_line[i]->SetPosTarget(&GetPosWorld());
		m_line[i]->SetRotTarget(&GetRot());
	}

	return S_OK;
}

bool CCollisionSphere::ToMesh(CCollisionMesh* inMesh)
{
	bool isLanding = false;
	int primitive = inMesh->GetPrimitive();
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = inMesh->GetVtxBuff();
	LPDIRECT3DINDEXBUFFER9 idxBuff = inMesh->GetIdxBuff();
	D3DXMATRIX mtxWorld = inMesh->GetMtxWorld();

	CObjectPolygon3D::VERTEX_3D* pVtx = nullptr;			// 頂点情報へのポインタ
	WORD* pIdx;
	const int nTri = 3;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// インデックスバッファをロック
	idxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < primitive; nCnt++)
	{
		D3DXVECTOR3 posPoly[nTri];

		// 頂点座標の取得
		posPoly[0] = pVtx[pIdx[nCnt + 0]].pos;
		posPoly[1] = pVtx[pIdx[nCnt + 1]].pos;
		posPoly[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{// 縮退ポリゴンを飛ばす
			continue;
		}

		// ローカルからワールドに変換
		D3DXVec3TransformCoord(&posPoly[0], &posPoly[0], &mtxWorld);
		D3DXVec3TransformCoord(&posPoly[1], &posPoly[1], &mtxWorld);
		D3DXVec3TransformCoord(&posPoly[2], &posPoly[2], &mtxWorld);

		D3DXVECTOR3 vecLine[nTri];

		// 頂点座標の取得
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		D3DXVECTOR3 pos = GetPosWorld();

		// 頂点座標の取得
		vecPlayer[0] = pos - posPoly[0];
		vecPlayer[1] = pos - posPoly[1];
		vecPlayer[2] = pos - posPoly[2];

		float InOut[nTri];

		InOut[0] = Vec2Cross(&vecLine[0], &vecPlayer[0]);
		InOut[1] = Vec2Cross(&vecLine[1], &vecPlayer[1]);
		InOut[2] = Vec2Cross(&vecLine[2], &vecPlayer[2]);

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

			if (nCnt % 2 == 1)
			{// 法線ベクトルの向きを正す
				vecNormal *= -1;
			}

			// 当たったオブジェクトの位置を設定
			float meshHeight = posPoly[0].y - (vecNormal.x * (pos.x - posPoly[0].x) + vecNormal.z * (pos.z - posPoly[0].z)) / vecNormal.y;

			if (pos.y < meshHeight)
			{// メッシュの高さよりプレイヤーの高さのほうが下のとき
				m_extrusionHeight = meshHeight;
			}
			else
			{
				return isLanding;
			}

			isLanding = true;
		}
	}

	// インデックスバッファのアンロック
	vtxBuff->Unlock();
	// 頂点バッファをアンロックする
	idxBuff->Unlock();

	return isLanding;
}

bool CCollisionSphere::ToBox(CCollisionBox* inBox, bool isExtrusion)
{
	return false;
}

bool CCollisionSphere::ToSphere(CCollisionSphere* inSphere)
{
	float addLength = m_length + inSphere->GetLength();

	D3DXVECTOR3 difference = GetPosWorld() - inSphere->GetPosWorld();

	float differenceLength = D3DXVec3Length(&difference);

	if (addLength >= differenceLength)
	{
		return true;
	}

	return false;
}

bool CCollisionSphere::ToCylinder(CCollisionCylinder * inCylinder)
{
	float lengthSphere = GetLength();
	D3DXVECTOR3 posWorldSphere = GetPosWorld();

	float cylinderLength = inCylinder->GetLength();
	float cylinderHeigth = inCylinder->GetHeight();
	D3DXVECTOR3 posWorldCylinder = inCylinder->GetPosWorld();

	// 円柱の半径と球の半径を足した距離
	float addLength = cylinderLength + lengthSphere;
	float addHeight = cylinderHeigth + lengthSphere;

	// 円柱の中心値から球の中心値までの距離
	D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceX.x = posWorldCylinder.x - posWorldSphere.x;

	D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceY.y = posWorldCylinder.y - posWorldSphere.y;

	D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceZ.z = posWorldCylinder.z - posWorldSphere.z;

	//x,y,zの絶対値の計算
	float differenceLengthX = D3DXVec3Length(&differenceX);
	float differenceLengthY = D3DXVec3Length(&differenceY);
	float differenceLengthZ = D3DXVec3Length(&differenceZ);

	if (differenceLengthX <= addLength
		&& differenceLengthY < addHeight
		&& differenceLengthZ <= addLength)
	{
		if (posWorldCylinder.z + (cylinderLength * 0.5f) > posWorldSphere.z - lengthSphere
			&& posWorldCylinder.z - (cylinderLength * 0.5f) < posWorldSphere.z + lengthSphere
			&& posWorldCylinder.y + (cylinderHeigth * 0.5f) > posWorldSphere.y - lengthSphere
			&& posWorldCylinder.y - (cylinderHeigth * 0.5f) < posWorldSphere.y + lengthSphere)
		{
			if (posWorldCylinder.x + (cylinderLength * 0.5f) > posWorldSphere.x - lengthSphere)
			{// 左の当たり判定
				return true;
			}

			if (posWorldCylinder.x - (cylinderLength * 0.5f) < posWorldSphere.x + lengthSphere)
			{// 右の当たり判定
				return true;
			}
		}

		if (posWorldCylinder.x + (cylinderLength * 0.5f) > posWorldSphere.x - lengthSphere
			&& posWorldCylinder.x - (cylinderLength * 0.5f) < posWorldSphere.x + lengthSphere
			&& posWorldCylinder.y + (cylinderHeigth * 0.5f) > posWorldSphere.y - lengthSphere
			&& posWorldCylinder.y - (cylinderHeigth * 0.5f) < posWorldSphere.y + lengthSphere)
		{
			if (posWorldCylinder.z + (cylinderLength * 0.5f) > posWorldSphere.z - lengthSphere)
			{// 前の当たり判定
				return true;
			}

			if (posWorldCylinder.z - (cylinderLength * 0.5f) < posWorldSphere.z + lengthSphere)
			{// 奥の当たり判定
				return true;
			}
		}

		if (posWorldCylinder.x + (cylinderLength * 0.5f) > posWorldSphere.x - lengthSphere
			&& posWorldCylinder.x - (cylinderLength * 0.5f) < posWorldSphere.x + lengthSphere
			&& posWorldCylinder.z + (cylinderLength * 0.5f) > posWorldSphere.z - lengthSphere
			&& posWorldCylinder.z - (cylinderLength * 0.5f) < posWorldSphere.z + lengthSphere)
		{
			if (posWorldCylinder.y + (cylinderHeigth * 0.5f) < posWorldSphere.y - lengthSphere
				)
			{// 上の当たり判定
				return true;
			}

			if (posWorldCylinder.y - (cylinderHeigth * 0.5f) > posWorldSphere.y + lengthSphere)
			{// 下の当たり判定
				return true;
			}
		}
	}

	return false;
}

CCollisionSphere * CCollisionSphere::Create(const D3DXVECTOR3 & pos, const float length)
{
	CCollisionSphere* collision = new CCollisionSphere;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_length = length;
	collision->SetLine();
	return collision;
}

void CCollisionSphere::SetLine()
{
	// ４つの頂点
	D3DXVECTOR3 posLine[6];
	posLine[0] = D3DXVECTOR3(m_length, 0.0f, 0.0f);
	posLine[1] = D3DXVECTOR3(-m_length, 0.0f, 0.0f);
	posLine[2] = D3DXVECTOR3(0.0f, m_length, 0.0f);
	posLine[3] = D3DXVECTOR3(0.0f, -m_length, 0.0f);
	posLine[4] = D3DXVECTOR3(0.0f, 0.0f, m_length);
	posLine[5] = D3DXVECTOR3(0.0f, 0.0f, -m_length);

	m_line[0]->SetLine(posLine[2], posLine[0]);
	m_line[1]->SetLine(posLine[2], posLine[1]);
	m_line[2]->SetLine(posLine[2], posLine[4]);
	m_line[3]->SetLine(posLine[2], posLine[5]);
	m_line[4]->SetLine(posLine[3], posLine[0]);
	m_line[5]->SetLine(posLine[3], posLine[1]);
	m_line[6]->SetLine(posLine[3], posLine[4]);
	m_line[7]->SetLine(posLine[3], posLine[5]);
}
