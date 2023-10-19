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

//--------------------------------------------------------------
// ����
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
