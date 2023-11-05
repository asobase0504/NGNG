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
// �R���X�g���N�^
//--------------------------------------------------------------
CCollisionMesh::CCollisionMesh() : m_primitive(0), m_vtxBuff(nullptr), m_idxBuff(nullptr)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CCollisionMesh::~CCollisionMesh()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CCollisionMesh::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CCollisionMesh::Uninit()
{
	CCollision::Uninit();
}

//--------------------------------------------------------------
// �����蔻��̐���
// �����F���b�V���̃|���S�����A���_���A�C���f�b�N�X��
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
