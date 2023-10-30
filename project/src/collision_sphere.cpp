#include "collision_sphere.h"
#include "collision_mesh.h"
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
	}

	return E_NOTIMPL;
}

void CCollisionSphere::Update()
{
	// �S�̒��_
	D3DXVECTOR3 posLine[6];
	posLine[0] = D3DXVECTOR3(m_length, 0.0f, 0.0f);
	posLine[1] = D3DXVECTOR3(-m_length, 0.0f, 0.0f);
	posLine[2] = D3DXVECTOR3(0.0f, m_length, 0.0f);
	posLine[3] = D3DXVECTOR3(0.0f, -m_length, 0.0f);
	posLine[4] = D3DXVECTOR3(0.0f, 0.0f, m_length);
	posLine[5] = D3DXVECTOR3(0.0f, 0.0f, -m_length);

	m_line[0]->SetLine(GetPos(), GetRot(), posLine[2], posLine[0], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_line[1]->SetLine(GetPos(), GetRot(), posLine[2], posLine[1], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_line[2]->SetLine(GetPos(), GetRot(), posLine[2], posLine[4], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_line[3]->SetLine(GetPos(), GetRot(), posLine[2], posLine[5], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_line[4]->SetLine(GetPos(), GetRot(), posLine[3], posLine[0], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_line[5]->SetLine(GetPos(), GetRot(), posLine[3], posLine[1], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_line[6]->SetLine(GetPos(), GetRot(), posLine[3], posLine[4], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_line[7]->SetLine(GetPos(), GetRot(), posLine[3], posLine[5], D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
}

void CCollisionSphere::Uninit()
{
	for (int i = 0; i < 8; i++)
	{
		m_line[i]->Uninit();
	}
	CCollision::Uninit();
}

bool CCollisionSphere::ToMesh(CCollisionMesh* inMesh)
{
	bool isLanding = false;
	int primitive = inMesh->GetPrimitive();
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = inMesh->GetVtxBuff();
	LPDIRECT3DINDEXBUFFER9 idxBuff = inMesh->GetIdxBuff();
	D3DXMATRIX mtxWorld = inMesh->GetMtxWorld();

	CObjectPolygon3D::VERTEX_3D* pVtx = nullptr;			// ���_���ւ̃|�C���^
	WORD* pIdx;
	const int nTri = 3;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// �C���f�b�N�X�o�b�t�@�����b�N
	idxBuff->Lock(0, 0, (void**)&pIdx, 0);

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
		D3DXVec3TransformCoord(&posPoly[0], &posPoly[0], &mtxWorld);
		D3DXVec3TransformCoord(&posPoly[1], &posPoly[1], &mtxWorld);
		D3DXVec3TransformCoord(&posPoly[2], &posPoly[2], &mtxWorld);

		D3DXVECTOR3 vecLine[nTri];

		// ���_���W�̎擾
		vecLine[0] = posPoly[1] - posPoly[0];
		vecLine[1] = posPoly[2] - posPoly[1];
		vecLine[2] = posPoly[0] - posPoly[2];

		D3DXVECTOR3 vecPlayer[nTri];

		D3DXVECTOR3 pos = GetPos();

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

			if (pos.y < meshHeight)
			{// ���b�V���̍������v���C���[�̍����̂ق������̂Ƃ�
				m_extrusionHeight = meshHeight;
			}
			else
			{
				return isLanding;
			}

			isLanding = true;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	vtxBuff->Unlock();
	// ���_�o�b�t�@���A�����b�N����
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

	D3DXVECTOR3 difference = GetPos() - inSphere->GetPos();

	float differenceLength = D3DXVec3Length(&difference);

	if (addLength >= differenceLength)
	{
		return true;
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

	return collision;
}
