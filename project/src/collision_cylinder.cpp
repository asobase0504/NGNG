//**************************************************************
//
// �~���̓����蔻��
// Author : ���c�喲
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
// �R���X�g���N�^
//--------------------------------------------------------------
CCollisionCylinder::CCollisionCylinder() : 
	m_length(0.0f),
	m_height(0.0f)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CCollisionCylinder::~CCollisionCylinder()
{
	for (int i = 0; i < 4; i++)
	{
		m_line[i] = nullptr;
	}
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CCollisionCylinder::Init()
{
	for (int i = 0; i < 4; i++)
	{
		m_line[i] = CLine::Create();
		SetEndChildren(m_line[i]);
	}
	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CCollisionCylinder::Update()
{
	CCollision::Update();

	D3DXVECTOR3 pos = GetPosWorld();
	D3DXVECTOR3 size = GetSize();
	D3DXVECTOR3 rot = GetRot();

	float left = -m_length;	// x1
	float right = m_length;	// x2
	float top = m_height;		// z1
	float bot = 0.0f;	// z2

	// �S�̒��_
	D3DXVECTOR3 posLine[6];
	posLine[0] = D3DXVECTOR3(0.0f, 0.0f, left);
	posLine[1] = D3DXVECTOR3(0.0f, 0.0f, right);
	posLine[2] = D3DXVECTOR3(right, 0.0f, 0.0f);
	posLine[3] = D3DXVECTOR3(left, 0.0f, 0.0f);
	posLine[4] = D3DXVECTOR3(0.0f, top, 0.0f);
	posLine[5] = D3DXVECTOR3(0.0f, bot, 0.0f);

	m_line[0]->SetLine(pos, rot, posLine[0], posLine[1], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[1]->SetLine(pos, rot, posLine[2], posLine[3], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[2]->SetLine(pos, rot, posLine[4], posLine[5], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	//m_line[3]->SetLine(pos, rot, posLine[3], posLine[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//--------------------------------------------------------------
// �~���Ɖ~��
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
// �~���Ɣ�
// �����FCCollisionBox* inBox (CCollisionBox�̃|�C���^), bool isExtrusion (���o�����邩�ǂ���)
//--------------------------------------------------------------
bool CCollisionCylinder::ToBox(CCollisionBox* inBox, bool isExtrusion)
{
	bool isLanding = false;

	D3DXVECTOR3 boxPos = inBox->GetPosWorld();
	D3DXVECTOR3 boxSize = inBox->GetSize();
	D3DXMATRIX boxMtxWorld = inBox->GetMtxWorld();

	D3DXVECTOR3 cylinderPos = GetPosWorld();
	D3DXVECTOR3 cylinderPosOld = GetPosOld();
	float radius = GetLength();

	float left = -boxSize.x * 0.5f;		// ��
	float right = boxSize.x * 0.5f;		// �E
	float top = boxSize.y * 0.5f;		// ��
	float bottum = -boxSize.y * 0.5f;	// ��
	float back = boxSize.z * 0.5f;		// ��
	float front = -boxSize.z * 0.5f;	// �O

	// �S�̒��_
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

	// ���o�ʒu
	D3DXVECTOR3 extrusion(0.0f, 0.0f, 0.0f);

	SetIsTop(false);
	SetIsUnder(false);

	if (InOut[0] < 0.0f && InOut[1] < 0.0f && InOut[2] < 0.0f && InOut[3] < 0.0f)
	{// Y�̉��o
		if (cylinderPosOld.y >= boxPos.y + boxSize.y && cylinderPos.y < boxPos.y + boxSize.y)
		{// ��
			extrusion.x = cylinderPos.x;
			extrusion.y = boxPos.y + boxSize.y;
			extrusion.z = cylinderPos.z;

			SetPosParent(extrusion);
			SetIsTop(true);
			isLanding = true;
		}

		if (cylinderPosOld.y + m_height <= boxPos.y  && cylinderPos.y + m_height > boxPos.y)
		{// ��
			extrusion.x = cylinderPos.x;
			extrusion.y = boxPos.y - m_height;
			extrusion.z = cylinderPos.z; 

			SetIsUnder(true);
			SetPosParent(extrusion);
			isLanding = true;
		}

		if (cylinderPos.y < boxPos.y + boxSize.y && cylinderPos.y + m_height > boxPos.y)
		{// XZ�̉��o
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{// �ǂ̕������痈��������
				D3DXVECTOR3 vecPosOld = cylinderPosOld - worldPos[nCnt];
				float leftPosOld = Vec2Cross(&vecLine[nCnt], &vecPosOld);

				if (leftPosOld > 0.0f)
				{// ����������������
					isLanding = true;

					// posOld����n�_�܂ł̋����iV�j
					D3DXVECTOR3 V = worldPos[nCnt] - cylinderPosOld;
					// �v���C���[��MOVE�iV1�j
					D3DXVECTOR3 vecMove = cylinderPos - cylinderPosOld;

					float t1 = Vec2Cross(&V, &vecLine[nCnt]) / Vec2Cross(&vecMove, &vecLine[nCnt]);
					float t2 = Vec2Cross(&V, &vecMove) / Vec2Cross(&vecMove, &vecLine[nCnt]);

					const float eps = 0.00001f;
					if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1)
					{// �������Ă��Ȃ�
						continue;
					}
					else
					{// �����o���p�@���̊i�[�p�̔�
						D3DXVECTOR3 nor;
						// ������̃x�N�g��
						D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);
						// ���K��
						D3DXVec3Normalize(&vecLine[nCnt], &vecLine[nCnt]);
						// �ʂ̖@�������߂�
						D3DXVec3Cross(&nor, &vecLine[nCnt], &vecUp);
						// �傫�����P�ɂ���
						D3DXVec3Normalize(&nor, &nor);

						// �t����
						D3DXVECTOR3 reverseVecMove = cylinderPosOld - cylinderPos;
						// (a)
						float difMove = Vec2Dot(&reverseVecMove, &nor);

						// �����Ԃ�
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
// �~���Ƌ�
//--------------------------------------------------------------
bool CCollisionCylinder::ToSphere(CCollisionSphere * inSphere)
{
	float lengthSphere = inSphere->GetLength();
	D3DXVECTOR3 posWorldSphere = inSphere->GetPosWorld();

	// �~���̔��a�Ƌ��̔��a�𑫂�������
	float addLength = m_length + lengthSphere;
	float addHeight = m_height + lengthSphere;

	// �~���̒��S�l���狅�̒��S�l�܂ł̋���
	D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f,0.0f,0.0f);
	differenceX.x = GetPosWorld().x - posWorldSphere.x;

	D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceY.y = GetPosWorld().y - posWorldSphere.y;

	D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceZ.z = GetPosWorld().z - posWorldSphere.z;

	//x,y,z�̐�Βl�̌v�Z
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
			{// ���̓����蔻��
				return true;
			}

			if (GetPosWorld().x - (m_length * 0.5f) < posWorldSphere.x + lengthSphere)
			{// �E�̓����蔻��
 				return true;
			}
		}

		if (GetPosWorld().x + (m_length * 0.5f) > posWorldSphere.x - lengthSphere
			&& GetPosWorld().x - (m_length * 0.5f) < posWorldSphere.x + lengthSphere
			&& GetPosWorld().y + (m_height * 0.5f) > posWorldSphere.y - lengthSphere
			&& GetPosWorld().y - (m_height * 0.5f) < posWorldSphere.y + lengthSphere)
		{
			if (GetPosWorld().z + (m_length * 0.5f) > posWorldSphere.z - lengthSphere)
			{// �O�̓����蔻��
				return true;
			}

			if (GetPosWorld().z - (m_length * 0.5f) < posWorldSphere.z + lengthSphere)
			{// ���̓����蔻��
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
			{// ��̓����蔻��
				return true;
			}

			if (GetPosWorld().y - (m_height * 0.5f) > posWorldSphere.y + lengthSphere)
			{// ���̓����蔻��
				return true;
			}
		}
	}

	return false;
}

//--------------------------------------------------------------
// �~���ƃ��b�V��
//--------------------------------------------------------------
bool CCollisionCylinder::ToMesh(CCollisionMesh* inMesh)
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

		D3DXVECTOR3 pos = GetPosWorld();

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
				SetPosParent(D3DXVECTOR3(pos.x, meshHeight, pos.z));
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

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CCollisionCylinder* CCollisionCylinder::Create(const D3DXVECTOR3 & pos, const float length, const float height)
{
	CCollisionCylinder* collision = new CCollisionCylinder;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_length = length;
	collision->m_height = height;

	return collision;
}
