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
