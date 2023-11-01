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
	CCollision::Uninit();
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
	collision->SetMtxWorld(inMtxWorld);

	return collision;
}
