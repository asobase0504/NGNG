//**************************************************************
//
// �G�l�~�[�f�[�^�x�[�X
// Author : YudaKaito
//
//**************************************************************
//==============================================================
// include
//==============================================================
#include "enemy_data_base.h"
#include "abnormal_data_base.h"
#include "abnormal.h"
#include "enemy.h"
#include "bullet.h"
#include "melee_attack.h"

#include "skill.h"

//�s���p�^�[���ɕK�v��include
#include "player_manager.h"

// �}�N����`
#define UPDATE_FUNC_CAST(func) (static_cast<void(CEnemyDataBase::*)()>(&(func)))

//==============================================================
// �ÓI�����o�[�ϐ��̐錾
//==============================================================
CEnemyDataBase* CEnemyDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CEnemyDataBase::CEnemyDataBase()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CEnemyDataBase::~CEnemyDataBase()
{
}

//--------------------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------------------
CEnemyDataBase* CEnemyDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CEnemyDataBase;

		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CEnemyDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
void CEnemyDataBase::Init()
{
	m_activityFunc.resize(MAX_PATTERN);
	//--------------------------------------------------------------
	// �󒆂���ߊ��
	//--------------------------------------------------------------
	m_activityFunc[PATTERN_AIR_GO] = [](CEnemy* inEnemy)
	{
		// �ړ��ʂ̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���W�̎擾
		D3DXVECTOR3 pos = inEnemy->GetPos();

		// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

		// �G�̒Ǐ]
		if (pos.x <= PlayerPos.x)
		{
			move.x += MAX_SPEED;
		}
		else
		{
			move.x -= MAX_SPEED;
		}

		if (pos.y <= PlayerPos.y)
		{
			move.y += MAX_SPEED;
		}
		else
		{
			move.y -= MAX_SPEED;
		}

		if (pos.z <= PlayerPos.z)
		{
			move.z += MAX_SPEED;
		}
		else
		{
			move.z -= MAX_SPEED;
		}

		inEnemy->SetMove(move);
	};
	//--------------------------------------------------------------
	// �󒆂�����̋������҂�
	//--------------------------------------------------------------
	m_activityFunc[PATTERN_AIR_KEEP_DISTANCE] = [](CEnemy* inEnemy)
	{
		// �ړ��ʂ̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���W�̎擾
		D3DXVECTOR3 pos = inEnemy->GetPos();

		// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

		// �G�̒Ǐ]
		if (pos.x <= PlayerPos.x)
		{
			move.x += MAX_SPEED;
		}
		else
		{
			move.x -= MAX_SPEED;
		}

		if (pos.y <= PlayerPos.y)
		{
			move.y += MAX_SPEED;
		}
		else
		{
			move.y -= MAX_SPEED;
		}

		if (pos.z <= PlayerPos.z)
		{
			move.z += MAX_SPEED;
		}
		else
		{
			move.z -= MAX_SPEED;
		}

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		if (distance <= 150.0f)
		{
			move *= -0.5f;
		}

		inEnemy->SetMove(move);
	};
	//--------------------------------------------------------------
	// �n�ォ��ߊ��
	//--------------------------------------------------------------
	m_activityFunc[PATTERN_GROUND_GO] = [](CEnemy* inEnemy)
	{
		// �ړ��ʂ̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���W�̎擾
		D3DXVECTOR3 pos = inEnemy->GetPos();

		// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

		// �G�̒Ǐ]
		if (pos.x <= PlayerPos.x)
		{
			move.x += MAX_SPEED;
		}
		else
		{
			move.x -= MAX_SPEED;
		}
		if (pos.z <= PlayerPos.z)
		{
			move.z += MAX_SPEED;
		}
		else
		{
			move.z -= MAX_SPEED;
		}

		inEnemy->SetMove(move);
	};
	//--------------------------------------------------------------
	// �n�ォ����̋������҂�
	//--------------------------------------------------------------
	m_activityFunc[PATTERN_GROUND_KEEP_DISTANCE] = [](CEnemy* inEnemy)
	{
		// �ړ��ʂ̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���W�̎擾
		D3DXVECTOR3 pos = inEnemy->GetPos();

		// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

		// �G�̒Ǐ]
		if (pos.x <= PlayerPos.x)
		{
			move.x += MAX_SPEED;
		}
		else
		{
			move.x -= MAX_SPEED;
		}
		if (pos.z <= PlayerPos.z)
		{
			move.z += MAX_SPEED;
		}
		else
		{
			move.z -= MAX_SPEED;
		}

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		// �߂Â�����������
		if (distance <= 150.0f)
		{
			move *= -0.5f;
		}

		inEnemy->SetMoveXZ(move.x, move.z);
	};
	//--------------------------------------------------------------
	// �n�ォ��ߊ���čU��
	//--------------------------------------------------------------
	m_activityFunc[PATTERN_GROUND_GO_ATTACK] = [](CEnemy* inEnemy)
	{
		// �ړ��ʂ̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���W�̎擾
		D3DXVECTOR3 pos = inEnemy->GetPos();

		// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

		// �G�̒Ǐ]
		if (pos.x <= PlayerPos.x)
		{
			move.x += MAX_SPEED;
		}
		else
		{
			move.x -= MAX_SPEED;
		}
		if (pos.z <= PlayerPos.z)
		{
			move.z += MAX_SPEED;
		}
		else
		{
			move.z -= MAX_SPEED;
		}

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		inEnemy->AddAttackCnt(1);

		// �߂Â�����
		if (distance <= 50.0f)
		{
			if (inEnemy->GetAttackCnt() >= 120)
			{
				// �ߐڍU��
				CMeleeAttack::Create(D3DXVECTOR3(inEnemy->GetPos().x, inEnemy->GetPos().y, inEnemy->GetPos().z));
				inEnemy->SetAttackCnt(0);
				move *= -0.5f;
			}
		}

		inEnemy->SetMoveXZ(move.x, move.z);
	};
	//--------------------------------------------------------------
	// �S�[�����̓���
	//--------------------------------------------------------------
	// �S�[�����̃��[�U�[���~�߂鏈��
	m_activityFunc[PATTERN_GOLEM] = [](CEnemy* inEnemy)
	{
		// �ړ��ʂ̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���W�̎擾
		D3DXVECTOR3 pos = inEnemy->GetPos();

		// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		// �J�E���g�J�n
		inEnemy->AddAttackCnt(1);

		// �G�l�~�[�̋����������Ƃ�
		if (distance >= 150.0f )
		{
			if (inEnemy->GetAttackCnt() >= 180)
			{
				// �J�E���g�J�n
				inEnemy->SetAttackCnt(0);
				inEnemy->GetSkill()[0]->Skill();
				move *= -0.5f;
			}
		}

		// �G�̒Ǐ]
		if (pos.x <= PlayerPos.x)
		{
			move.x += MAX_SPEED;
		}
		else
		{
			move.x -= MAX_SPEED;
		}
		if (pos.z <= PlayerPos.z)
		{
			move.z += MAX_SPEED;
		}
		else
		{
			move.z -= MAX_SPEED;
		}

		inEnemy->SetMoveXZ(move.x,move.z);
	};

	//--------------------------------------------------------------
	// ����̓���
	//--------------------------------------------------------------
	//* �e���΂� */
	m_activityFunc[PATTERN_NINEFOX_BLAST] = [](CEnemy* inEnemy)
	{

	};

	EEnemyType type;

	//--------------------------------------------------------------
	// �G�l�~�[�̐E�X�e�[�^�X��ݒ�
	//--------------------------------------------------------------
	{// �[��
		type = SKELTON;
		m_status[type].s_hp = 100;
		m_status[type].s_attack = 1;
		m_status[type].s_size = 50.0f;
		m_status[type].s_collisionLength = 10.0f;
		m_status[type].s_collisionHeight = 50.0f;
		m_status[type].s_modelKey = "SKE";
	}

	{// ���
		type = NINE_FOX;
		m_status[type].s_hp = 1000;
		m_status[type].s_attack = 1;
		m_status[type].s_size = 150.0f;
		m_status[type].s_collisionLength = 100.0f;
		m_status[type].s_collisionHeight = 150.0f;
		m_status[type].s_modelKey = "NINE_FOX";
	}
}
