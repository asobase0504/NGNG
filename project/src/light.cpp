//**************************************************************
// 
// ���C�g�̍쐬
// Author : Hamada Ryuuga
// 
//**************************************************************

//==============================================================
// include
//==============================================================
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "input.h"

//==============================================================
// �萔��`
//==============================================================
const int CLight::LIGTH_MAX = 5;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight(CTaskGroup::EPriority inPriority) :
	CTask(inPriority, CTaskGroup::EPushMethod::PUSH_TOP)
{
	SetRole(ROLE_LIGHT);
	m_light.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CLight::Init(void)
{
	m_light.resize(LIGTH_MAX);

	// ���C�g�̐ݒ�
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);

	Set(D3DLIGHT_DIRECTIONAL, color, D3DXVECTOR3(-0.32f, -0.49f, -0.93f), 0);

	// �f�o�C�X�ւ̃|�C���^�̎擾
	CApplication::GetInstance()->GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, color);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// �X�V
//=============================================================================
void CLight::Update(void)
{
	if (CInput::GetKey()->Press(DIK_I))
	{
		m_light[0].Direction.y += -0.1f;
	}
	if (CInput::GetKey()->Press(DIK_K))
	{
		m_light[0].Direction.y += 0.1f;
	}
	if (CInput::GetKey()->Press(DIK_J))
	{
		m_light[0].Direction.x += -0.1f;
	}
	if (CInput::GetKey()->Press(DIK_L))
	{
		m_light[0].Direction.x += 0.1f;
	}
}

//=============================================================================
// �ݒ�
//=============================================================================
void CLight::Set(D3DLIGHTTYPE type,D3DXCOLOR col, D3DXVECTOR3 vec, int nNum)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;		// ���C�g�̕����x�N�g��

	m_light[nNum].Type = type;	// ���C�g�̎�ނ�ݒ� ( ���s���� )
	m_light[nNum].Diffuse = col;	// ���C�g�̊g�U����ݒ� ( ���C�g�̐F )

	vecDir = vec;	// ���C�g�̕�����ݒ�

	// ���K������ ( �傫�� 1 �̃x�N�g���ɂ��� )
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[nNum].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(nNum, &m_light[nNum]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(nNum, true);
}
