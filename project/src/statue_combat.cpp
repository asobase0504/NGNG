//**************************************************************
//
// �킢�̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_combat.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "input.h"
#include "utility.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueCombat::CStatueCombat(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueCombat::~CStatueCombat()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueCombat::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos, rot);

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CStatueCombat::Uninit()
{
	// �I������
	CStatue::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueCombat::Update()
{
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	D3DXVECTOR3 pos = GetPos();

	// �v���C���[���G��Ă��鎞
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// �v���C���[������̃L�[���������Ƃ�
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				// �G�̐���
				float randX = FloatRandom(1.5f, 0.5f);
				float randZ = FloatRandom(1.5f, 0.5f);

				CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(pos.x * randX,pos.y,pos.z * randZ),D3DXVECTOR3(50.0f,50.0f,50.0f), CEnemyManager::NONE);
			}
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
void CStatueCombat::Draw(void)
{
	// �`�揈��
	CStatue::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueCombat* CStatueCombat::Create(D3DXVECTOR3 pos)
{
	CStatueCombat* pStatuecombat;
	pStatuecombat = new CStatueCombat;
	pStatuecombat->SetPos(pos);
	pStatuecombat->Init();

	return pStatuecombat;
}