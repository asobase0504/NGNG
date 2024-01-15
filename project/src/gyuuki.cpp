//**************************************************************
//
// �[��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "gyuuki.h"
#include "collision_cylinder.h"
#include "collision_box.h"
#include "model_skin.h"
#include "skill.h"
#include "player_manager.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CGyuuki::CGyuuki()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CGyuuki::~CGyuuki()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CGyuuki::Init()
{
	CEnemy::Init();

	// ���f��
	m_skinModel->Load("GYUUKI");

	m_size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// �����蔻��
	m_collision->SetHeight(50.0f);
	m_collision->SetLength(10.0f);

	// �����߂�����
	m_extrusion->SetSize(D3DXVECTOR3(150.0f,100.0f,150.0f));

	// �X�e�[�^�X
	m_attack.SetCurrent(1);
	m_hp.SetCurrent(100);
	m_hp.AddMax(100);
	m_movePower.Init(0.1f);
	m_movePower.SetCurrent(0.1f);

	// SKILL�̍쐬
	m_skill.push_back(CSkill::Create());
	m_skill[0]->SetSkill("GYUUKI_STAMP_SKILL", this);
	SetEndChildren(m_skill[0]);

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CGyuuki::Update()
{
	CEnemy::Update();

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
	D3DXVECTOR3 distancePos = (PlayerPos - pos);
	float distance = D3DXVec3Length(&distancePos);

	GetSkill()[0]->Use();
}

//--------------------------------------------------------------
// �ړ�
//--------------------------------------------------------------
void CGyuuki::Move()
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
