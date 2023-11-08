#include "abnormal_data_base.h"
#include "abnormal.h"

#include "character.h"
#include "utility.h"

//==============================================================
// 静的メンバー変数の宣言
//==============================================================
CAbnormalDataBase* CAbnormalDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CAbnormalDataBase::CAbnormalDataBase()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
void CAbnormalDataBase::Init()
{
	m_abnormal[ABNORMAL_FIRE] = CAbnormal::Create(ABNORMAL_FIRE);
	// やけど状態 ----------------------------------------------
	m_abnormal[ABNORMAL_FIRE]->SetWhenAddFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->AddUbnormalStack(ABNORMAL_FIRE);
		inCharacter->SetUbnormalTime(ABNORMAL_FIRE, 60);
	});
	m_abnormal[ABNORMAL_FIRE]->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->GetHp()->AddCurrent(-1);
	});

	//----------------------------------------------------------
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
CAbnormalDataBase * CAbnormalDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CAbnormalDataBase;

		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

CAbnormalDataBase::~CAbnormalDataBase()
{
}

void CAbnormalDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}
