//**************************************************************
//
// �e���|�[�^�[�̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_teleporter.h"
#include "statue_manager.h"
#include "player_manager.h"
#include "input.h"
#include "map.h"
#include "collision_mesh.h"
#include "collision_box.h"
#include "object_mesh.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "utility.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueTeleporter::CStatueTeleporter(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueTeleporter::~CStatueTeleporter()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueTeleporter::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	m_time = 0;

	CStatue::Init(pos, rot);
	m_bOnce = false;
	m_btimeAdd = false;

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CStatueTeleporter::Uninit()
{
	// �I������
	CStatue::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueTeleporter::Update()
{
	// ���擾
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();

	// �v���C���[���G��Ă��鎞
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// �v���C���[������̃L�[���������Ƃ�
			if (!m_bOnce)
			{
				float randX = FloatRandom(1.5f, 0.5f);
				float randZ = FloatRandom(1.5f, 0.5f);

				m_pEnemy = CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(randX, 0.0f, randZ), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);

				CStatus<int>* enemyHp = m_pEnemy->GetHp();
				enemyHp->SetCurrent(0);
				m_bOnce = true;
			}

			m_btimeAdd = true;
		}
	}

	if (m_bOnce)
	{
		if ((m_pEnemy->IsDied()) && (m_time >= MAX_TIME))
		{
			//-------------------------
			// �}�b�v�ړ������ǉ�
			//-------------------------
		}
	}

	if (m_btimeAdd)
	{
		// ���Ԓǉ�
		m_time++;
	}

	// �X�V����
	CStatue::Update();

#ifdef _DEBUG
	CDebugProc::Print("BloodPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CStatueTeleporter::Draw(void)
{
	// �`�揈��
	CStatue::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueTeleporter* CStatueTeleporter::Create(D3DXVECTOR3 pos)
{
	CStatueTeleporter* pStatueteleporter;
	pStatueteleporter = new CStatueTeleporter;
	pStatueteleporter->SetPos(pos);
	pStatueteleporter->Init();

	return pStatueteleporter;
}