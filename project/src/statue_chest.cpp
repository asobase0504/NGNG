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
	CStatue::Init();
	m_bOnce = false;

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CStatueChest::Uninit()
{
	// �I������
	CStatue::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueChest::Update()
{
	// �v���C���[���擾
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int> playerMoney = pPlayer->GetMoney();

	// �v���C���[���G��Ă��鎞
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// �v���C���[������̃L�[���������Ƃ�
			if (!m_bOnce)
			{
				// �v���C���[�����𒲐����Đݒ�
				playerMoney.AddCurrent(-10);
				pPlayer->SetMoney(playerMoney);

				//-------------------------------------------------------------------------------
				// �A�C�e�������_���h���b�v�֐��ǉ�
				//---------------------------------------------------------------------------------
				D3DXVECTOR3 pos = GetPos();
				CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), CItemDataBase::ITEM_POWER_ON);

				m_bOnce = true;
			}
		}
		else
		{
			m_bOnce = false;
		}
	}

	// �X�V����
	CStatue::Update();

#ifdef _DEBUG
	//CDebugProc::Print("Enemy�Fpos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CStatueChest::Draw(void)
{
	// �`�揈��
	CStatue::Draw();
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