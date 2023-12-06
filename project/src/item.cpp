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
// �R���X�g���N�^
//--------------------------------------------------------------
CItem::CItem(CTaskGroup::EPriority list) : 
	CTask(list),
	m_getFunc(nullptr),
	m_lostFunc(nullptr),
	m_allwayFunc(nullptr),
	m_damageFunc(nullptr),
	m_hitFunc(nullptr),
	m_rarity(CItemDataBase::RARITY_NONE)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CItem::~CItem()
{
}

//--------------------------------------------------------------
// ������
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
// ����
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
