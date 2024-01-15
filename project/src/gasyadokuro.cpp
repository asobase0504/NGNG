//**************************************************************
//
// �[��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "gasyadokuro.h"
#include "collision_cylinder.h"
#include "collision_box.h"
#include "model_skin.h"
#include "skill.h"
#include "player_manager.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CGasyadokuro::CGasyadokuro()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CGasyadokuro::~CGasyadokuro()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CGasyadokuro::Init()
{
	CEnemy::Init();

	// ���f��
	m_skinModel->Load("GASYADOKURO");

	m_size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// �����蔻��
	m_collision->SetHeight(280.0f);
	m_collision->SetLength(100.0f);

	// �傫��
	m_extrusion->SetSize(D3DXVECTOR3(40.0f, 90.0f, 40.0f));
	m_extrusion->SetPos(D3DXVECTOR3(0.0f, 70.0f, 0.0f));

	// �X�e�[�^�X
	m_attack.SetCurrent(1);
	m_hp.SetCurrent(100);
	m_hp.AddMax(100);
	m_movePower.Init(1.0f);
	m_movePower.SetCurrent(1.0f);

	// SKILL�̍쐬
	m_skill.push_back(CSkill::Create());
	m_skill[0]->SetSkill("GASYADOKURO_ATTACK_SKILL", this);
	SetEndChildren(m_skill[0]);

	m_skill.push_back(CSkill::Create());
	m_skill[1]->SetSkill("SKELTON_SUMMON_SKILL", this);
	SetEndChildren(m_skill[1]);

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CGasyadokuro::Update()
{
	CEnemy::Update();

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
	D3DXVECTOR3 distancePos = (PlayerPos - pos);
	float distance = D3DXVec3Length(&distancePos);

	if (distance <= 170.0f)
	{
		// �@����(��)
		GetSkill()[0]->Use();
	}
	else
	{
		// �ǂ���̏���
		GetSkill()[1]->Use();
	}

}

//--------------------------------------------------------------
// �ړ�
//--------------------------------------------------------------
void CGasyadokuro::Move()
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
