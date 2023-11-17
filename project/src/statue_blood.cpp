//**************************************************************
//
// ���̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_blood.h"
#include "statue_manager.h"
#include "player_manager.h"
#include "input.h"
#include "map.h"
#include "collision_mesh.h"
#include "collision_box.h"
#include "object_mesh.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueBlood::CStatueBlood(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueBlood::~CStatueBlood()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueBlood::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos, rot);
	LoadModel("STATUE_BLOOD");
	m_bOnce = false;

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CStatueBlood::Uninit()
{
	// �I������
	CStatue::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueBlood::Update()
{
	// �v���C���[���擾
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerHp = pPlayer->GetHp();
	CStatus<int>* playerMoney = pPlayer->GetMoney();

	// �v���C���[���G��Ă��鎞
	if (Touch())
	{
		if (!m_bOnce)
		{
			// �v���C���[��HP�Ƃ����𒲐����Đݒ�
			playerHp->AddCurrent(-10);
			playerMoney->AddCurrent(10);

			m_bOnce = true;
		}
		else
		{
			m_bOnce = false;
		}
	}

	// �X�V����
	CStatue::Update();

#ifdef _DEBUG
#if 0
	CDebugProc::Print("BloodPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // 0
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CStatueBlood::Draw(void)
{
	// �`�揈��
	CStatue::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueBlood* CStatueBlood::Create(D3DXVECTOR3 pos)
{
	CStatueBlood* pStatueblood;
	pStatueblood = new CStatueBlood;
	pStatueblood->SetPos(pos);
	pStatueblood->Init();

	return pStatueblood;
}