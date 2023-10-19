#include "item_data_base.h"
#include "item.h"

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
