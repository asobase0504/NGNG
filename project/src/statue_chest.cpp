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
#include "collision_box.h"
#include "input.h"

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
	m_bOnce = false;

	return S_OK;
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueChest::Update()
{
	// �v���C���[���擾
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerMoney = pPlayer->GetMoney();

	// �v���C���[���G��Ă��鎞
	if (Touch() && !m_bOnce)
	{
		// �v���C���[�����𒲐����Đݒ�
		playerMoney->AddCurrent(-10);

		//-------------------------------------------------------------------------------
		// �A�C�e�������_���h���b�v�֐��ǉ�
		//---------------------------------------------------------------------------------
		D3DXVECTOR3 pos = GetPos();
		CItemManager::GetInstance()->CreateRandomItemRarityRate(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), GetMtxRot(), {0.7f,0.25,0.5f,0.0f});

		m_bOnce = true;
	}

	// �X�V����
	CStatue::Update();

#ifdef _DEBUG
#if 0
	CDebugProc::Print("ChestPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // 0
#endif // _DEBUG
}

//--------------------------------------------------------------sdw
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