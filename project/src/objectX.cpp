//**************************************************************
//
// �I�u�W�F�N�gX���� [objectX.cpp]
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "objectX.h"
#include "objectX_group.h"
#include "object_polygon3d.h"
#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "utility.h"
#include "camera.h"
#include "light.h"
#include "game.h"
#include "camera_game.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CObjectX::CObjectX(CTaskGroup::EPriority nPriority) :
	CObject(nPriority),
	m_scale(1.0f, 1.0f, 1.0f),
	m_minVtxOrigin(0.0f, 0.0f, 0.0f),
	m_maxVtxOrigin(0.0f, 0.0f, 0.0f),
	m_minVtx(0.0f, 0.0f, 0.0f),
	m_maxVtx(0.0f, 0.0f, 0.0f),
	m_mesh(nullptr),
	m_buffMat(nullptr),
	m_numMat(0),
	m_parent(nullptr),
	m_isCollision(true),
	m_isHasOutLine(false),
	m_isHasShadow(false),
	m_TimeTarget(120),
	tex0(nullptr)
{
	//�I�u�W�F�N�g�̃^�C�v�Z�b�g����
	CObject::SetType(CObject::MODEL);
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxRot);
	m_materialDiffuse.clear();
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CObjectX::~CObjectX()
{
}

//--------------------------------------------------------------
// �I�u�W�F�N�g�̏�����
// Author : Yuda Kaito
// �T�v : ���������s��
//--------------------------------------------------------------
HRESULT CObjectX::Init()
{
	extern LPD3DXEFFECT pEffect;	// �V�F�[�_�[

	// ���ꂳ���E�E�E����ϗp�r���Ƃ̖��O����Ȃ��ق����ǂ������񂶂�H
	// �n���h���̏�����
	m_hTechnique = pEffect->GetTechniqueByName("Diffuse");			// �G�t�F�N�g
	m_hTexture = pEffect->GetParameterByName(NULL, "Tex");			// �e�N�X�`��
	m_hvLightDir = pEffect->GetParameterByName(NULL, "vLightDir");	// ���C�g�̕���
	m_hvDiffuse = pEffect->GetParameterByName(NULL, "vDiffuse");	// ���_�J���[
	m_hvAmbient = pEffect->GetParameterByName(NULL, "vAmbient");	// ���_�J���[
	m_hWorld = pEffect->GetParameterByName(NULL, "mWorld");			// ���[���h�s��
	m_hProj = pEffect->GetParameterByName(NULL, "mProj");			// �v���W�F�N�V�����s��
	m_hView = pEffect->GetParameterByName(NULL, "mView");			// �r���[�s��
	m_hTime = pEffect->GetParameterByName(NULL, "Test");			// ����
	m_hTimeTarget = pEffect->GetParameterByName(NULL, "TimeTarget");// �ڕW����
	m_hSize = pEffect->GetParameterByName(NULL, "mSize");		// �T�C�Y�ݒ�
	m_hRot = pEffect->GetParameterByName(NULL, "mRot");
	m_hTrans = pEffect->GetParameterByName(NULL, "mTrans");
	m_hParent = pEffect->GetParameterByName(NULL, "mParent");
	m_hScale = pEffect->GetParameterByName(NULL, "mScale");
	m_hCameraVec = pEffect->GetParameterByName(NULL, "vEyeVec");
	m_hvEyePos = pEffect->GetParameterByName(NULL, "mEyePos");

	m_TimeCnt = m_TimeTarget;

	CObject::Init();

	return S_OK;
}

//--------------------------------------------------------------
// �`��
// Author : Yuda Kaito
// �T�v : �`����s��
//--------------------------------------------------------------
void CObjectX::Draw()
{
	extern LPD3DXEFFECT pEffect;		// �V�F�[�_�[

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (pEffect == nullptr)
	{
		assert(false);
		return;
	}

	if (m_isBlackFlash && m_TimeCnt > 0)
	{
		m_TimeCnt--;
	}
	if (!m_isBlackFlash && m_TimeCnt <= m_TimeTarget)
	{
		m_TimeCnt++;
	}

	if (CInput::GetKey()->Trigger(DIK_R))
	{
		m_isBlackFlash = true;
	}
	if (CInput::GetKey()->Trigger(DIK_P))
	{
		m_isBlackFlash = false;
	}

	/* pEffect�ɒl�������Ă� */

	//-------------------------------------------------
	// �V�F�[�_�̐ݒ�
	//-------------------------------------------------

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScale;
	D3DXMATRIX mtxSize;
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxRot;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXVECTOR3 CameraRot = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera()->GetRot();

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	// �傫���𔽉f
	D3DXMatrixScaling(&mtxSize, 1.03f,1.03f,1.03f);
	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMATRIX mtxParent;
	D3DXMatrixIdentity(&mtxParent);

	if (m_parent != nullptr)
	{// ToDo : �����𒼂��Ȃ��ƃp�[�c�������Ȃ��̂ŋC��t���悤�I�������A���̂����ȁB
		mtxParent = m_parent->GetMtxWorld();

		// �s��|���Z�֐�
		//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

		pEffect->SetMatrix(m_hParent, &mtxParent);
	}

	//------------------------------------------------------------------------------------------//

	// �^�X�N�O���[�v���
	CTaskGroup* taskGroup = CApplication::GetInstance()->GetTaskGroup();

	// �J�������
	CCamera* pCamera = (CCamera*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_CAMERA, GetPriority());

	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	if (pCamera != nullptr)
	{
		viewMatrix = pCamera->GetMtxView();
		projMatrix = pCamera->GetMtxProje();
	}

	pEffect->SetTechnique(m_hTechnique);
	pEffect->Begin(NULL, 0);

	// ���[���h�ˉe�ϊ��s��
	// �V�F�[�_�[�ɍs���n��
	pEffect->SetMatrix(m_hWorld, &m_mtxWorld);
	pEffect->SetMatrix(m_hScale, &mtxScale);
	pEffect->SetMatrix(m_hSize, &mtxSize);
	pEffect->SetMatrix(m_hRot, &mtxRot);
	pEffect->SetMatrix(m_hTrans, &mtxTrans);
	pEffect->SetMatrix(m_hProj, &projMatrix);
	pEffect->SetMatrix(m_hView, &viewMatrix);

	// �V�F�[�_�[�ɖړI�̒l��n��
	pEffect->SetFloat(m_hTimeTarget, m_TimeTarget);

	// �V�F�[�_�[�ɃJ�������W��n��
	D3DXVECTOR3 c = pCamera->GetPos();
	D3DXVECTOR3 camerapos = D3DXVECTOR3(c.x, c.y, c.z);
	D3DXVECTOR3 objpos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

	D3DXVECTOR3 vec = camerapos - objpos;

	D3DXVec3Normalize(&vec,&vec);
	NormalizeAngle(vec.x);
	NormalizeAngle(vec.y);
	NormalizeAngle(vec.z);

	pEffect->SetVector(m_hCameraVec, &D3DXVECTOR4(vec.x, vec.y, vec.z,0.0f));

	// �V�F�[�_�[�ɕ`�悩��o�߂������Ԃ�n��
	pEffect->SetFloat(m_hTime, m_TimeCnt);

	// ���C�g���
	CLight* lightClass = (CLight*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_LIGHT, GetPriority());

	if (lightClass == nullptr)
	{
		lightClass = (CLight*)taskGroup->SearchRoleTop(CTask::ERole::ROLE_LIGHT, GetPriority() - 1);
	}
	D3DLIGHT9 light = lightClass->GetLight(0);

	// ���C�g�̕���
	D3DXVECTOR4 lightDir = D3DXVECTOR4(light.Direction.x, light.Direction.y, light.Direction.z, 0);
	// ���C�g�̕������V�F�[�_�[�ɓn��
	pEffect->SetVector(m_hvLightDir, &lightDir);
	pEffect->SetVector(m_hCameraVec, &D3DXVECTOR4(CameraRot.x, CameraRot.y, CameraRot.z, 0.0f));

	//�}�e���A���f�[�^�̃|�C���^���擾����
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_numMat; nCntMat++)
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
			tex0 = texture;
		}

		// �e�N�X�`���̐ݒ�
		pEffect->SetTexture(m_hTexture, tex0);

		// �ʏ탂�f���̕`��
		pEffect->BeginPass(1);
		m_mesh->DrawSubset(nCntMat);	//���f���p�[�c�̕`��
		pEffect->EndPass();

		// �����f���̕`��
		pEffect->BeginPass(2);
		//�J�����O�̐ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		m_mesh->DrawSubset(nCntMat);	//���f���p�[�c�̕`��
		//�J�����O�̐ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		pEffect->EndPass();
	}

	pEffect->End();
}

//--------------------------------------------------------------
// �`��
// Author : Yuda Kaito
// �T�v : �`����s��
//--------------------------------------------------------------
void CObjectX::DrawMaterial()
{
	extern LPD3DXEFFECT pEffect;		// �V�F�[�_�[
}

//--------------------------------------------------------------
// scale�̐ݒ�
//--------------------------------------------------------------
void CObjectX::SetScale(const D3DXVECTOR3& inScale)
{
	m_scale = inScale;

	m_minVtx.x = m_scale.x * m_minVtxOrigin.x;
	m_minVtx.y = m_scale.y * m_minVtxOrigin.y;
	m_minVtx.z = m_scale.z * m_minVtxOrigin.z;

	m_maxVtx.x = m_scale.x * m_maxVtxOrigin.x;
	m_maxVtx.y = m_scale.y * m_maxVtxOrigin.y;
	m_maxVtx.z = m_scale.z * m_maxVtxOrigin.z;
}

//--------------------------------------------------------------
// �����̐ݒ�
// Author : Yuda Kaito
//--------------------------------------------------------------
void CObjectX::SetRot(const D3DXVECTOR3 & inRot)
{
	if (m_rot != inRot)
	{
		SetMtxRot(inRot);
	}
	m_rot = inRot;
}

//--------------------------------------------------------------
// ���_�ő召�l�̌v�Z����
// Author : Yuda Kaito
//--------------------------------------------------------------
void CObjectX::SetMtxRot(const D3DXVECTOR3& inRot)
{
	D3DXQUATERNION quaternion;
	D3DXQuaternionRotationYawPitchRoll(&quaternion, inRot.y, inRot.x, inRot.z);
	SetMtxQuaternion(quaternion);
}

//--------------------------------------------------------------
// ���_�ő召�l�̌v�Z����
// Author : Yuda Kaito
//--------------------------------------------------------------
void CObjectX::CalculationVtx()
{
	D3DXMATRIX mtxTrans, mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);

	// �����̔��f
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &m_mtxRot);		// �s��|���Z�֐�

	D3DXVec3TransformCoord(&m_maxVtx, &m_maxVtx, &mtxWorld);
	D3DXVec3TransformCoord(&m_minVtx, &m_minVtx, &mtxWorld);

	if (m_maxVtx.x < m_minVtx.x)
	{
		float change = m_maxVtx.x;
		m_maxVtx.x = m_minVtx.x;
		m_minVtx.x = change;
	}

	if (m_maxVtx.y < m_minVtx.y)
	{
		float change = m_maxVtx.y;
		m_maxVtx.y = m_minVtx.y;
		m_minVtx.y = change;
	}

	if (m_maxVtx.z < m_minVtx.z)
	{
		float change = m_maxVtx.z;
		m_maxVtx.z = m_minVtx.z;
		m_minVtx.z = change;
	}
}

//--------------------------------------------------------------
// ��������
// Author : Yuda Kaito
//--------------------------------------------------------------
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

//--------------------------------------------------------------
// ���f���̓ǂݍ���
// Author : Yuda Kaito
//--------------------------------------------------------------
void CObjectX::LoadModel(std::string aFileName)
{
	CObjectXGroup *xGroup = CApplication::GetInstance()->GetObjectXGroup();
	m_buffMat = xGroup->GetBuffMat(aFileName);
	m_maxVtxOrigin = xGroup->GetMaxVtx(aFileName);
	m_maxVtx = m_maxVtxOrigin;
	m_minVtxOrigin = xGroup->GetMinVtx(aFileName);
	m_minVtx = m_minVtxOrigin;
	m_mesh = xGroup->GetMesh(aFileName);
	m_numMat = xGroup->GetNumMat(aFileName);
	m_size = xGroup->GetSize(aFileName);
}

//--------------------------------------------------------------
// ���s���e����
// Author : Yuda Kaito
//--------------------------------------------------------------
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
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// ���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// ���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A����ێ�
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	if (m_buffMat != nullptr)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_buffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_numMat; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			Material = pMat[nCntMat].MatD3D;
			Material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			Material.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&Material);

			// ���f���p�[�c�̕`��
			m_mesh->DrawSubset(nCntMat);
		}
	}

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------------------------------
// �F���i�g�U���ˌ��j�̐ݒ�
// Author : Yuda Kaito
//--------------------------------------------------------------
void CObjectX::SetMaterialDiffuse(unsigned int index, const D3DXCOLOR& inColor)
{
	// �ύX�\��̃}�e���A�����Ȃ��ꍇ
	if (index >= m_numMat)
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

//--------------------------------------------------------------
// Sphere��AABB�̓����蔻��
// Author : Yuda Kaito
//--------------------------------------------------------------
bool CObjectX::SphereAndAABB(CObjectX* inObjectX, D3DXVECTOR3* outPos)
{
	if (!inObjectX->IsCollision())
	{
		return false;
	}

	D3DXVECTOR3 dist(0.0f, 0.0f, 0.0f);
	float length = AABBAndPointLength(inObjectX, &dist);	// �ŒZ����

	if (m_maxVtx.x * 1.4f > length)
	{
		if (outPos != nullptr)
		{
			*outPos = dist;
		}

		m_pos -= dist * (m_maxVtx.x * 1.4f - length);
	}

	return m_maxVtx.x * 1.4f > length;
}

//--------------------------------------------------------------
// Ray��AABB�̓����蔻��
// Author : Yuda Kaito
//--------------------------------------------------------------
bool CObjectX::RayAndAABB(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inNormal, D3DXVECTOR3* outPos)
{
	float tmin = (m_minVtx.x + m_pos.x - inPos.x) / inNormal.x;
	float tmax = (m_maxVtx.x + m_pos.x - inPos.x) / inNormal.x;

	if (tmin > tmax)
	{
		std::swap(tmin, tmax);
	}

	float tymin = (m_minVtx.y + m_pos.y - inPos.y) / inNormal.y;
	float tymax = (m_maxVtx.y + m_pos.y - inPos.y) / inNormal.y;

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

	float tzmin = (m_minVtx.z + m_pos.z - inPos.z) / inNormal.z;
	float tzmax = (m_maxVtx.z + m_pos.z - inPos.z) / inNormal.z;

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

//--------------------------------------------------------------
// ������AABB�̓����蔻��
// Author : Yuda Kaito
//--------------------------------------------------------------
bool CObjectX::SegmentAndAABB(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inPos2, D3DXVECTOR3* outPos)
{
	// �����̗��[�_��AABB���Ɋ܂܂�Ă��邩�ǂ����𔻒肷��B
	{
		D3DXVECTOR3 min = m_pos + m_minVtx;
		D3DXVECTOR3 max = m_pos + m_maxVtx;

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

//--------------------------------------------------------------
// ���ݒn��AABB�̍ŏ�����
// Author : Yuda Kaito
//--------------------------------------------------------------
float CObjectX::AABBAndPointLength(CObjectX* inObject, D3DXVECTOR3* outDist)
{
	float SqLen = 0.0f;	// �����ׂ̂���̒l���i�[

						// �e���œ_���ŏ��l�ȉ��������͍ő�l�ȏ�Ȃ�΁A�����l��

	D3DXVECTOR3 min = inObject->m_pos + inObject->m_minVtx;
	D3DXVECTOR3 max = inObject->m_pos + inObject->m_maxVtx;
	D3DXVECTOR3 dist(0.0f, 0.0f, 0.0f);

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
		dist.z += -1.0f;
	}

	D3DXVec3Normalize(&dist, &dist);

	if (outDist != nullptr)
	{
		*outDist = dist;
	}

	return sqrt(SqLen);
}
