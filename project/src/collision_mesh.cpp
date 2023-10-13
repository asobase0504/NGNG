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
}

//--------------------------------------------------------------
// ���b�V���Ɖ~��
// �����F�~���̃R���W����
//--------------------------------------------------------------
bool CCollisionMesh::ToCylinder(CCollisionCyinder* inCyinder, bool isExtrusion)
{
	int primitive = m_primitive;
	CObjectPolygon3D::VERTEX_3D* pVtx = nullptr;			// ���_���ւ̃|�C���^
	WORD* pIdx;
	const int nTri = 3;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// �C���f�b�N�X�o�b�t�@�����b�N
	m_idxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < primitive; nCnt++)
	{
		D3DXVECTOR3 posPoly[nTri];

		// ���_���W�̎擾
		posPoly[0] = pVtx[pIdx[nCnt + 0]].pos;
		posPoly[1] = pVtx[pIdx[nCnt + 1]].pos;
		posPoly[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{// �k�ރ|���S�����΂�
			continue;
		}

		// ���[�J�����烏�[���h�ɕϊ�
		D3DXVec3TransformCoord(&posPoly[0], &posPoly[0], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[1], &posPoly[1], &m_mtxWorld);
		D3DXVec3TransformCoord(&posPoly[2], &posPoly[2], &m_mtxWorld);

		D3DXVECTOR3 vecLine[nTri];

		// ���_���W�̎擾
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		D3DXVECTOR3 pos = inCyinder->GetPos();

		// ���_���W�̎擾
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

				// ���ʂ̔�
				D3DXVECTOR3 vecNormal;
				// ���b�V���̖@�������߂�
				D3DXVec3Cross(&vecNormal, &V1, &V2);
				// �傫�����P�ɂ���
				D3DXVec3Normalize(&vecNormal, &vecNormal);

				if (nCnt % 2 == 1)
				{// �@���x�N�g���̌����𐳂�
					vecNormal *= -1;
				}

				// ���������I�u�W�F�N�g�̈ʒu��ݒ�
				float meshHeight = posPoly[0].y - (vecNormal.x * (pos.x - posPoly[0].x) + vecNormal.z * (pos.z - posPoly[0].z)) / vecNormal.y;
				m_extrusionHeight = meshHeight;

			}
			return true;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_vtxBuff->Unlock();
	// ���_�o�b�t�@���A�����b�N����
	m_idxBuff->Unlock();

	return false;
}

//--------------------------------------------------------------
// ���b�V���Ƌ�
//--------------------------------------------------------------
bool CCollisionMesh::ToSphere(CCollisionSphere* inSphere)
{
	return false;
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
	collision->m_mtxWorld = inMtxWorld;

	return collision;
}
