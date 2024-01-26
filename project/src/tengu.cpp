//**************************************************************
//
// �V��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "tengu.h"
#include "collision_cylinder.h"
#include "model_skin.h"
#include "skill.h"
#include "player_manager.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CTengu::CTengu()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CTengu::~CTengu()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CTengu::Init()
{
	CEnemy::Init();

	// ���f��
	m_skinModel->Load("TENGU");

	m_size = D3DXVECTOR3(50.0f, 130.0f, 50.0f);

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
	m_skill[0]->SetSkill("STORM", this);
	SetEndChildren(m_skill[0]);

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CTengu::Update()
{
	CEnemy::Update();

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
	D3DXVECTOR3 distancePos = (PlayerPos - pos);
	float distance = D3DXVec3Length(&distancePos);

	// �G�l�~�[�̋����������Ƃ�
	{
		GetSkill()[0]->Use();
	}
}

//--------------------------------------------------------------
// �ړ�
//--------------------------------------------------------------
void CTengu::Move()
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
