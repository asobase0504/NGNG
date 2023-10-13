//**************************************************************
//
// エネミーデータベース
// Author : YudaKaito
//
//**************************************************************

// マクロ定義
#define UPDATE_FUNC_CAST(func) (static_cast<void(CEnemyDataBase::*)()>(&(func)))

//==============================================================
// include
//==============================================================
#include "enemy_data_base.h"

CEnemyDataBase::CEnemyDataBase()
{
}

CEnemyDataBase * CEnemyDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CEnemyDataBase;

		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

CEnemyDataBase::~CEnemyDataBase()
{
}

void CEnemyDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}

void CEnemyDataBase::Init()
{
	m_activityFunc["COME"] = []()
	{
	};
}
