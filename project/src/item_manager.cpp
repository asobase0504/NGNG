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
// �R���X�g���N�^
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
	m_itemData(nullptr), m_itemModel(nullptr), m_itemType(ITEM_NONE)
{
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
	m_itemModel = nullptr;
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
