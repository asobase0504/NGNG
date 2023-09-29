//=============================================================================
//
// �I�u�W�F�N�gX���� [objectX.cpp]
// Author : Yuda Kaito
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "objectX.h"
#include "objectX_group.h"
#include "object_polygon3d.h"
#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "utility.h"
#include "camera.h"
#include "light.h"
#include <assert.h>

#define InFront( a ) \
	((a) < 0.0f)

#define Behind( a ) \
	((a) >= 0.0f)

#define On( a ) \
	((a) < 0.005f && (a) > -0.005f)

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CObjectX::CObjectX(CTaskGroup::EPriority nPriority) :
	CObject(nPriority),
	m_scale(1.0f,1.0f,1.0f),
	m_MinVtxOrigin(0.0f, 0.0f, 0.0f),
	m_MaxVtxOrigin(0.0f, 0.0f, 0.0f),
	m_MinVtx(0.0f, 0.0f, 0.0f),
	m_MaxVtx(0.0f, 0.0f, 0.0f),
	m_pMesh(nullptr),
	m_pBuffMat(nullptr),
	m_NumMat(0),
	m_pParent(nullptr),
	m_isCollision(true),
	m_hasOutLine(false),
	m_hasShadow(false),
	pTex0(nullptr)
{
	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(CObject::MODEL);
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxRot);
	m_materialDiffuse.clear();
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CObjectX::~CObjectX()
{
}

//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̏�����
// Author : Yuda Kaito
// �T�v : ���������s��
//-----------------------------------------------------------------------------
HRESULT CObjectX::Init()
{
	extern LPD3DXEFFECT pEffect;	// �V�F�[�_�[

	// �n���h���̏�����
	m_hTechnique = pEffect->GetTechniqueByName("Diffuse");			// �G�t�F�N�g
	m_hTexture = pEffect->GetParameterByName(NULL, "Tex");			// �e�N�X�`��
	m_hmWVP = pEffect->GetParameterByName(NULL, "mWVP");			// ���[�J��-�ˉe�ϊ��s��
	m_hmWIT = pEffect->GetParameterByName(NULL, "mWIT");			// ���[�J��-���[���h�ϊ��s��
	m_hvLightDir = pEffect->GetParameterByName(NULL, "vLightDir");	// ���C�g�̕���
	m_hvDiffuse = pEffect->GetParameterByName(NULL, "vDiffuse");	// ���_�J���[
	m_hvAmbient = pEffect->GetParameterByName(NULL, "vAmbient");	// ���_�J���[
	m_hvEyePos = pEffect->GetParameterByName(NULL, "vEyePos");

	return S_OK;
}

//-----------------------------------------------------------------------------
// �`��
// Author : Yuda Kaito
// �T�v : �`����s��
//-----------------------------------------------------------------------------
void CObjectX::Draw()
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxTrans, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		D3DXMATRIX mtxParent = m_pParent->GetMtxWorld();

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	}

	DrawMaterial();
}

//-----------------------------------------------------------------------------
// �`��
// Author : Yuda Kaito
// �T�v : �`����s��
//-----------------------------------------------------------------------------
void CObjectX::DrawMaterial()
{
	extern LPD3DXEFFECT pEffect;		// �V�F�[�_�[

	if (pEffect == nullptr)
	{
		assert(false);
		return;
	}

	/* pEffect�ɒl�������Ă� */

	// �^�X�N�O���[�v���
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// �J�������
	CCamera* pCamera = (CCamera*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_CAMERA, GetPriority());

	D3DMATRIX viewMatrix = pCamera->GetMtxView();
	D3DMATRIX projMatrix = pCamera->GetMtxProje();

	// ���C�g���
	CLight* lightClass = (CLight*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_LIGHT, GetPriority());
	D3DLIGHT9 light = lightClass->GetLight(0);

	D3DXMATRIX m;

	//-------------------------------------------------
	// �V�F�[�_�̐ݒ�
	//-------------------------------------------------
	pEffect->SetTechnique(m_hTechnique);
	pEffect->Begin(NULL, 0);

	D3DXMatrixTranslation(&m, 1.0f, 0.0f, 0.0f);

	// ���[�J��-�ˉe�ϊ��s��
	D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
	D3DXMatrixTranspose(&m, &m);
	pEffect->SetMatrix(m_hmWIT, &m);

	// ���[�J��-�ˉe�ϊ��s��
	m = m_mtxWorld * viewMatrix * projMatrix;
	pEffect->SetMatrix(m_hmWVP, &m);

	// ���C�g�̕���
	D3DXVECTOR4 lightDir = D3DXVECTOR4(light.Direction.x, light.Direction.y, light.Direction.z, 0);
	D3DXMatrixInverse(&m, NULL, &m_mtxWorld);
	D3DXVec4Transform(&lightDir, &lightDir, &m);
	D3DXVec3Normalize((D3DXVECTOR3*)&lightDir, (D3DXVECTOR3*)&lightDir);
	pEffect->SetVector(m_hvLightDir, &lightDir);

	// ���_�s��
	m = m_mtxWorld * viewMatrix;
	D3DXMatrixInverse(&m, NULL, &m);

	// ���_
	D3DXVECTOR4 EyePos(0, 0, 0, 1);
	D3DXVec4Transform(&EyePos, &EyePos, &m);
	D3DXVec4Normalize(&EyePos, &EyePos);
	pEffect->SetVector(m_hvEyePos, &EyePos);	//���_���V�F�[�_�[�ɓn��

	//�}�e���A���f�[�^�̃|�C���^���擾����
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		// ���f���̐F�̐ݒ� 
		{
			D3DXVECTOR4 Diffuse;

			if (m_materialDiffuse.count(nCntMat) != 0)
			{
				Diffuse = (D3DXVECTOR4)m_materialDiffuse[nCntMat];
			}
			else
			{
				Diffuse = D3DXVECTOR4(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a);
			}

			Diffuse.w = m_color.a;

			pEffect->SetVector(m_hvDiffuse, &Diffuse);
		}
		{
			D3DXVECTOR4 Ambient;
			//Ambient = D3DXVECTOR4(pMat[nCntMat].MatD3D.Ambient.r, pMat[nCntMat].MatD3D.Ambient.g, pMat[nCntMat].MatD3D.Ambient.b, pMat[nCntMat].MatD3D.Ambient.a);
			Ambient = D3DXVECTOR4(0.0f, 0.0f, 0.0f, pMat[nCntMat].MatD3D.Ambient.a);
			pEffect->SetVector(m_hvAmbient, &Ambient);
		}

		LPDIRECT3DTEXTURE9 texture = CTexture::GetInstance()->GetTexture("TOON");
		if (texture != nullptr)
		{// �e�N�X�`���̓K��
			pTex0 = texture;
		}

		// �e�N�X�`���̐ݒ�
		pEffect->SetTexture(m_hTexture, pTex0);

		pEffect->BeginPass(0);
		m_pMesh->DrawSubset(nCntMat);	//���f���p�[�c�̕`��
		pEffect->EndPass();
	}

	pEffect->End();
}

//-----------------------------------------------------------------------------
// scale�̐ݒ�
//-----------------------------------------------------------------------------
void CObjectX::SetScale(const D3DXVECTOR3& inScale)
{
	m_scale = inScale;

	m_MinVtx.x = m_scale.x * m_MinVtxOrigin.x;
	m_MinVtx.y = m_scale.y * m_MinVtxOrigin.y;
	m_MinVtx.z = m_scale.z * m_MinVtxOrigin.z;

	m_MaxVtx.x = m_scale.x * m_MaxVtxOrigin.x;
	m_MaxVtx.y = m_scale.y * m_MaxVtxOrigin.y;
	m_MaxVtx.z = m_scale.z * m_MaxVtxOrigin.z;
}

//-----------------------------------------------------------------------------
// �����̐ݒ�
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CObjectX::SetRot(const D3DXVECTOR3 & inRot)
{
	if (m_rot != inRot)
	{
		SetMtxRot(inRot);
	}
	m_rot = inRot;
}

//-----------------------------------------------------------------------------
// ���_�ő召�l�̌v�Z����
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CObjectX::SetMtxRot(const D3DXVECTOR3 & inRot)
{
	D3DXQUATERNION quaternion;
	D3DXQuaternionRotationYawPitchRoll(&quaternion, inRot.y, inRot.x, inRot.z);
	SetMtxQuaternion(quaternion);
}

//-----------------------------------------------------------------------------
// ���_�ő召�l�̌v�Z����
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CObjectX::CalculationVtx()
{
	D3DXMATRIX mtxTrans, mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);

	// �����̔��f
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &m_mtxRot);		// �s��|���Z�֐�

	D3DXVec3TransformCoord(&m_MaxVtx, &m_MaxVtx, &mtxWorld);
	D3DXVec3TransformCoord(&m_MinVtx, &m_MinVtx, &mtxWorld);

	if (m_MaxVtx.x < m_MinVtx.x)
	{
		float change = m_MaxVtx.x;
		m_MaxVtx.x = m_MinVtx.x;
		m_MinVtx.x = change;
	}

	if (m_MaxVtx.y < m_MinVtx.y)
	{
		float change = m_MaxVtx.y;
		m_MaxVtx.y = m_MinVtx.y;
		m_MinVtx.y = change;
	}

	if (m_MaxVtx.z < m_MinVtx.z)
	{
		float change = m_MaxVtx.z;
		m_MaxVtx.z = m_MinVtx.z;
		m_MinVtx.z = change;
	}
}

//-----------------------------------------------------------------------------
// ��������
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, CTaskGroup::EPriority nPriority)
{
	// �|�C���^�錾
	CObjectX *pObjectX = nullptr;

	// �C���X�^���X����
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{// �|�C���^�����݂�������s
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{// �|�C���^����������������s
		assert(false);
	}

	// �|�C���^��Ԃ�
	return pObjectX;
}

//-----------------------------------------------------------------------------
// ���f���̓ǂݍ���
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CObjectX::LoadModel(const char *aFileName)
{
	CObjectXGroup *xGroup = CApplication::GetInstance()->GetObjectXGroup();
	m_pBuffMat = xGroup->GetBuffMat(aFileName);
	m_MaxVtxOrigin = xGroup->GetMaxVtx(aFileName);
	m_MaxVtx = m_MaxVtxOrigin;
	m_MinVtxOrigin = xGroup->GetMinVtx(aFileName);
	m_MinVtx = m_MinVtxOrigin;
	m_pMesh = xGroup->GetMesh(aFileName);
	m_NumMat = xGroup->GetNumMat(aFileName);
	m_size = xGroup->GetSize(aFileName);
}

//-----------------------------------------------------------------------------
// ���s���e����
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CObjectX::Projection(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �ϐ��錾
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DMATERIAL9 Material;

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	vecLight = -D3DXVECTOR4(0.2f, -0.5f, 0.3f, 0.0f);

	if (m_pos.y >= -20.0f)
	{
		pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	}

	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow,&vecLight, &planeField);

	// ���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A����ێ�
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	if (m_pBuffMat != nullptr)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			Material = pMat[nCntMat].MatD3D;
			Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&Material);

			// ���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//-----------------------------------------------------------------------------
// �F���i�g�U���ˌ��j�̐ݒ�
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CObjectX::SetMaterialDiffuse(unsigned int index, const D3DXCOLOR & inColor)
{
	// �ύX�\��̃}�e���A�����Ȃ��ꍇ
	if (index >= m_NumMat)
	{
		assert(false);
		return;
	}

	if (m_materialDiffuse.count(index) == 0)
	{
		m_materialDiffuse.emplace(index, inColor);
	}
	else
	{
		m_materialDiffuse[index] = inColor;
	}
}

//-----------------------------------------------------------------------------
// Sphere��AABB�̓����蔻��
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
bool CObjectX::SphereAndAABB(CObjectX * inObjectX, D3DXVECTOR3 * outPos)
{
	if (!inObjectX->IsCollision())
	{
		return false;
	}

	D3DXVECTOR3 dist(0.0f,0.0f,0.0f);
	float length = AABBAndPointLength(inObjectX, &dist);	// �ŒZ����

	if (m_MaxVtx.x * 1.4f > length)
	{
		if (outPos != nullptr)
		{
			*outPos = dist;
		}

		m_pos -= dist * (m_MaxVtx.x * 1.4f - length);
	}

	return m_MaxVtx.x * 1.4f > length;
}

//-----------------------------------------------------------------------------
// Ray��AABB�̓����蔻��
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
bool CObjectX::RayAndAABB(const D3DXVECTOR3 & inPos, const D3DXVECTOR3 & inNormal, D3DXVECTOR3* outPos)
{
	float tmin = (m_MinVtx.x + m_pos.x - inPos.x) / inNormal.x;
	float tmax = (m_MaxVtx.x + m_pos.x - inPos.x) / inNormal.x;

	if (tmin > tmax)
	{
		std::swap(tmin, tmax);
	}

	float tymin = (m_MinVtx.y + m_pos.y - inPos.y) / inNormal.y;
	float tymax = (m_MaxVtx.y + m_pos.y - inPos.y) / inNormal.y;

	if (tymin > tymax)
	{
		std::swap(tymin, tymax);
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	float tzmin = (m_MinVtx.z + m_pos.z - inPos.z) / inNormal.z;
	float tzmax = (m_MaxVtx.z + m_pos.z - inPos.z) / inNormal.z;

	if (tzmin > tzmax)
	{
		std::swap(tzmin, tzmax);
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	*outPos = inPos + inNormal * tmin;

	return true;
}

//-----------------------------------------------------------------------------
// ������AABB�̓����蔻��
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
bool CObjectX::SegmentAndAABB(const D3DXVECTOR3 & inPos, const D3DXVECTOR3 & inPos2, D3DXVECTOR3* outPos)
{
	// �����̗��[�_��AABB���Ɋ܂܂�Ă��邩�ǂ����𔻒肷��B
	{
		D3DXVECTOR3 min = m_pos + m_MinVtx;
		D3DXVECTOR3 max = m_pos + m_MaxVtx;

		bool isBoxContainsPos;
		{
			bool isContainsX = inPos.x > min.x && inPos.x < max.x;
			bool isContainsY = inPos.y > min.y && inPos.y < max.y;
			bool isContainsZ = inPos.z > min.z && inPos.z < max.z;

			isBoxContainsPos = isContainsX && isContainsY && isContainsZ;
		}

		bool isBoxContainsPos2;
		{
			bool isContainsX = inPos2.x > min.x && inPos2.x < max.x;
			bool isContainsY = inPos2.y > min.y && inPos2.y < max.y;
			bool isContainsZ = inPos2.z > min.z && inPos2.z < max.z;

			isBoxContainsPos2 = isContainsX && isContainsY && isContainsZ;
		}

		if (isBoxContainsPos || isBoxContainsPos2)
		{
			*outPos = inPos;
			return true;
		}
	}
	D3DXVECTOR3 hitPos(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 min;
	D3DXVECTOR3 max;

	if (inPos.x < inPos2.x)
	{
		min.x = inPos.x;
		max.x = inPos2.x;
	}
	else
	{
		min.x = inPos2.x;
		max.x = inPos.x;
	}

	if (inPos.y < inPos2.y)
	{
		min.y = inPos.y;
		max.y = inPos2.y;
	}
	else
	{
		min.y = inPos2.y;
		max.y = inPos.y;
	}

	if (inPos.z < inPos2.z)
	{
		min.z = inPos.z;
		max.z = inPos2.z;
	}
	else
	{
		min.z = inPos2.z;
		max.z = inPos.z;
	}

	D3DXVECTOR3 dist = inPos2 - inPos;
	D3DXVec3Normalize(&dist, &dist);

	if (RayAndAABB(inPos, dist, &hitPos))
	{
		bool hitX = min.x < hitPos.x && hitPos.x < max.x;
		bool hitY = min.y < hitPos.y && hitPos.y < max.y;
		bool hitZ = min.z < hitPos.z && hitPos.z < max.z;

		if (hitX && hitY && hitZ)
		{
			if (outPos != nullptr)
			{
				*outPos = hitPos;
			}
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// ���ݒn��AABB�̍ŏ�����
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
float CObjectX::AABBAndPointLength(CObjectX * inObject, D3DXVECTOR3* outDist)
{
	float SqLen = 0.0f;	// �����ׂ̂���̒l���i�[

	// �e���œ_���ŏ��l�ȉ��������͍ő�l�ȏ�Ȃ�΁A�����l��

	D3DXVECTOR3 min = inObject->m_pos + inObject->m_MinVtx;
	D3DXVECTOR3 max = inObject->m_pos + inObject->m_MaxVtx;
	D3DXVECTOR3 dist(0.0f,0.0f,0.0f);

	if (m_pos.x < min.x)
	{
		SqLen += (m_pos.x - min.x) * (m_pos.x - min.x);
		dist.x += 1.0f;
	}

	if (m_pos.x > max.x)
	{
		SqLen += (m_pos.x - max.x) * (m_pos.x - max.x);
		dist.x += -1.0f;
	}

	if (m_pos.y < min.y)
	{
		SqLen += (m_pos.y - min.y) * (m_pos.y - min.y);
		dist.y += 1.0f;
	}

	if (m_pos.y > max.y)
	{
		SqLen += (m_pos.y - max.y) * (m_pos.y - max.y);
		dist.y += -1.0f;
	}

	if (m_pos.z < min.z)
	{
		SqLen += (m_pos.z - min.z) * (m_pos.z - min.z);
		dist.z += 1.0f;
	}

	if (m_pos.z > max.z)
	{
		SqLen += (m_pos.z - max.z) * (m_pos.z - max.z);
		dist.z+= -1.0f;
	}

	D3DXVec3Normalize(&dist, &dist);

	if (outDist != nullptr)
	{
		*outDist = dist;
	}

	return sqrt(SqLen);
}
