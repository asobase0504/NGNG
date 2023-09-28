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
	DrawOutLine();
	DrawShadow();
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
// �A�E�g���C����`��
//-----------------------------------------------------------------------------
void CObjectX::DrawOutLine()
{
	if (!m_hasOutLine)
	{
		return;
	}

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScale,mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&m_mtxWorld);

	// �傫���𔽉f
	//D3DXMatrixScaling(&mtxTrans, -m_scale.x * 1.05f, -m_scale.y * 1.05f, -m_scale.z * 1.05f);
	D3DXMatrixScaling(&mtxScale, -m_scale.x - 0.15f, -m_scale.y - 0.15f, -m_scale.z - 0.15f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

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

	D3DXCOLOR color = m_materialDiffuse[0];
	m_materialDiffuse[0] = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	DrawMaterial();
	m_materialDiffuse[0] = color;
}

//-----------------------------------------------------------------------------
// �e��`��
//-----------------------------------------------------------------------------
void CObjectX::DrawShadow()
{
	if (!m_hasShadow)
	{
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxShadow;
	D3DXPLANE planeField;

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	// Y�����Œ�ɂ���
	D3DXVECTOR3 pos(D3DXVECTOR3(0.0f, -FLT_MAX, 0.0f));

	// �S�Ă̒n�ʂƓ����蔻����s��
	CObject::TypeAllFunc(EType::PLAIN, CTaskGroup::EPriority::LEVEL_3D_1, [this,&pos](CObject* inObject)
	{
		CObjectX* plain = (CObjectX*)inObject;

		D3DXVECTOR3 outPos;

		if (plain->RayAndAABB(m_pos, D3DXVECTOR3(0.0f, -1.0f, 0.0f), &outPos))
		{
			outPos.y += 1.0f;

			bool isParentThanOn = m_pos.y > outPos.y;	// �e����
			bool isThisThanDown = pos.y < outPos.y;		// �\�肳��Ă�ʒu����

			if (isParentThanOn && isThisThanDown)
			{
				pos = outPos;
			}
		}
	});

	D3DXVECTOR3 normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	D3DXVECTOR4 vecLight;	// �e�̕���
	vecLight = D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f) * -1.0f;	// �^���ɉe�𗎂Ƃ�

	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// ���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxShadow);

	std::vector<D3DXCOLOR> diffuseList;
	diffuseList.resize(m_NumMat);

	for (int i = 0; i < (int)m_NumMat; i++)
	{
		diffuseList.at(i) = GetMaterialDiffuse(i);
		SetMaterialDiffuse(i,D3DXCOLOR(0.15f,0.15f,0.15f,1.0f));
	}

	DrawMaterial();

	for (int i = 0; i < (int)m_NumMat; i++)
	{
		SetMaterialDiffuse(i, diffuseList.at(i));
	}
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
// OBB��OBB�̓����蔻��
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
bool CObjectX::OBBAndOBB(CObjectX* inObjectX)
{
	if (!inObjectX->IsCollision())
	{
		return false;
	}

	// �ϐ��錾
	D3DXVECTOR3 interval = GetPos() - inObjectX->GetPos();

	D3DXVECTOR3 thisVecX;
	D3DXVECTOR3 thisVecY;
	D3DXVECTOR3 thisVecZ;
	D3DXVECTOR3 thisNormalizeVecX;
	D3DXVECTOR3 thisNormalizeVecY;
	D3DXVECTOR3 thisNormalizeVecZ;

	{
		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot = m_mtxRot;

		D3DXVECTOR3 size = GetMaxVtx();

		thisNormalizeVecX = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		thisNormalizeVecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		thisNormalizeVecZ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3TransformCoord(&thisNormalizeVecX, &thisNormalizeVecX, &mtxRot);
		D3DXVec3TransformCoord(&thisNormalizeVecY, &thisNormalizeVecY, &mtxRot);
		D3DXVec3TransformCoord(&thisNormalizeVecZ, &thisNormalizeVecZ, &mtxRot);
		D3DXVec3Normalize(&thisNormalizeVecX, &thisNormalizeVecX);
		D3DXVec3Normalize(&thisNormalizeVecY, &thisNormalizeVecY);
		D3DXVec3Normalize(&thisNormalizeVecZ, &thisNormalizeVecZ);
		thisVecX = thisNormalizeVecX * size.x;
		thisVecY = thisNormalizeVecY * size.y;
		thisVecZ = thisNormalizeVecZ * size.z;
	}

	D3DXVECTOR3 targetVecX;
	D3DXVECTOR3 targetVecY;
	D3DXVECTOR3 targetVecZ;
	D3DXVECTOR3 targetNormalizeVecX;
	D3DXVECTOR3 targetNormalizeVecY;
	D3DXVECTOR3 targetNormalizeVecZ;

	{
		// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxRot = inObjectX->GetMtxRot();

		D3DXVECTOR3 size = inObjectX->GetMaxVtx();

		targetNormalizeVecX = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		targetNormalizeVecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		targetNormalizeVecZ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVec3TransformCoord(&targetNormalizeVecX, &targetNormalizeVecX, &mtxRot);
		D3DXVec3TransformCoord(&targetNormalizeVecY, &targetNormalizeVecY, &mtxRot);
		D3DXVec3TransformCoord(&targetNormalizeVecZ, &targetNormalizeVecZ, &mtxRot);
		D3DXVec3Normalize(&targetNormalizeVecX, &targetNormalizeVecX);
		D3DXVec3Normalize(&targetNormalizeVecY, &targetNormalizeVecY);
		D3DXVec3Normalize(&targetNormalizeVecZ, &targetNormalizeVecZ);
		targetVecX = targetNormalizeVecX * size.x;
		targetVecY = targetNormalizeVecY * size.y;
		targetVecZ = targetNormalizeVecZ * size.z;
	}

	float thisRadius;
	float targetRadius;
	float length;

	//A.e1
	thisRadius = D3DXVec3Length(&thisVecX);
	targetRadius = LenSegOnSeparateAxis(&thisNormalizeVecX, &targetVecX, &targetVecY, &targetVecZ);
	length = fabs(D3DXVec3Dot(&interval, &thisNormalizeVecX));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//A.e2
	thisRadius = D3DXVec3Length(&thisVecY);
	targetRadius = LenSegOnSeparateAxis(&thisNormalizeVecY, &targetVecX, &targetVecY, &targetVecZ);
	length = fabs(D3DXVec3Dot(&interval, &thisNormalizeVecY));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//A.e3
	thisRadius = D3DXVec3Length(&thisVecZ);
	targetRadius = LenSegOnSeparateAxis(&thisNormalizeVecZ, &targetVecX, &targetVecY, &targetVecZ);
	length = fabs(D3DXVec3Dot(&interval, &thisNormalizeVecZ));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//B.e1
	thisRadius = D3DXVec3Length(&targetVecX);
	targetRadius = LenSegOnSeparateAxis(&targetNormalizeVecX, &thisVecX, &thisVecY, &thisVecZ);
	length = fabs(D3DXVec3Dot(&interval, &targetNormalizeVecX));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//B.e2
	thisRadius = D3DXVec3Length(&targetVecY);
	targetRadius = LenSegOnSeparateAxis(&targetNormalizeVecY, &thisVecX, &thisVecY, &thisVecZ);
	length = fabs(D3DXVec3Dot(&interval, &targetNormalizeVecY));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//B.e3
	thisRadius = D3DXVec3Length(&targetVecZ);
	targetRadius = LenSegOnSeparateAxis(&targetNormalizeVecZ, &thisVecX, &thisVecY, &thisVecZ);
	length = fabs(D3DXVec3Dot(&interval, &targetNormalizeVecZ));
	if (length > thisRadius + targetRadius)
	{
		return false;
	}

	//C11
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecX, &targetNormalizeVecX);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecY, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecY, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C12
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecX, &targetNormalizeVecY);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecY, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C13
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecX, &targetNormalizeVecZ);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecY, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecY);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C21
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecY, &targetNormalizeVecX);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecY, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C22
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecY, &targetNormalizeVecY);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C23
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecY, &targetNormalizeVecZ);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecZ);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecY);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C31
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecZ, &targetNormalizeVecX);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecY);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecY, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C32
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecZ, &targetNormalizeVecY);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecY);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecZ);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//C33
	{
		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &thisNormalizeVecZ, &targetNormalizeVecZ);
		thisRadius = LenSegOnSeparateAxis(&Cross, &thisVecX, &thisVecY);
		targetRadius = LenSegOnSeparateAxis(&Cross, &targetVecX, &targetVecY);
		length = fabs(D3DXVec3Dot(&interval, &Cross));
		if (length > thisRadius + targetRadius)
		{
			return false;
		}
	}

	//CDebugProc::Print("��HIT��\n");
	return true;
}

//-----------------------------------------------------------------------------
// OBB��OBB�̓����蔻��(�����߂����܂�)
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
bool CObjectX::OBBAndOBB(CObjectX* inObjectX, D3DXVECTOR3* outPos)
{
	if (!inObjectX->IsCollision())
	{
		return false;
	}

	static bool debug = false;

	if (debug)CDebugProc::Print("----------------------------------------------\n");

	// �t�s��
	D3DXMATRIX mtxThisRot = InverseMatrixConversion(m_mtxRot);

	// �t�s��
	D3DXMATRIX targetMtxRot = InverseMatrixConversion(inObjectX->GetMtxRot());

	// ���g�ƃ^�[�Q�b�g�̌���������
	D3DXMATRIX mtx = mtxThisRot * inObjectX->GetMtxRot();

	// ��Βl
	D3DXMATRIX mtxAds;
	mtxAds._11 = fabsf(mtx._11);
	mtxAds._12 = fabsf(mtx._21);
	mtxAds._13 = fabsf(mtx._31);
	mtxAds._21 = fabsf(mtx._12);
	mtxAds._22 = fabsf(mtx._22);
	mtxAds._23 = fabsf(mtx._32);
	mtxAds._31 = fabsf(mtx._13);
	mtxAds._32 = fabsf(mtx._23);
	mtxAds._33 = fabsf(mtx._33);

	const float etc = 1.0e-6f;	// �߂����Ꮼ���Ȑ���(100������1)
	bool parallel = false;

	if (mtxAds._11 + etc >= 1.0f ||
		mtxAds._12 + etc >= 1.0f || 
		mtxAds._13 + etc >= 1.0f || 
		mtxAds._21 + etc >= 1.0f || 
		mtxAds._22 + etc >= 1.0f || 
		mtxAds._23 + etc >= 1.0f || 
		mtxAds._31 + etc >= 1.0f || 
		mtxAds._32 + etc >= 1.0f || 
		mtxAds._33 + etc >= 1.0f)
	{
		parallel = true;
	}

	D3DXVECTOR3 interval;
	D3DXVECTOR3 pos = (GetPos() - inObjectX->GetPos());
	D3DXVec3TransformCoord(&interval, &pos, &mtxThisRot);	// m_mtxRot�ł͂Ȃ��t�s��G

	if (debug)CDebugProc::Print("pos : %.2f,%.2f,%.2f \n", pos.x, pos.y, pos.z);
	if (debug)D3DXVec3Length(&interval) <= 50.0f ? CDebugProc::Print("��interval�� : %.2f,%.2f,%.2f \n", interval.x, interval.y, interval.z) : CDebugProc::Print("interval : %.2f,%.2f,%.2f \n", interval.x, interval.y, interval.z);

	if (debug)CDebugProc::Print("\nm_mtxRot\n");
	if (debug)CDebugProc::Print(" 1 : %.2f,%.2f,%.2f     ", m_mtxRot._11, m_mtxRot._12, m_mtxRot._13);
	if (debug)CDebugProc::Print(" 2 : %.2f,%.2f,%.2f     ", m_mtxRot._21, m_mtxRot._22, m_mtxRot._23);
	if (debug)CDebugProc::Print(" 3 : %.2f,%.2f,%.2f     ", m_mtxRot._31, m_mtxRot._32, m_mtxRot._33);
	if (debug)CDebugProc::Print("\nmtxThisRot\n");
	if (debug)CDebugProc::Print(" 1 : %.2f,%.2f,%.2f     ", mtxThisRot._11, mtxThisRot._12, mtxThisRot._13);
	if (debug)CDebugProc::Print(" 2 : %.2f,%.2f,%.2f     ", mtxThisRot._21, mtxThisRot._22, mtxThisRot._23);
	if (debug)CDebugProc::Print(" 3 : %.2f,%.2f,%.2f     ", mtxThisRot._31, mtxThisRot._32, mtxThisRot._33);
	if (debug)CDebugProc::Print("\ninObjectX->GetMtxRot()\n");
	if (debug)CDebugProc::Print(" 1 : %.2f,%.2f,%.2f     ", inObjectX->GetMtxRot()._11, inObjectX->GetMtxRot()._12, inObjectX->GetMtxRot()._13);
	if (debug)CDebugProc::Print(" 2 : %.2f,%.2f,%.2f     ", inObjectX->GetMtxRot()._21, inObjectX->GetMtxRot()._22, inObjectX->GetMtxRot()._23);
	if (debug)CDebugProc::Print(" 3 : %.2f,%.2f,%.2f     ", inObjectX->GetMtxRot()._31, inObjectX->GetMtxRot()._32, inObjectX->GetMtxRot()._33);
	if (debug)CDebugProc::Print("\nmtx\n");
	if (debug)CDebugProc::Print(" 1 : %.2f,%.2f,%.2f     ", mtx._11, mtx._12, mtx._13);
	if (debug)CDebugProc::Print(" 2 : %.2f,%.2f,%.2f     ", mtx._21, mtx._22, mtx._23);
	if (debug)CDebugProc::Print(" 3 : %.2f,%.2f,%.2f     ", mtx._31, mtx._32, mtx._33);
	if (debug)CDebugProc::Print("\n\n");

	//if (debug)CDebugProc::Print("mtxAds : %.2f,%.2f,%.2f   %.2f,%.2f,%.2f  %.2f,%.2f,%.2f�� ", mtxAds._11, mtxAds._12, mtxAds._13, mtxAds._21, mtxAds._22, mtxAds._23, mtxAds._31, mtxAds._32, mtxAds._33);
	//if (debug)CDebugProc::Print("interval : %.2f,%.2f,%.2f ��", interval.x, interval.y, interval.z);

	float s;

	D3DXVECTOR3 thisScale = m_MaxVtx;
	{
		//D3DXVECTOR3 scale = m_scale * 0.5f;
		//thisScale.x *= scale.x;
		//thisScale.y *= scale.y;
		//thisScale.z *= scale.z;
		if (debug)CDebugProc::Print("thisScale : %.2f,%.2f,%.2f ��", thisScale.x, thisScale.y, thisScale.z);
	}

	D3DXVECTOR3 targetScale = inObjectX->GetMaxVtx();
	{
		//D3DXVECTOR3 scale = inObjectX->GetScale() * 0.5f;
		//if (debug)CDebugProc::Print("\n");
		//if (debug)CDebugProc::Print("scale : %.2f,%.2f,%.2f ��", inObjectX->GetScale().x, inObjectX->GetScale().y, inObjectX->GetScale().z);
		//if (debug)CDebugProc::Print("targetScale : %.2f,%.2f,%.2f \n", targetScale.x, targetScale.y, targetScale.z);
		//targetScale.x *= scale.x;
		//targetScale.y *= scale.y;
		//targetScale.z *= scale.z;
		//if (debug)CDebugProc::Print("scale : %.2f,%.2f,%.2f ��", scale.x, scale.y, scale.z);
		if (debug)CDebugProc::Print("targetScale : %.2f,%.2f,%.2f \n", targetScale.x, targetScale.y, targetScale.z);
	}

	float aMax = -FLT_MAX;
	float bMax = -FLT_MAX;
	float eMax = -FLT_MAX;
	int aAxis = ~0;
	int bAxis = ~0;
	int eAxis = ~0;
	D3DXVECTOR3 nA;
	D3DXVECTOR3 nB;
	D3DXVECTOR3 nE;

	auto TrackFaceAxis = [](int* axis,int nCnt,float s,float* max,const D3DXVECTOR3& normal, D3DXVECTOR3* axisNormal)
	{
		if (s > 0.0f)
		{
			return true;
		}

		if (s > *max)
		{
			*max = s;
			*axis = nCnt;
			*axisNormal = normal;
		}
		return false;
	};

	//A.e1
	s = fabs(interval.x) - (thisScale.x + D3DXVec3Dot(&D3DXVECTOR3(mtxAds._11, mtxAds._12, mtxAds._13), &targetScale));
	if (TrackFaceAxis(&aAxis, 0, s, &aMax, D3DXVECTOR3(mtxThisRot._11, mtxThisRot._21, mtxThisRot._31), &nA))
	{
		if (debug)CDebugProc::Print("��A.e1\n");
		return false;
	}

	//A.e2
	s = fabs(interval.y) - (thisScale.y + D3DXVec3Dot(&D3DXVECTOR3(mtxAds._21, mtxAds._22, mtxAds._23), &targetScale));
	if (TrackFaceAxis(&aAxis, 1, s, &aMax, D3DXVECTOR3(mtxThisRot._12, mtxThisRot._22, mtxThisRot._32), &nA))
	{
		if (debug)CDebugProc::Print("s : %.2f", s);
		if (debug)CDebugProc::Print("�� A.e2\n");
		return false;
	}

	//A.e3
	s = fabs(interval.z) - (thisScale.z + D3DXVec3Dot(&D3DXVECTOR3(mtxAds._31, mtxAds._32, mtxAds._33), &targetScale));
	if (TrackFaceAxis(&aAxis, 2, s, &aMax, D3DXVECTOR3(mtxThisRot._13, mtxThisRot._23, mtxThisRot._33), &nA))
	{
		if (debug)CDebugProc::Print("s : %.2f", s);
		if (debug)CDebugProc::Print("�� A.e3\n");
		return false;
	}

	//B.e1
	s = fabs(D3DXVec3Dot(&interval, &D3DXVECTOR3(mtx._11, mtx._21, mtx._31))) - (targetScale.x + D3DXVec3Dot(&D3DXVECTOR3(mtxAds._11, mtxAds._21, mtxAds._31), &thisScale));
	if (TrackFaceAxis(&bAxis, 3, s, &bMax, D3DXVECTOR3(targetMtxRot._11, targetMtxRot._21, targetMtxRot._31), &nB))
	{
		if (debug)CDebugProc::Print("s : %.2f", s);
		if (debug)CDebugProc::Print("�� B.e1\n");
		return false;
	}

	//B.e2
	s = fabs(D3DXVec3Dot(&interval, &D3DXVECTOR3(mtx._12, mtx._22, mtx._32))) - (targetScale.y + D3DXVec3Dot(&D3DXVECTOR3(mtxAds._12, mtxAds._22, mtxAds._32), &thisScale));
	if (TrackFaceAxis(&bAxis, 4, s, &bMax, D3DXVECTOR3(targetMtxRot._12, targetMtxRot._22, targetMtxRot._32), &nB))
	{
		if (debug)CDebugProc::Print("s : %.2f", s);
		if (debug)CDebugProc::Print("�� B.e2\n");
		return false;
	}

	//B.e3
	s = fabs(D3DXVec3Dot(&interval, &D3DXVECTOR3(mtx._13, mtx._23, mtx._33))) - (targetScale.z + D3DXVec3Dot(&D3DXVECTOR3(mtxAds._13, mtxAds._23, mtxAds._33),&thisScale));
	if (TrackFaceAxis(&bAxis, 5, s, &bMax, D3DXVECTOR3(targetMtxRot._13, targetMtxRot._23, targetMtxRot._33), &nB))
	{
		if (debug)CDebugProc::Print("s : %.2f", s);
		if (debug)CDebugProc::Print("��b : %.2f", fabs(D3DXVec3Dot(&interval, &D3DXVECTOR3(mtx._13, mtx._23, mtx._33))));
		if (debug)CDebugProc::Print("��a : %.2f", targetScale.z + D3DXVec3Dot(&D3DXVECTOR3(mtxAds._13, mtxAds._23, mtxAds._33), &thisScale));
		if (debug)CDebugProc::Print("��a_1 : %.2f", targetScale.z);
		if (debug)CDebugProc::Print("��a_2 : %.2f", D3DXVec3Dot(&D3DXVECTOR3(mtxAds._13, mtxAds._23, mtxAds._33), &thisScale));
		if (debug)CDebugProc::Print("�� B.e3\n");
		return false;
	}

	// ���s�ł͂Ȃ��ꍇ
	if (!parallel)
	{
		float thisRadius;
		float targetRadius;

		auto TrackEdgeAxis = [](int* axis, int nCnt, float s, float* max, const D3DXVECTOR3& normal, D3DXVECTOR3* axisNormal)
		{
			if (s > 0.0f)
			{
				return true;
			}

			float i = 1.0f / D3DXVec3Length(&normal);
			s *= i;

			if (s > *max)
			{
				*max = s;
				*axis = nCnt;
				*axisNormal = normal * i;
			}

			return false;
		};

		//C11
		thisRadius = thisScale.y * mtxAds._31 + thisScale.z * mtxAds._21;
		targetRadius = targetScale.y * mtxAds._13 + targetScale.z * mtxAds._12;
		s = fabs(interval.z * mtx._21 - interval.y * mtx._31) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 6, s, &eMax, D3DXVECTOR3(0.0f, -mtx._31, mtx._21), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C11\n");
			return false;
		}

		//C12
		thisRadius = thisScale.y * mtxAds._32 + thisScale.z * mtxAds._22;
		targetRadius = targetScale.x * mtxAds._13 + targetScale.z * mtxAds._11;
		s = fabs(interval.z * mtx._22 - interval.y * mtx._32) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 7, s, &eMax, D3DXVECTOR3(0.0f, -mtx._32, mtx._22), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C12\n");
			return false;
		}

		//C13
		thisRadius = thisScale.y * mtxAds._33 + thisScale.z * mtxAds._23;
		targetRadius = targetScale.x * mtxAds._12 + targetScale.y * mtxAds._11;
		s = fabs(interval.z * mtx._23 - interval.y * mtx._33) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 8, s, &eMax, D3DXVECTOR3(0.0f, -mtx._33, mtx._23), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C13\n");
			return false;
		}

		//C21
		thisRadius = thisScale.x * mtxAds._31 + thisScale.z * mtxAds._11;
		targetRadius = targetScale.y * mtxAds._23 + targetScale.z * mtxAds._22;
		s = fabs(interval.x * mtx._31 - interval.z * mtx._11) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 9, s, &eMax, D3DXVECTOR3(mtx._31, 0.0f, -mtx._11), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f�� ", s);
			if (debug)CDebugProc::Print("a : %.2f�� ", fabs(interval.x * mtx._31 - interval.z * mtx._11));
			if (debug)CDebugProc::Print("Scale : %.2f,%.2f�� ", thisScale.x, thisScale.z);
			if (debug)CDebugProc::Print("this : %.2f�� ", thisRadius);
			if (debug)CDebugProc::Print("target : %.2f�� ", targetRadius);
			if (debug)CDebugProc::Print("C21\n");
			return false;
		}

		//C22
		thisRadius = thisScale.x * mtxAds._32 + thisScale.z * mtxAds._12;
		targetRadius = targetScale.x * mtxAds._23 + targetScale.z * mtxAds._21;
		s = fabs(interval.x * mtx._32 - interval.z * mtx._12) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 10, s, &eMax, D3DXVECTOR3(mtx._32, 0.0f, -mtx._12), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C22\n");
			return false;
		}

		//C23
		thisRadius = thisScale.x * mtxAds._33 + thisScale.z * mtxAds._13;
		targetRadius = targetScale.x * mtxAds._22 + targetScale.y * mtxAds._21;
		s = fabs(interval.x * mtx._33 - interval.z * mtx._13) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 11, s, &eMax, D3DXVECTOR3(mtx._33, 0.0f, -mtx._13), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C23\n");
			return false;
		}

		//C31
		thisRadius = thisScale.x * mtxAds._21 + thisScale.y * mtxAds._11;
		targetRadius = targetScale.y * mtxAds._33 + targetScale.z * mtxAds._32;
		s = fabs(interval.y * mtx._11 - interval.x * mtx._21) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 12, s, &eMax, D3DXVECTOR3(-mtx._21, mtx._11, 0.0f), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C31\n");
			return false;
		}

		//C32
		thisRadius = thisScale.x * mtxAds._22 + thisScale.y * mtxAds._12;
		targetRadius = targetScale.x * mtxAds._33 + targetScale.z * mtxAds._31;
		s = fabs(interval.y * mtx._12 - interval.x * mtx._22) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 13, s, &eMax, D3DXVECTOR3(-mtx._22, mtx._12, 0.0f), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C32\n");
			return false;
		}

		//C33
		thisRadius = thisScale.x * mtxAds._23 + thisScale.y * mtxAds._13;
		targetRadius = targetScale.x * mtxAds._32 + targetScale.y * mtxAds._31;
		s = fabs(interval.y * mtx._13 - interval.x * mtx._23) - (thisRadius + targetRadius);
		if (TrackEdgeAxis(&eAxis, 14, s, &eMax, D3DXVECTOR3(-mtx._23, mtx._13, 0.0f), &nE))
		{
			if (debug)CDebugProc::Print("s : %.2f", s);
			if (debug)CDebugProc::Print("�� C33\n");
			return false;
		}
	}

	if (debug)CDebugProc::Print("s : %.2f", s);
	if (debug)CDebugProc::Print("�� ��Hit��\n");

	/* �����܂Œʂ�ΐڐG���Ă� */

	// Artificial axis bias to improve frame coherence
	const float kRelTol = 0.95f;
	const float kAbsTol = 0.01f;
	int axis;
	float sMax;
	D3DXVECTOR3 n;
	
	float faceMax;
	if (aMax > bMax)
	{
		faceMax = aMax;
	}
	else
	{
		faceMax = bMax;
	}
	
	if (kRelTol * eMax > faceMax + kAbsTol)
	{
		axis = eAxis;
		sMax = eMax;
		n = nE;
	}
	else
	{
		if (kRelTol * bMax > aMax + kAbsTol)
		{
			axis = bAxis;
			sMax = bMax;
			n = nB;
		}
		else
		{
			axis = aAxis;
			sMax = aMax;
			n = nA;
		}
	}
	
	if (D3DXVec3Dot(&n, &(GetPos() - inObjectX->GetPos())) < 0.0f)
	{
		n = -n;
	}
	
	if (axis == ~0)
	{
		assert(false);
		return true;
	}
	
	if (debug)CDebugProc::Print("����: %d \n", axis);

	if (axis < 6)
	{
		D3DXVECTOR3 rtx_pos;
		D3DXVECTOR3 itx_pos;
		D3DXMATRIX rtx_mtxRot;
		D3DXMATRIX itx_mtxRot;
		D3DXVECTOR3 eR;
		D3DXVECTOR3 eI;
		bool flip;
	
		if (axis < 3)
		{
			rtx_pos = m_pos;
			itx_pos = inObjectX->GetPos();
			rtx_mtxRot = m_mtxRot;
			itx_mtxRot = inObjectX->GetMtxRot();
			eR = thisScale;
			eI = targetScale;
			flip = false;
		}
		else
		{
			rtx_pos = inObjectX->GetPos();
			itx_pos = m_pos;
			rtx_mtxRot = inObjectX->GetMtxRot();
			itx_mtxRot = m_mtxRot;
			eR = targetScale;
			eI = thisScale;
			flip = true;
			n = -n;
		}
	
		// Compute reference and incident edge information necessary for clipping
		ClipVertex incident[4];
		ComputeIncidentFace(itx_pos, itx_mtxRot, eI, n, incident);

		char clipEdges[4];
		D3DXMATRIX basis;
		D3DXVECTOR3 e;
		ComputeReferenceEdgesAndBasis(eR, rtx_pos, rtx_mtxRot, n, axis, clipEdges, &basis, &e);
	
		// Clip the incident face against the reference face side planes
		ClipVertex out[8];
		float depths[8];
		int outNum;
		outNum = Clip(rtx_pos, e, clipEdges, basis, incident, out, depths);
	
		if (outNum)
		{
			//m->contactCount = outNum;
			//m->normal = flip ? -n : n;
	
			if (debug)CDebugProc::Print("���� : %.2f,%.2f,%.2f \n", flip ? -n.x : n.x, flip ? -n.y : n.y, flip ? -n.z : n.z);

			for (int i = 0; i < outNum; ++i)
			{
				if (debug)CDebugProc::Print("�߂��ʒu�H : %.2f,%.2f,%.2f \n", out[i].v.x, out[i].v.y, out[i].v.z);
				if (debug)CDebugProc::Print("�ђʂ��Ă鋗���H : %.2f \n", depths[i]);
				//q3Contact* c = m->contacts + i;
	
				//FeaturePair pair = out[i].f;
	
				//if (flip)
				//{
				//	std::swap(pair.inI, pair.inR);
				//	std::swap(pair.outI, pair.outR);
				//}
	
				//c->fp = out[i].f;
				//c->position = out[i].v;
				//c->penetration = depths[i];
			}
		}
	}
	else
	{
		D3DXVECTOR3 vector = n;
		n.x = m_mtxRot._11 * vector.x + m_mtxRot._12 * vector.y + m_mtxRot._13 * vector.z;
		n.y = m_mtxRot._21 * vector.x + m_mtxRot._22 * vector.y + m_mtxRot._23 * vector.z;
		n.z = m_mtxRot._31 * vector.x + m_mtxRot._32 * vector.y + m_mtxRot._33 * vector.z;

		D3DXVECTOR3 dist = inObjectX->GetPos() - m_pos;
		if (D3DXVec3Dot(&n, &dist) < 0.0f)
		{
			n = -n;
		}

		D3DXVECTOR3 PA, QA;
		D3DXVECTOR3 PB, QB;

		auto SupportEdge = [](const D3DXVECTOR3& tx_pos, const D3DXMATRIX& tx_rot, const D3DXVECTOR3& e, D3DXVECTOR3 n, D3DXVECTOR3* aOut, D3DXVECTOR3* bOut)
		{
			D3DXVECTOR3 vector = n;
			n.x = tx_rot._11 * vector.x + tx_rot._21 * vector.y + tx_rot._31 * vector.z;
			n.y = tx_rot._12 * vector.x + tx_rot._22 * vector.y + tx_rot._32 * vector.z;
			n.z = tx_rot._13 * vector.x + tx_rot._23 * vector.y + tx_rot._33 * vector.z;

			D3DXVECTOR3 absN;
			absN.x = fabs(n.x);
			absN.y = fabs(n.y);
			absN.z = fabs(n.z);
			D3DXVECTOR3 a, b;

			// x > y
			if (absN.x > absN.y)
			{
				// x > y > z
				if (absN.y > absN.z)
				{
					a = D3DXVECTOR3(e.x, e.y, e.z);
					b = D3DXVECTOR3(e.x, e.y, -e.z);
				}

				// x > z > y || z > x > y
				else
				{
					a = D3DXVECTOR3(e.x, e.y, e.z);
					b = D3DXVECTOR3(e.x, -e.y, e.z);
				}
			}

			// y > x
			else
			{
				// y > x > z
				if (absN.x > absN.z)
				{
					a = D3DXVECTOR3(e.x, e.y, e.z);
					b = D3DXVECTOR3(e.x, e.y, -e.z);
				}

				// z > y > x || y > z > x
				else
				{
					a = D3DXVECTOR3(e.x, e.y, e.z);
					b = D3DXVECTOR3(-e.x, e.y, e.z);
				}
			}
			
			float signx;;
			if (n.x >= 0.0f)
			{
				signx = 1.0f;
			}
			else
			{
				signx = -1.0f;
			}

			float signy;
			if (n.y >= 0.0f)
			{
				signy = 1.0f;
			}
			else
			{
				signy = -1.0f;
			}

			float signz;
			if (n.z >= 0.0f)
			{
				signz = 1.0f;
			}
			else
			{
				signz = -1.0f;
			}

			a.x *= signx;
			a.y *= signy;
			a.z *= signz;
			b.x *= signx;
			b.y *= signy;
			b.z *= signz;

			aOut->x = tx_rot._11 * a.x + tx_rot._12 * a.y + tx_rot._13 * a.z;
			aOut->y = tx_rot._21 * a.x + tx_rot._22 * a.y + tx_rot._23 * a.z;
			aOut->z = tx_rot._31 * a.x + tx_rot._32 * a.y + tx_rot._33 * a.z;
			*aOut += tx_pos;

			bOut->x = tx_rot._11 * b.x + tx_rot._12 * b.y + tx_rot._13 * b.z;
			bOut->y = tx_rot._21 * b.x + tx_rot._22 * b.y + tx_rot._23 * b.z;
			bOut->z = tx_rot._31 * b.x + tx_rot._32 * b.y + tx_rot._33 * b.z;
			*bOut += tx_pos;
		};

		SupportEdge(m_pos, m_mtxRot, thisScale, n, &PA, &QA);
		SupportEdge(inObjectX->GetPos(), inObjectX->GetMtxRot(), targetScale, -n, &PB, &QB);

		D3DXVECTOR3 CA, CB;
		{
			D3DXVECTOR3 DA = QA - PA;
			D3DXVECTOR3 DB = QB - PB;
			D3DXVECTOR3 r = PA - PB;
			float a = D3DXVec3Dot(&DA, &DA);
			float e = D3DXVec3Dot(&DB, &DB);
			float f = D3DXVec3Dot(&DB, &r);
			float c = D3DXVec3Dot(&DA, &r);

			float b = D3DXVec3Dot(&DA, &DB);
			float denom = a * e - b * b;

			float TA = (b * f - c * e) / denom;
			float TB = (b * TA + f) / e;

			CA = PA + DA * TA;
			CB = PB + DB * TB;
		}

		CDebugProc::Print("�߂��ʒu : %.2f,%.2f,%.2f\n", (CA.x + CB.x) * 0.5f, (CA.y + CB.y) * 0.5f, (CA.z + CB.z) * 0.5f);
		CDebugProc::Print("�ђʂ��Ă鋗���H : %.2f \n", sMax);
		//m->normal = n;
		//m->contactCount = 1;
	
		//q3Contact* c = m->contacts;
		//FeaturePair pair;
		//pair.key = axis;
		//c->fp = pair;
		//c->penetration = sMax;
		//c->position = (CA + CB) * 0.5f;
	}

	return true;
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

//-----------------------------------------------------------------------------
// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
// Author : Yuda Kaito
// �����F������Sep�͕W��������Ă��邱��
//-----------------------------------------------------------------------------
float CObjectX::LenSegOnSeparateAxis(D3DXVECTOR3 * Sep, D3DXVECTOR3 * e1, D3DXVECTOR3 * e2, D3DXVECTOR3 * e3)
{
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0.0f;
	return r1 + r2 + r3;
}

void CObjectX::ComputeIncidentFace(const D3DXVECTOR3 & itx_pos, const D3DXMATRIX & itx_mtxRot, const D3DXVECTOR3 & e, D3DXVECTOR3 n, ClipVertex * out)
{
	D3DXVECTOR3 normal = n;
	n.x = itx_mtxRot._11 * normal.x + itx_mtxRot._21 * normal.y + itx_mtxRot._31 * normal.z;
	n.y = itx_mtxRot._12 * normal.x + itx_mtxRot._22 * normal.y + itx_mtxRot._32 * normal.z;
	n.z = itx_mtxRot._13 * normal.x + itx_mtxRot._23 * normal.y + itx_mtxRot._33 * normal.z;

	D3DXVECTOR3 absN;
	absN.x = fabs(n.x);
	absN.y = fabs(n.y);
	absN.z = fabs(n.z);

	if (absN.x > absN.y && absN.x > absN.z)
	{
		if (n.x > 0.0f)
		{
			out[0].v = D3DXVECTOR3(e.x, e.y, -e.z);
			out[1].v = D3DXVECTOR3(e.x, e.y, e.z);
			out[2].v = D3DXVECTOR3(e.x, -e.y, e.z);
			out[3].v = D3DXVECTOR3(e.x, -e.y, -e.z);

			out[0].f.ri.inI = 9;
			out[0].f.ri.outI = 1;
			out[1].f.ri.inI = 1;
			out[1].f.ri.outI = 8;
			out[2].f.ri.inI = 8;
			out[2].f.ri.outI = 7;
			out[3].f.ri.inI = 7;
			out[3].f.ri.outI = 9;
		}

		else
		{
			out[0].v = D3DXVECTOR3(-e.x, -e.y, e.z);
			out[1].v = D3DXVECTOR3(-e.x, e.y, e.z);
			out[2].v = D3DXVECTOR3(-e.x, e.y, -e.z);
			out[3].v = D3DXVECTOR3(-e.x, -e.y, -e.z);

			out[0].f.ri.inI = 5;
			out[0].f.ri.outI = 11;
			out[1].f.ri.inI = 11;
			out[1].f.ri.outI = 3;
			out[2].f.ri.inI = 3;
			out[2].f.ri.outI = 10;
			out[3].f.ri.inI = 10;
			out[3].f.ri.outI = 5;
		}
	}

	else if (absN.y > absN.x && absN.y > absN.z)
	{
		if (n.y > 0.0f)
		{
			out[0].v = D3DXVECTOR3(-e.x, e.y, e.z);
			out[1].v = D3DXVECTOR3(e.x, e.y, e.z);
			out[2].v = D3DXVECTOR3(e.x, e.y, -e.z);
			out[3].v = D3DXVECTOR3(-e.x, e.y, -e.z);

			out[0].f.ri.inI = 3;
			out[0].f.ri.outI = 0;
			out[1].f.ri.inI = 0;
			out[1].f.ri.outI = 1;
			out[2].f.ri.inI = 1;
			out[2].f.ri.outI = 2;
			out[3].f.ri.inI = 2;
			out[3].f.ri.outI = 3;
		}

		else
		{
			out[0].v = D3DXVECTOR3(e.x, -e.y, e.z);
			out[1].v = D3DXVECTOR3(-e.x, -e.y, e.z);
			out[2].v = D3DXVECTOR3(-e.x, -e.y, -e.z);
			out[3].v = D3DXVECTOR3(e.x, -e.y, -e.z);

			out[0].f.ri.inI = 7;
			out[0].f.ri.outI = 4;
			out[1].f.ri.inI = 4;
			out[1].f.ri.outI = 5;
			out[2].f.ri.inI = 5;
			out[2].f.ri.outI = 6;
			out[3].f.ri.inI = 5;
			out[3].f.ri.outI = 6;
		}
	}

	else
	{
		if (n.z > 0.0f)
		{
			out[0].v = D3DXVECTOR3(-e.x, e.y, e.z);
			out[1].v = D3DXVECTOR3(-e.x, -e.y, e.z);
			out[2].v = D3DXVECTOR3(e.x, -e.y, e.z);
			out[3].v = D3DXVECTOR3(e.x, e.y, e.z);

			out[0].f.ri.inI = 0;
			out[0].f.ri.outI = 11;
			out[1].f.ri.inI = 11;
			out[1].f.ri.outI = 4;
			out[2].f.ri.inI = 4;
			out[2].f.ri.outI = 8;
			out[3].f.ri.inI = 8;
			out[3].f.ri.outI = 0;
		}

		else
		{
			out[0].v = D3DXVECTOR3(e.x, -e.y, -e.z);
			out[1].v = D3DXVECTOR3(-e.x, -e.y, -e.z);
			out[2].v = D3DXVECTOR3(-e.x, e.y, -e.z);
			out[3].v = D3DXVECTOR3(e.x, e.y, -e.z);

			out[0].f.ri.inI = 9;
			out[0].f.ri.outI = 6;
			out[1].f.ri.inI = 6;
			out[1].f.ri.outI = 10;
			out[2].f.ri.inI = 10;
			out[2].f.ri.outI = 2;
			out[3].f.ri.inI = 2;
			out[3].f.ri.outI = 9;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		D3DXVECTOR3 vector = out[i].v + itx_pos;
		out[i].v.x = itx_mtxRot._11 * vector.x + itx_mtxRot._12 * vector.y + itx_mtxRot._13 * vector.z;
		out[i].v.y = itx_mtxRot._21 * vector.x + itx_mtxRot._22 * vector.y + itx_mtxRot._23 * vector.z;
		out[i].v.z = itx_mtxRot._31 * vector.x + itx_mtxRot._32 * vector.y + itx_mtxRot._33 * vector.z;
	}
}

void CObjectX::ComputeReferenceEdgesAndBasis(const D3DXVECTOR3 & eR, const D3DXVECTOR3 & rtx_pos, const D3DXMATRIX & rtx_mtxRot, D3DXVECTOR3 n, int axis, char * out, D3DXMATRIX * basis, D3DXVECTOR3 * e)
{
	D3DXVECTOR3 normal = n;
	n.x = rtx_mtxRot._11 * normal.x + rtx_mtxRot._21 * normal.y + rtx_mtxRot._31 * normal.z;
	n.y = rtx_mtxRot._12 * normal.x + rtx_mtxRot._22 * normal.y + rtx_mtxRot._32 * normal.z;
	n.z = rtx_mtxRot._13 * normal.x + rtx_mtxRot._23 * normal.y + rtx_mtxRot._33 * normal.z;

	if (axis >= 3)
		axis -= 3;

	switch (axis)
	{
	case 0:
		if (n.x > 0.0f)
		{
			out[0] = 1;
			out[1] = 8;
			out[2] = 7;
			out[3] = 9;

			*e = D3DXVECTOR3(eR.y, eR.z, eR.x);

			basis->_11 = rtx_mtxRot._12;
			basis->_21 = rtx_mtxRot._22;
			basis->_31 = rtx_mtxRot._32;

			basis->_12 = rtx_mtxRot._13;
			basis->_22 = rtx_mtxRot._23;
			basis->_32 = rtx_mtxRot._33;

			basis->_13 = rtx_mtxRot._11;
			basis->_23 = rtx_mtxRot._21;
			basis->_33 = rtx_mtxRot._31;
		}

		else
		{
			out[0] = 11;
			out[1] = 3;
			out[2] = 10;
			out[3] = 5;

			*e = D3DXVECTOR3(eR.z, eR.y, eR.x);

			basis->_11 = rtx_mtxRot._13;
			basis->_21 = rtx_mtxRot._23;
			basis->_31 = rtx_mtxRot._33;

			basis->_12 = rtx_mtxRot._12;
			basis->_22 = rtx_mtxRot._22;
			basis->_32 = rtx_mtxRot._32;

			basis->_13 = -rtx_mtxRot._11;
			basis->_23 = -rtx_mtxRot._21;
			basis->_33 = -rtx_mtxRot._31;
		}
		break;

	case 1:
		if (n.y > 0.0f)
		{
			out[0] = 0;
			out[1] = 1;
			out[2] = 2;
			out[3] = 3;

			*e = D3DXVECTOR3(eR.z, eR.x, eR.y);

			basis->_11 = rtx_mtxRot._13;
			basis->_21 = rtx_mtxRot._23;
			basis->_31 = rtx_mtxRot._33;

			basis->_12 = rtx_mtxRot._11;
			basis->_22 = rtx_mtxRot._21;
			basis->_32 = rtx_mtxRot._31;

			basis->_13 = rtx_mtxRot._12;
			basis->_23 = rtx_mtxRot._22;
			basis->_33 = rtx_mtxRot._32;
		}

		else
		{
			out[0] = 4;
			out[1] = 5;
			out[2] = 6;
			out[3] = 7;

			*e = D3DXVECTOR3(eR.z, eR.x, eR.y);

			basis->_11 = rtx_mtxRot._13;
			basis->_21 = rtx_mtxRot._23;
			basis->_31 = rtx_mtxRot._33;

			basis->_12 = -rtx_mtxRot._11;
			basis->_22 = -rtx_mtxRot._21;
			basis->_32 = -rtx_mtxRot._31;

			basis->_13 = -rtx_mtxRot._12;
			basis->_23 = -rtx_mtxRot._22;
			basis->_33 = -rtx_mtxRot._32;
		}
		break;

	case 2:
		if (n.z > 0.0f)
		{
			out[0] = 11;
			out[1] = 4;
			out[2] = 8;
			out[3] = 0;

			*e = D3DXVECTOR3(eR.y, eR.x, eR.z);

			basis->_11 = -rtx_mtxRot._12;
			basis->_21 = -rtx_mtxRot._22;
			basis->_31 = -rtx_mtxRot._32;

			basis->_12 = rtx_mtxRot._11;
			basis->_22 = rtx_mtxRot._21;
			basis->_32 = rtx_mtxRot._31;

			basis->_13 = rtx_mtxRot._13;
			basis->_23 = rtx_mtxRot._23;
			basis->_33 = rtx_mtxRot._33;
		}

		else
		{
			out[0] = 6;
			out[1] = 10;
			out[2] = 2;
			out[3] = 9;

			*e = D3DXVECTOR3(eR.y, eR.x, eR.z);

			basis->_11 = -rtx_mtxRot._12;
			basis->_21 = -rtx_mtxRot._22;
			basis->_31 = -rtx_mtxRot._32;

			basis->_12 = -rtx_mtxRot._11;
			basis->_22 = -rtx_mtxRot._21;
			basis->_32 = -rtx_mtxRot._31;

			basis->_13 = -rtx_mtxRot._13;
			basis->_23 = -rtx_mtxRot._23;
			basis->_33 = -rtx_mtxRot._33;
		}
		break;
	}
}

int CObjectX::Clip(const D3DXVECTOR3 & rPos, const D3DXVECTOR3 & e, char * clipEdges, const D3DXMATRIX & basis, ClipVertex * incident, ClipVertex * outVerts, float * outDepths)
{
	int inCount = 4;
	int outCount;
	ClipVertex in[8];
	ClipVertex out[8];

	for (int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3 dist = incident[i].v - rPos;
		in[i].v.x = basis._11 * dist.x + basis._21 * dist.y + basis._31 * dist.z;
		in[i].v.y = basis._12 * dist.x + basis._22 * dist.y + basis._32 * dist.z;
		in[i].v.z = basis._13 * dist.x + basis._23 * dist.y + basis._33 * dist.z;
	}

	auto Orthographic = [](float sign, float e, int axis, int clipEdge, ClipVertex* in, int inCount, ClipVertex* out)
	{
		int outCount = 0;
		ClipVertex a = in[inCount - 1];

		for (int i = 0; i < inCount; ++i)
		{
			ClipVertex b = in[i];

			float da = sign * a.v[axis] - e;
			float db = sign * b.v[axis] - e;

			ClipVertex cv;

			// B
			if (((InFront(da) && InFront(db)) || On(da) || On(db)))
			{
				assert(outCount < 8);
				out[outCount++] = b;
			}

			// I
			else if (InFront(da) && Behind(db))
			{
				cv.f = b.f;
				cv.v = a.v + (b.v - a.v) * (da / (da - db));
				cv.f.ri.outR = (char)clipEdge;
				cv.f.ri.outI = 0;
				assert(outCount < 8);
				out[outCount++] = cv;
			}

			// I, B
			else if (Behind(da) && InFront(db))
			{
				cv.f = a.f;
				cv.v = a.v + (b.v - a.v) * (da / (da - db));
				cv.f.ri.inR = (char)clipEdge;
				cv.f.ri.inI = 0;
				assert(outCount < 8);
				out[outCount++] = cv;

				assert(outCount < 8);
				out[outCount++] = b;
			}

			a = b;
		}

		return outCount;
	};

	outCount = Orthographic(1.0f, e.x, 0, clipEdges[0], in, inCount, out);

	if (!outCount)
		return 0;

	inCount = Orthographic(1.0f, e.y, 1, clipEdges[1], out, outCount, in);

	if (!inCount)
		return 0;

	outCount = Orthographic(-1.0f, e.x, 0, clipEdges[2], in, inCount, out);

	if (!outCount)
		return 0;

	inCount = Orthographic(-1.0f, e.y, 1, clipEdges[3], out, outCount, in);

	// Keep incident vertices behind the reference face
	outCount = 0;
	for (int i = 0; i < inCount; ++i)
	{
		float d = in[i].v.z - e.z;

		if (d <= 0.0f)
		{
			D3DXVECTOR3 vector = in[i].v;
			outVerts[outCount].v .x = basis._11 * vector.x + basis._12 * vector.y + basis._13 * vector.z;
			outVerts[outCount].v .y = basis._21 * vector.x + basis._22 * vector.y + basis._23 * vector.z;
			outVerts[outCount].v .z = basis._31 * vector.x + basis._32 * vector.y + basis._33 * vector.z;
			outVerts[outCount].v += rPos;
			outVerts[outCount].f = in[i].f;
			outDepths[outCount++] = d;
		}
	}

	assert(outCount <= 8);

	return outCount;
}
