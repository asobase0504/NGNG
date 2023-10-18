//**************************************************************
//
// �X�L���f�[�^�x�[�X
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "skill_data_base.h"

//==============================================================
// �ÓI�����o�[�ϐ��̐錾
//==============================================================
CSkillDataBase* CSkillDataBase::m_instance = nullptr;

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkillDataBase::CSkillDataBase()
{
}

//--------------------------------------------------------------
// instance�̎擾
//--------------------------------------------------------------
CSkillDataBase * CSkillDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CSkillDataBase;
		
		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkillDataBase::~CSkillDataBase()
{
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CSkillDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
void CSkillDataBase::Init()
{
	m_dates["YAMATO_SKILL_1"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // �������̌���

	},
		[](CCharacter* inusedCharacter)
	{ // Hit���̌���

	} };
	m_dates["YAMATO_SKILL_2"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // �������̌���

	},
		[](CCharacter* inusedCharacter)
	{ // Hit���̌���

	} };
	m_dates["YAMATO_SKILL_3"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // �������̌���
	},
		[](CCharacter* inusedCharacter)
	{ // Hit���̌���

	} };
	m_dates["YAMATO_SKILL_4"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // �������̌���

	},
		[](CCharacter* inusedCharacter)
	{ // Hit���̌���

	} };
}
