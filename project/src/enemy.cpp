//**************************************************************
//
// �G
// Author : ���c�喲
//
//**************************************************************

#ifdef _DEBUG
#if 0
#define ENEMY_DEBUG
#endif
#endif

// include
#include "enemy.h"
#include "player.h"
#include "player_manager.h"
#include "status.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_box.h"
#include "enemy_hp_ui.h"
#include "model_skin.h"

#include "enemy_data_base.h"
#include "skill.h"
#include "game.h"
#include "difficult.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CEnemy::CEnemy()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CEnemy::~CEnemy()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CEnemy::Init()
{
	// ����������
	CCharacter::Init();

	// �G�Ώ��
	m_relation = ERelation::HOSTILE;

	m_AttackCnt = 0;
	// ���f���̓ǂݍ���
	m_skinModel = CSkinMesh::Create("SKE");
	SetEndChildren(m_skinModel);

	m_Activity = (CEnemyDataBase::GetInstance()->GetActivityFunc(CEnemyDataBase::EActivityPattern::PATTERN_GOLEM));

	m_pEHPUI = CEnemy_HPUI::Create(this);
	SetEndChildren(m_pEHPUI);

	// �����蔻��̍쐬
	m_collision = CCollisionCylinder::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10.0f, 10.0f);
	m_collision->SetParent(&m_pos);
	SetEndChildren(m_collision);

	// SKILL�̍쐬
	m_skill.push_back(CSkill::Create());
	m_skill[0]->SetSkill("GOLEM_SKILL_1",this);
	SetEndChildren(m_skill[0]);

	m_dropMoney = 5;
	return S_OK;
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CEnemy::Update()
{
	if (m_isDied)
	{
		Uninit();
		return;
	}

	if (m_isStun)
	{
		SetMove(D3DXVECTOR3(0.0f,0.0f,0.0f));
		return;
	}

	// ���݂�activity�ɐݒ肷��B
	m_Activity(this);

	CDifficult *pDiff = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetDifficult();
	int exp = pDiff->GetLevel();

	AddExp(exp);

	// �X�V����
	CCharacter::Update();

#ifdef ENEMY_DEBUG
	CDebugProc::Print("Enemy�Fmove3(%f,%f,%f)\n", m_move.x, m_move.y, m_move.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// ���S����
//--------------------------------------------------------------
void CEnemy::Died()
{
	CPlayerManager::GetInstance()->GetPlayer()->GetMoney()->AddCurrent(m_dropMoney);
	CCharacter::Died();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
void CEnemy::Move()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

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

	SetMoveXZ(move.x,move.z);
}