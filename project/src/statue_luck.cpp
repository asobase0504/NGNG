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
// �X�V����
//--------------------------------------------------------------
void CStatueLuck::Update()
{
	// �v���C���[���擾
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerMoney = pPlayer->GetMoney();

	// �v���C���[���G��Ă��鎞
	
	if (Touch())
	{
		if (m_nItemCount < 2)
		{
			// �v���C���[�����𒲐����Đݒ�
			playerMoney->AddCurrent(-m_nUseMoney);

			// �A�C�e���m���v�Z
			int randomCount = IntRandom(100, 1);

			int answer = CItemManager::GetInstance()->CreateRandomItemRarityRate(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), GetMtxRot(),{ 0.05f,0.1f,0.2f,0.65f });

			switch (answer)
			{
			case 0:	// ���A
				m_nItemCount++;
				break;
			case 1:	// �A���R����
				m_nItemCount++;
				break;
			case 2:	// �R����
				m_nItemCount++;
				break;
			case 3:	// �n�Y��
				break;
			default:
				break;
			}

			// ����K�`�����鎞�p�ɕK�v�������𑝂₵�Đݒ肵�Ă���
			int randomNumber = rand() % 10;
			m_nUseMoney += randomNumber;

			m_bOnce = true;
		}
	}

	// �X�V����
	CStatue::Update();

#ifdef _DEBUG
#if 0
	CDebugProc::Print("LuckPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // 0
#endif // _DEBUG
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