//**************************************************************
//
// �v���C���[
// Author : ����]��
//
//**************************************************************

// include
#include "player.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_cylinder.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// ����������
	CCharacter::Init();

	// ���f���̓ǂݍ���
	m_apModel[0]->LoadModel("PLAYER01");
	m_apModel[0]->CalculationVtx();

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	m_collisionCyinder = CCollisionCyinder::Create(pos, 10.0f, 50.0f);
	m_collision.push_back(m_collisionCyinder);

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CPlayer::Uninit()
{
	// �R���g���[���[�̔j��
	if (m_controller != nullptr)
	{
		delete m_controller;
		m_controller = nullptr;
	}

	m_collisionCyinder->Uninit();

	// �I������
	CCharacter::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CPlayer::Update()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();
	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	if (m_controller == nullptr)
	{
		return;
	}

	// �ړ�
	Move();

	// �W�����v
	Jump();

	// �_�b�V��
	Dash();

	m_controller->TakeItem();
	
	bool a = m_collisionCyinder->ToBox(CEnemyManager::GetInstance()->GetEnemyBox(),true);
	m_collisionCyinder->SetPos(pos);

	if (a)
	{
		//D3DXVECTOR3 pos = GetPos();
		//SetPos(D3DXVECTOR3(m_collisionCyinder->GetExtrusion().x, pos.y, pos.z));
		//m_collisionCyinder->SetPos(D3DXVECTOR3(m_collisionCyinder->GetExtrusion().x, pos.y, pos.z));
	}

	// �X�V����
	CCharacter::Update();

#ifdef _DEBUG
	CDebugProc::Print("Player�Fpos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("Player�Fmove(%f,%f,%f)\n", move.x, move.y, move.z);
	CDebugProc::Print("PlayerCollision�Fpos(%f,%f,%f)\n", m_collisionCyinder->GetPos().x, m_collisionCyinder->GetPos().y, m_collisionCyinder->GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer;
	pPlayer = new CPlayer(CObject::PLAYER);
	pPlayer->SetPos(pos);
	pPlayer->Init();

	return pPlayer;
}

//--------------------------------------------------------------
// �ړ�
//--------------------------------------------------------------
void CPlayer::Move()
{
	// �ړ���
	SetMove(m_controller->Move());
}

//--------------------------------------------------------------
// �W�����v
//--------------------------------------------------------------
void CPlayer::Jump()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	// �W�����v
	bool jump = m_controller->Jump();

	if (jump && !m_jumpCount.MaxCurrentSame())
	{
 		m_jumpCount.AddCurrent(1);

		// �W�����v��
		move.y += m_jumpPower.GetCurrent();
	}
	else
	{
		if (!(GetPos().y > 0.0f))
		{
			m_jumpCount.SetCurrent(0);
		}
	}

	if (GetPos().y > 0.0f)
	{
		// �d��
		move.y -= 0.175f;
	}

	// �ړ��ʂ̐ݒ�
	SetMove(move);
}

//--------------------------------------------------------------
// �_�b�V��
//--------------------------------------------------------------
void CPlayer::Dash()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	// �_�b�V��
	m_isdash = m_controller->Dash();

	if (m_isdash)
	{
		// �_�b�V�����x
		move.x *= DASH_SPEED;
		move.z *= DASH_SPEED;
	}

	// �ړ��ʂ̐ݒ�
	SetMove(move);
}

//--------------------------------------------------------------
// �R���g���[���[�̐ݒ�
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}