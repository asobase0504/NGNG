//**************************************************************
//
// �󔠂̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_chest.h"
#include "player_manager.h"
#include "item_manager.h"
#include "collision_cylinder.h"
#include "collision_box.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueChest::CStatueChest(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueChest::~CStatueChest()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueChest::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos, rot);
	m_collisionBox->SetPos(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	m_collisionBox->SetSize(D3DXVECTOR3(2.5f, 5.0f, 2.5f));
	LoadModel("STATUE_CHEST");

	return S_OK;
}

//--------------------------------------------------------------
// �I����
//--------------------------------------------------------------
bool CStatueChest::Select(CCharacter * selectCharacter)
{
	CStatus<int>* money = selectCharacter->GetMoney();

	// ����������Ȃ��Ȃ�x�������ł��Ȃ�
	if (money->GetCurrent() < 10)
	{
		return false;
	}

	// �v���C���[�����𒲐����Đݒ�
	money->AddCurrent(-10);

	//-------------------------------------------------------------------------------
	// �A�C�e�������_���h���b�v�֐��ǉ�
	//---------------------------------------------------------------------------------
	D3DXVECTOR3 pos = GetPos();
	CItemManager::GetInstance()->CreateRandomItemRarityRate(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), GetMtxRot(), { 0.7f,0.25,0.5f,0.0f });
	//CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), GetMtxRot(), CItemDataBase::EItemType::ITEM_DANGO);

	m_collisionCylinder->Uninit();
	m_collisionCylinder = nullptr;

	return true;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueChest* CStatueChest::Create(D3DXVECTOR3 pos)
{
	CStatueChest* pStatuechest;
	pStatuechest = new CStatueChest;
	pStatuechest->SetPos(pos);
	pStatuechest->Init();

	return pStatuechest;
}