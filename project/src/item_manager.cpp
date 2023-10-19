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

//==============================================================
// 静的メンバ変数宣言
//==============================================================
CItemManager* CItemManager::m_itemManager = nullptr;

//--------------------------------------------------------------
// インスタンス
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
	m_itemData(nullptr), m_itemType(CItemDataBase::ITEM_NONE)
{
	m_itemModel.clear();
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
	m_itemModel.clear();
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
void CItemManager::CreateItem(const D3DXVECTOR3& inPos, CItemDataBase::EItemType inId)
{
	m_itemType = inId;

	switch (m_itemType)
	{
	case CItemDataBase::ITEM_POWER_UP:
		m_itemData = CItem::Create(inId);
		m_itemModel.push_back(CItemModel::Create(inPos, inId));
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
// 取得した時全アイテム
//--------------------------------------------------------------
void CItemManager::AllWhenPick(CCharacter* inCharacter, item_count inItem)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_FUNC func = item->GetWhenPickFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i]);
	}
}

//--------------------------------------------------------------
// 失った時全アイテム
//--------------------------------------------------------------
void CItemManager::AllWhenLost(CCharacter* inCharacter, item_count inItem)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_FUNC func = item->GetWhenLostFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i]);
	}
}

//--------------------------------------------------------------
// 常時全アイテム
//--------------------------------------------------------------
void CItemManager::AllWhenAllWay(CCharacter* inCharacter, item_count inItem)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_FUNC func = item->GetWhenAllWayFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i]);
	}
}

//--------------------------------------------------------------
// ダメージを受けた時全アイテム
//--------------------------------------------------------------
void CItemManager::AllWhenDamage(CCharacter* inCharacter, item_count inItem)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_FUNC func = item->GetWhenDamageFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i]);
	}
}

void CItemManager::AllWhenHit(CCharacter* inCharacter, item_count inItem)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_FUNC func = item->GetWhenHitFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i]);
	}
}
