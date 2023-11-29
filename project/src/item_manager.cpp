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
// �ÓI�����o�ϐ��錾
//==============================================================
CItemManager* CItemManager::m_itemManager = nullptr;

//--------------------------------------------------------------
// �C���X�^���X
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
// �R���X�g���N�^
//--------------------------------------------------------------
CItemManager::CItemManager(CTaskGroup::EPriority list) : 
	m_itemData(nullptr), m_itemType(CItemDataBase::ITEM_NONE)
{
	m_itemModel.clear();
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CItemManager::~CItemManager()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CItemManager::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CItemManager::Uninit()
{
	m_itemData = nullptr;
	m_itemModel.clear();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CItemManager::Update()
{
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CItemManager::Draw()
{
}

void CItemManager::CreateRandomItem(const D3DXVECTOR3 & inPos, const D3DXMATRIX & boxmtx)
{
	int id = IntRandom(0, CItemDataBase::EItemType::ITEM_MAX - 1);
	CreateItem(inPos, boxmtx,(CItemDataBase::EItemType)id);
}

void CItemManager::CreateRandomItemRarity(const D3DXVECTOR3 & inPos, const D3DXMATRIX & boxmtx, CItemDataBase::ERarity inRarity)
{
	CItemDataBase::EItemType id = (CItemDataBase::EItemType)IntRandom(0, CItemDataBase::EItemType::ITEM_MAX - 1);
	CItemDataBase::ERarity rarity = CItemDataBase::GetInstance()->GetItemData(id)->GetRerity();

	while (rarity != inRarity)
	{
		id = (CItemDataBase::EItemType)IntRandom(0, CItemDataBase::EItemType::ITEM_MAX - 1);
		rarity = CItemDataBase::GetInstance()->GetItemData(id)->GetRerity();
	}

	CreateItem(inPos, boxmtx, CItemDataBase::ITEM_KOBAN/*(CItemDataBase::EItemType)id*/);
}

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
	{ // �͂���
		return rarity;
	}

	CreateRandomItemRarity(inPos, boxmtx, rarity);
	return rarity;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
void CItemManager::CreateItem(const D3DXVECTOR3& inPos, const D3DXMATRIX& boxmtx, CItemDataBase::EItemType inId)
{
	m_itemType = inId;

	m_itemData = CItem::Create(m_itemType);
	m_itemModel.push_back(CItemModel::Create(inPos, boxmtx, inId));
}

//--------------------------------------------------------------
// �擾�������S�A�C�e��
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
// ���������S�A�C�e��
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
// �펞�S�A�C�e��
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
// �_���[�W���󂯂����S�A�C�e��
//--------------------------------------------------------------
void CItemManager::AllWhenDamage(CCharacter* inCharacter, item_count inItem, CCharacter* outCharacter)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_ACTION_FUNC func = item->GetWhenDamageFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i],outCharacter);
	}
}

void CItemManager::AllWhenHit(CCharacter* inCharacter, item_count inItem, CCharacter* outCharacter)
{
	CItemDataBase* dataBase = CItemDataBase::GetInstance();

	for (int i = 0; i < CItemDataBase::ITEM_MAX; i++)
	{
		if (inItem[i] == 0)
		{
			continue;
		}

		CItem* item = dataBase->GetItemData((CItemDataBase::EItemType)i);
		CItem::ITEM_ACTION_FUNC func = item->GetWhenHitFunc();

		if (func == nullptr)
		{
			continue;
		}

		func(inCharacter, inItem[i], outCharacter);
	}
}
