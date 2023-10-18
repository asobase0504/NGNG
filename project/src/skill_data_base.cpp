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
// instanceの取得
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
	m_dates["YAMATO_SKILL_1"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // 発動時の効果

	},
		[](CCharacter* inusedCharacter)
	{ // Hit時の効果

	} };
	m_dates["YAMATO_SKILL_2"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // 発動時の効果

	},
		[](CCharacter* inusedCharacter)
	{ // Hit時の効果

	} };
	m_dates["YAMATO_SKILL_3"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // 発動時の効果
	},
		[](CCharacter* inusedCharacter)
	{ // Hit時の効果

	} };
	m_dates["YAMATO_SKILL_4"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // 発動時の効果

	},
		[](CCharacter* inusedCharacter)
	{ // Hit時の効果

	} };
}
