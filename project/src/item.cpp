//**************************************************************
//
// item_data
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "item.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CItem::CItem(CTaskGroup::EPriority list) : 
	CTask(list),
	m_getFunc(nullptr),
	m_lostFunc(nullptr),
	m_allwayFunc(nullptr),
	m_deathFunc(nullptr),
	m_receiveFunc(nullptr),
	m_inflictFunc(nullptr),
	m_rarity(CItemDataBase::RARITY_NONE)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CItem::~CItem()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CItem::Init()
{
	return S_OK;
}

void CItem::Uninit()
{
	CTask::Uninit();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CItem* CItem::Create(CItemDataBase::EItemType inId)
{
	CItem* pItemData = nullptr;
	pItemData = new CItem;

	if (pItemData != nullptr)
	{
		pItemData->Init();
	}

	return pItemData;
}
