//**************************************************************
//
// item_manager
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "item_manager.h"

#include "item.h"
#include "item_model.h"

CItemManager* CItemManager::m_itemManager = nullptr;

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CItemManager* CItemManager::GetInstance()
{
	if (m_itemManager == nullptr)
	{
		m_itemManager = new CItemManager;
	}
	return m_itemManager;
}

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CItemManager::CItemManager(CTaskGroup::EPriority list) : 
	m_itemData(nullptr), m_itemModel(nullptr), m_itemType(ITEM_NONE)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CItemManager::~CItemManager()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CItemManager::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CItemManager::Uninit()
{
	m_itemData = nullptr;
	m_itemModel = nullptr;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CItemManager::Update()
{
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CItemManager::Draw()
{
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
void CItemManager::CreateItem(const D3DXVECTOR3& inPos, ITEM_TYPE inId)
{
	m_itemType = inId;

	switch (m_itemType)
	{
	case ITEM_POWER_UP:
		m_itemData = CItem::Create(inId);
		m_itemModel = CItemModel::Create(inPos, inId);
		break;
	default:
		break;
	}
}
