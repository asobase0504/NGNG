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
#include "utility.h"

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
void CItemManager::CreateItem(const D3DXVECTOR3& inPos, const D3DXMATRIX& boxmtx, CItemDataBase::EItemType inId)
{
	m_itemType = inId;

	m_itemData = CItem::Create(m_itemType);
	CItemModel::Create(inPos, boxmtx, inId);
}

//--------------------------------------------------------------
// レアリティ指定でアイテムの生成
//--------------------------------------------------------------
void CItemManager::CreateRandomItemRarity(const D3DXVECTOR3 & inPos, const D3DXMATRIX & boxmtx, CItemDataBase::ERarity inRarity)
{
	CItemDataBase::EItemType id = (CItemDataBase::EItemType)IntRandom(0, CItemDataBase::EItemType::ITEM_MAX - 1);
	CItemDataBase::ERarity rarity = CItemDataBase::GetInstance()->GetItemData(id)->GetRerity();

	while (rarity != inRarity)
	{
		id = (CItemDataBase::EItemType)IntRandom(0, CItemDataBase::EItemType::ITEM_MAX - 1);
		rarity = CItemDataBase::GetInstance()->GetItemData(id)->GetRerity();
	}

	CreateItem(inPos, boxmtx, CItemDataBase::ITEM_TOISI/*(CItemDataBase::EItemType)id*/);
}

//--------------------------------------------------------------
// レアリティごとの出現割合でアイテムの生成
//--------------------------------------------------------------
CItemDataBase::ERarity CItemManager::CreateRandomItemRarityRate(const D3DXVECTOR3 & inPos, const D3DXMATRIX & boxmtx, std::array<float, CItemDataBase::RARITY_MAX> rarityRate)
{
	std::vector<float> vec;
	vec.resize(rarityRate.size());
	for (int i = 0; i < (int)rarityRate.size(); i++)
	{
		vec[i] = rarityRate[i];
	}
	CItemDataBase::ERarity rarity = (CItemDataBase::ERarity)IntRateRandom(vec);

	if (rarity == CItemDataBase::ERarity::RARITY_LOSE)
	{ // はずれ
		return rarity;
	}

	CreateRandomItemRarity(inPos, boxmtx, rarity);
	return rarity;
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
void CItemManager::AllWhenAllways(CCharacter* inCharacter, item_count inItem)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_FUNC func = item->GetWhenAllwaysFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i]);
	}
}

void CItemManager::AllWhenUseSkill(CCharacter* inCharacter, item_count inItem, CCharacter* outCharacter)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_ACTION_FUNC func = item->GetWhenDeathFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i], outCharacter);
	}
}

//--------------------------------------------------------------
// 死亡させたときに発動するアイテム
//--------------------------------------------------------------
void CItemManager::AllWhenDeath(CCharacter* inCharacter, item_count inItem, CCharacter* outCharacter)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_ACTION_FUNC func = item->GetWhenDeathFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i], outCharacter);
	}
}

//--------------------------------------------------------------
// ダメージを受けた時全アイテム
//--------------------------------------------------------------
void CItemManager::AllWhenReceive(CCharacter* inCharacter, item_count inItem, CCharacter* outCharacter)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_ACTION_FUNC func = item->GetWhenReceiveFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i],outCharacter);
	}
}

void CItemManager::AllWhenInflict(CCharacter* inCharacter, item_count inItem, CCharacter* outCharacter)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_ACTION_FUNC func = item->GetWhenInflictFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i], outCharacter);
	}
}
