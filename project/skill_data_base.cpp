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

//--------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------------------------
CSkillDataBase* CSkillDataBase::m_instance = nullptr;


//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkillDataBase::CSkillDataBase()
{
}

//--------------------------------------------------------------
// �V���O���g���ł̃C���X�^���X�̎擾
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
// �I������
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
// ����������
//--------------------------------------------------------------
void CSkillDataBase::Init()
{
	m_skillDataBase["YAMATO_SKILL_1"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // �������ɔ������������
		
	},
		[this](CCharacter* inusedCharacter)
	{ // Hit���ɔ������������
		
	} };

	m_skillDataBase["YAMATO_SKILL_2"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // �������ɔ������������

	},
		[this](CCharacter* inusedCharacter)
	{ // Hit���ɔ������������

	} };

	m_skillDataBase["YAMATO_SKILL_3"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // �������ɔ������������

	},
		[this](CCharacter* inusedCharacter)
	{ // Hit���ɔ������������

	} };

	m_skillDataBase["YAMATO_SKILL_4"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // �������ɔ������������

	},
		[this](CCharacter* inusedCharacter)
	{ // Hit���ɔ������������

	} };
}
