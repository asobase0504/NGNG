//**************************************************************
//
// スキルデータベース
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
#include "yamato_skill_3.h"
#include "yamato_skill_4.h"
#include "Skill5.h"
#include "golem_skill_1.h"

//==============================================================
// 静的メンバー変数の宣言
//==============================================================
CSkillDataBase* CSkillDataBase::m_instance = nullptr;

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkillDataBase::CSkillDataBase()
{
}

//--------------------------------------------------------------
// instance縺ｮ蜿門ｾ・
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
// デストラクタ
//--------------------------------------------------------------
CSkillDataBase::~CSkillDataBase()
{
}

//--------------------------------------------------------------
// 終了
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
// 初期化
//--------------------------------------------------------------
void CSkillDataBase::Init()
{
	m_dates["YAMATO_SKILL_1"] = { 60,1,1,0,30,30,0.7f,0,D3DXVECTOR3(30.0f,30.0f,30.0f),CYamatoSkill_1::Create };
	m_dates["YAMATO_SKILL_1"].texKey = "SKILL_ICON_YAMATO1";
	m_dates["YAMATO_SKILL_2"] = { 180,1,1,0,30,5,1.0,0,D3DXVECTOR3(30.0f,30.0f,30.0f),CYamatoSkill_2::Create };
	m_dates["YAMATO_SKILL_2"].texKey = "SKILL_ICON_YAMATO2";
	m_dates["YAMATO_SKILL_3"] = { 120,1,1,0,120,20,1.0,0,D3DXVECTOR3(30.0f,30.0f,30.0f),CYamatoSkill_3::Create };
	m_dates["YAMATO_SKILL_3"].texKey = "SKILL_ICON_YAMATO3";
	m_dates["YAMATO_SKILL_4"] = { 300,1,1,0,120,20,1.0f,120.0f,D3DXVECTOR3(40.0f,40.0f,40.0f),CYamatoSkill_4::Create };
	m_dates["YAMATO_SKILL_4"].texKey = "SKILL_ICON_YAMATO4";
	m_dates["YAMATO_SKILL_5"] = { 300,1,1,0,120,20,1.0f,120.0f,D3DXVECTOR3(40.0f,40.0f,40.0f),CSkill5::Create };
	m_dates["YAMATO_SKILL_5"].texKey = "SKILL_ICON_YAMATO5";
	m_dates["GOLEM_SKILL_1"] = { 50,1,1,0,600,0,0,0,D3DXVECTOR3(30.0f,30.0f,30.0f),CGolemSkill_1::Create };
}