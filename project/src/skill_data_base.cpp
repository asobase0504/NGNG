﻿//**************************************************************
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
#include "karakasa_skill.h"
#include "monster_skill.h"

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
	SKILL_INFO* info;

	// 通常攻撃
	info = &m_dates["YAMATO_SKILL_1"];
	info->baseInfo.CT = 60;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CYamatoSkill_1::Create;
	info->texKey = "SKILL_ICON_YAMATO1";
	
	// ワープ
	info = &m_dates["YAMATO_SKILL_2"];
	info->baseInfo.CT = 180;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CYamatoSkill_2::Create;
	info->texKey = "SKILL_ICON_YAMATO2";
	
	// 回転切り
	info = &m_dates["YAMATO_SKILL_3"];
	info->baseInfo.CT = 120;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CYamatoSkill_3::Create;
	info->texKey = "SKILL_ICON_YAMATO3";
	
	// 透明連続攻撃
	info = &m_dates["YAMATO_SKILL_4"];
	info->baseInfo.CT = 300;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CYamatoSkill_4::Create;
	info->texKey = "SKILL_ICON_YAMATO4";
	
	// クールダウンリセット
	info = &m_dates["YAMATO_SKILL_5"];
	info->baseInfo.CT = 300;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CSkill5::Create;
	info->texKey = "SKILL_ICON_YAMATO5";
	
	// 弾
	info = &m_dates["GOLEM_SKILL_1"];
	info->baseInfo.CT = 50;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CGolemSkill_1::Create;
	
	// 空中に飛んで突撃
	info = &m_dates["KARAKASA_SKILL"];
	info->baseInfo.CT = 500;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CKarakasaSkill::Create;

	// 徐々に加速する突撃
	info = &m_dates["MONSTER_SKILL"];
	info->baseInfo.CT = 500;
	info->baseInfo.stock = 1;
	info->baseInfo.invincible = 0;
	info->ability = CMonsterSkill::Create;
}