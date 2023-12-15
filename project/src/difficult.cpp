//**************************************************************
//
// ��Փx�V�X�e��
// Author : Tomidokoro Tomoki
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "difficult.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CDifficult::CDifficult() :
	CObject(CTaskGroup::LEVEL_3D_1)
{
	m_time = 0;
	m_gameLevel = 0;
	m_enemyLevel = 0;
	m_isCount = true;
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CDifficult::~CDifficult()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CDifficult::Init()
{
	CObject::Init();

	return S_OK;
}

//--------------------------------------------------------------
// ������(�I�[�o�[���[�h)
//--------------------------------------------------------------
HRESULT CDifficult::Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	CObject::Init();

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CDifficult::Uninit()
{
	CObject::Uninit();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CDifficult::Update()
{
	if (m_isCount)
	{// ���Ԃ��o�߂�����
		m_time++;
	}

	if (m_time >= 300)
	{
		m_gameLevel++;
		m_enemyLevel = m_gameLevel * 10;
		m_time = 0;
	}

	CObject::Update();
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CDifficult::Draw()
{
	CObject::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CDifficult* CDifficult::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	CDifficult* pDifficult = nullptr;
	pDifficult = new CDifficult;

	if (pDifficult != nullptr)
	{
		pDifficult->Init(inPos, inRot, inSize);
		pDifficult->SetPos(inPos);
		pDifficult->SetRot(inRot);
		pDifficult->SetSize(inSize);
	}

	return pDifficult;
}
