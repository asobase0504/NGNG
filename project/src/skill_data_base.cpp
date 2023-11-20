//**************************************************************
//
// スキルチE�Eタベ�Eス
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

// Skill
#include "yamato_skill_1.h"
#include "yamato_skill_2.h"
#include "golem_skill_1.h"

//==============================================================
// 静的メンバ�E変数の宣言
//==============================================================
CSkillDataBase* CSkillDataBase::m_instance = nullptr;

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkillDataBase::CSkillDataBase()
{
}

//--------------------------------------------------------------
// instanceの取征E
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
// チE��トラクタ
//--------------------------------------------------------------
CSkillDataBase::~CSkillDataBase()
{
}

//--------------------------------------------------------------
// 終亁E
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
// 初期匁E
//--------------------------------------------------------------
void CSkillDataBase::Init()
{
	m_dates["YAMATO_SKILL_1"] = { 60,1,1,0,60,0,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[this](CCharacter* inusedCharacter)
	{// 発動時の効极E
		if (inusedCharacter != nullptr)
		{
			CYamatoSkill_1::Create(inusedCharacter);
		}

		return false;
	}};
	m_dates["YAMATO_SKILL_2"] = { 120,1,1,0,5,0,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[this](CCharacter* inusedCharacter)
	{ // 発動時の効极E
		if (inusedCharacter != nullptr)
		{
			CYamatoSkill_2::Create(inusedCharacter);
		}

		return false;
	}};
	m_dates["YAMATO_SKILL_3"] = { 0,1,1,0,5,0,D3DXVECTOR3(0.0f,0.0f,0.0f),
		[](CCharacter* inusedCharacter)
	{ // 発動時の効极E
		return false;
	}};
	m_dates["YAMATO_SKILL_4"] = { 0,1,1,0,5,0,D3DXVECTOR3(0.0f,0.0f,0.0f),
		[](CCharacter* inusedCharacter)
	{ // 発動時の効极E
		return false;
	}};
	m_dates["GOLEM_SKILL_1"] = { 50,1,1,0,600,0,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[this](CCharacter* inusedCharacter)
	{// 発動時の効极E
		if (inusedCharacter != nullptr)
		{
			CGolemSkill_1::Create(inusedCharacter);
		}
		return false;
	}};
}