#include "item_data_base.h"
#include "item.h"

#include "character.h"

//==============================================================
// 静的メンバー変数の宣言
//==============================================================
CItemDataBase* CItemDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CItemDataBase::CItemDataBase()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
void CItemDataBase::Init()
{
	m_item[ITEM_POWER_UP] = CItem::Create(ITEM_POWER_UP);
	m_item[ITEM_POWER_UP]->SetWhenPickFunc([](CCharacter* inCharacter,int cnt)
	{
		CStatus<unsigned int> jumpCount = inCharacter->GetJumpCount();
		jumpCount.AddItemEffect(1);
		inCharacter->SetJumpCount(jumpCount);
	});
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
CItemDataBase * CItemDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CItemDataBase;

		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

CItemDataBase::~CItemDataBase()
{
}

void CItemDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}
