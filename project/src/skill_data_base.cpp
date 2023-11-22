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
#include "collision_box.h"
#include "character.h"
#include "enemy_manager.h"
#include "collision_sphere.h"
#include "yamato_skill_1.h"
#include "yamato_skill_2.h"
#include "yamato_skill_3.h"

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
	m_dates["YAMATO_SKILL_1"] = { 0,1,1,0,30,30,0.7,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[this](CCharacter* inusedCharacter)
	{// �������̌���
		if (inusedCharacter != nullptr)
		{
			CYamatoSkill_1::Create(inusedCharacter);
		}

		return false;
	},
		[this](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{// Hit���̌���
		//CStatus<unsigned int> atk = inusedCharacter->GetAtk();
		//int nAtk = atk.GetCurrent();

		inusedCharacter->Attack(inusedInTarget,2.0f);

		return false;
	} };

	m_dates["YAMATO_SKILL_2"] = { 120,1,1,0,5,5,1.0,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[this](CCharacter* inusedCharacter)
	{ // �������̌���
		if (inusedCharacter != nullptr)
		{
			CYamatoSkill_2::Create(inusedCharacter);
		}

		return false;
	},
		[this](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{ // Hit���̌���
		return false;
	} };
	m_dates["YAMATO_SKILL_3"] = { 120,1,1,0,120,20,0.0,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[](CCharacter* inusedCharacter)
	{ // �������̌���
		if (inusedCharacter != nullptr)
		{
			CYamatoSkill_3::Create(inusedCharacter);
		}

		return false;
	},
		[](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{ // Hit���̌���
		return false;
	} };
	m_dates["YAMATO_SKILL_4"] = { 0,1,1,0,5,0,1.0,D3DXVECTOR3(0.0f,0.0f,0.0f),
		[](CCharacter* inusedCharacter)
	{ // �������̌���
		return false;
	},
		[](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{ // Hit���̌���
		return false;
	} };
}