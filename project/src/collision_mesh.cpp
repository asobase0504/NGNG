//**************************************************************
//
// collision_mesh
// Author : Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "collision_mesh.h"
#include "object_polygon3d.h"
#include "collision_cylinder.h"
#include "utility.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CCollisionMesh::CCollisionMesh() : m_primitive(0), m_vtxBuff(nullptr), m_idxBuff(nullptr)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CCollisionMesh::~CCollisionMesh()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CCollisionMesh::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CCollisionMesh::Uninit()
{
}

//--------------------------------------------------------------
// メッシュと円柱
// 引数：円柱のコリジョン
//--------------------------------------------------------------
bool CCollisionMesh::ToCylinder(CCollisionCyinder* inCyinder, bool isExtrusion)
{
	int primitive = m_primitive;
	CObjectPolygon3D::VERTEX_3D* pVtx = nullptr;			// 頂点情報へのポインタ
	WORD* pIdx;
	const int nTri = 3;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// インデックスバッファをロック
	m_idxBuff->Lock(0, 0, (void**)&pIdx, 0);

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
		D3DXVec3TransformCoord(&posPoly[0], &posPoly[0], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[1], &posPoly[1], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[2], &posPoly[2], &m_mtxWorld);

		D3DXVECTOR3 vecLine[nTri];

		// 頂点座標の取得
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		D3DXVECTOR3 pos = inCyinder->GetPos();

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
			if (isExtrusion)
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
				m_extrusionHeight = meshHeight;

			}
			return true;
		}
	}

	// インデックスバッファのアンロック
	m_vtxBuff->Unlock();
	// 頂点バッファをアンロックする
	m_idxBuff->Unlock();

	return false;
}

//--------------------------------------------------------------
// メッシュと球
//--------------------------------------------------------------
bool CCollisionMesh::ToSphere(CCollisionSphere* inSphere)
{
	return false;
}

//--------------------------------------------------------------
// 当たり判定の生成
// 引数：メッシュのポリゴン数、頂点数、インデックス数
//--------------------------------------------------------------
CCollisionMesh* CCollisionMesh::Create(int inPrimitive, LPDIRECT3DVERTEXBUFFER9 inVtxBuff, LPDIRECT3DINDEXBUFFER9 inIdxBuff, D3DXMATRIX inMtxWorld)
{
	CCollisionMesh* collision = new CCollisionMesh;

	assert(collision != nullptr);

	collision->Init();
	collision->m_primitive = inPrimitive;
	collision->m_vtxBuff = inVtxBuff;
	collision->m_idxBuff = inIdxBuff;
	collision->m_mtxWorld = inMtxWorld;

	return collision;
}
