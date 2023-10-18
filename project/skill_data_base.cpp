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

//--------------------------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------------------------
CSkillDataBase* CSkillDataBase::m_instance = nullptr;


//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkillDataBase::CSkillDataBase()
{
}

//--------------------------------------------------------------
// シングルトンでのインスタンスの取得
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
// 終了処理
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
// 初期化処理
//--------------------------------------------------------------
void CSkillDataBase::Init()
{
	m_skillDataBase["YAMATO_SKILL_1"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // 発動時に発生させるもの
		
	},
		[this](CCharacter* inusedCharacter)
	{ // Hit時に発生させるもの
		
	} };

	m_skillDataBase["YAMATO_SKILL_2"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // 発動時に発生させるもの

	},
		[this](CCharacter* inusedCharacter)
	{ // Hit時に発生させるもの

	} };

	m_skillDataBase["YAMATO_SKILL_3"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // 発動時に発生させるもの

	},
		[this](CCharacter* inusedCharacter)
	{ // Hit時に発生させるもの

	} };

	m_skillDataBase["YAMATO_SKILL_4"] = { 0,1,60,2.0f,6.0f,
		[this](CCharacter* inusedCharacter)
	{ // 発動時に発生させるもの

	},
		[this](CCharacter* inusedCharacter)
	{ // Hit時に発生させるもの

	} };
}
