//**************************************************************
//
// �^�̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_luck.h"
#include "player_manager.h"
#include "item_manager.h"
#include "input.h"
#include "utility.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueLuck::CStatueLuck(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueLuck::~CStatueLuck()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueLuck::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos,rot);
	LoadModel("STATUE_LUCK");

	m_bOnce = false;
	m_bChance = false;
	m_nUseMoney = 10;
	m_nItemCount = 0;

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CStatueLuck::Uninit()
{
	// �I������
	CStatue::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueLuck::Update()
{
	// �v���C���[���擾
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerMoney = pPlayer->GetMoney();

	// �v���C���[���G��Ă��鎞
	
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// �v���C���[������̃L�[���������Ƃ�
			if (!m_bOnce)
			{
				if (m_nItemCount < 2)
				{
					// �v���C���[�����𒲐����Đݒ�
					playerMoney->AddCurrent(-m_nUseMoney);

					// �A�C�e���m���v�Z
					int randomCount = IntRandom(100, 1);

					if (randomCount <= 4)
					{// ���A

					//--------------------------
					//  �A�C�e���h���b�v�֐�
					//--------------------------

						m_nItemCount++;
					}
					else if (randomCount >= 5 && randomCount <= 12)
					{// �A���R����

					 //--------------------------
					 //  �A�C�e���h���b�v�֐�
					 //--------------------------

						m_nItemCount++;
					}
					else if (randomCount >= 13 && randomCount <= 39)
					{// �R����

					 //--------------------------
					 //  �A�C�e���h���b�v�֐�
					 //--------------------------

						m_nItemCount++;
					}
					else
					{// �n�Y��

					}

					// ����K�`�����鎞�p�ɕK�v�������𑝂₵�Đݒ肵�Ă���
					int randomNumber = rand() % 10;
					m_nUseMoney += randomNumber;

					m_bOnce = true;
				}
			}
		}
		else
		{
			m_bOnce = false;
			m_bChance = false;
		}
	}

	// �X�V����
	CStatue::Update();

#ifdef _DEBUG
	CDebugProc::Print("LuckPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CStatueLuck::Draw(void)
{
	// �`�揈��
	CStatue::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueLuck* CStatueLuck::Create(D3DXVECTOR3 pos)
{
	CStatueLuck* pStatuechest;
	pStatuechest = new CStatueLuck;
	pStatuechest->SetPos(pos);
	pStatuechest->Init();

	return pStatuechest;
}