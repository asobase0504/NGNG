//**************************************************************
//
// �[��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "dullahan.h"
#include "collision_cylinder.h"
#include "model_skin.h"
#include "skill.h"
#include "player_manager.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CDullahan::CDullahan()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CDullahan::~CDullahan()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CDullahan::Init()
{
	CEnemy::Init();

	// ���f��
	m_skinModel->Load("DULLAHAN");

	m_size = D3DXVECTOR3(50.0f, 150.0f, 50.0f);

	// �����蔻��
	m_collision->SetHeight(100.0f);
	m_collision->SetLength(20.0f);

	// �X�e�[�^�X
	m_attack.SetCurrent(1);
	m_hp.SetCurrent(100);
	m_hp.AddMax(100);
	m_movePower.Init(1.0f);
	m_movePower.SetCurrent(1.0f);


	// SKILL�̍쐬
	m_skill.push_back(CSkill::Create());
	m_skill[0]->SetSkill("GOLEM_SKILL_1", this);
	SetEndChildren(m_skill[0]);

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CDullahan::Update()
{
	CEnemy::Update();

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
	D3DXVECTOR3 distancePos = (PlayerPos - pos);
	float distance = D3DXVec3Length(&distancePos);

	// �J�E���g�J�n
	AddAttackCnt(1);

	// �G�l�~�[�̋����������Ƃ�
	if (distance >= 150.0f)
	{
		if (GetAttackCnt() >= 180)
		{
			// �J�E���g�J�n
			SetAttackCnt(0);
			GetSkill()[0]->Use();
		}
	}
}

//--------------------------------------------------------------
// �ړ�
//--------------------------------------------------------------
void CDullahan::Move()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

	D3DXVECTOR3 distancePos = (PlayerPos - pos);

	distancePos.y = 0.0f;

	D3DXVec3Normalize(&distancePos, &distancePos);

	distancePos *= m_movePower.GetCurrent();

	SetMoveXZ(distancePos.x, distancePos.z);
}
