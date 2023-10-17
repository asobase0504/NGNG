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
#include "utility.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{
	m_collisionCyinder = nullptr;
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

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	m_collisionCyinder = CCollisionCyinder::Create(pos,5.0f, 50.0f);

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CPlayer::Uninit(void)
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
void CPlayer::Update(void)
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	if (m_controller == nullptr)
	{
		return;
	}


	// �ړ�
	Move();

	// �X�V����
	CCharacter::Update();

	// �W�����v
	Jump();

	// �_�b�V��
	Dash();
	
	DEBUG_PRINT("pos1 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);

	if (m_collisionCyinder->ToBox(CEnemyManager::GetInstance()->GetEnemyBox(), true))
	{
		// �����o�����ʒu
		D3DXVECTOR3 extrusion = m_collisionCyinder->GetExtrusion();
		SetPos(D3DXVECTOR3(extrusion));
		m_collisionCyinder->SetPos(D3DXVECTOR3(extrusion));
		DEBUG_PRINT("pos2 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	DEBUG_PRINT("pos3 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);

#ifdef _DEBUG
	CDebugProc::Print("Player�Fpos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
	CDebugProc::Print("Player�Fmove(%f,%f,%f)\n", move.x, move.y, move.z);
	CDebugProc::Print("PlayerCollision�Fpos(%f,%f,%f)\n", m_collisionCyinder->GetPos().x, m_collisionCyinder->GetPos().y, m_collisionCyinder->GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
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

	bool jump = false;

	// �W�����v
	jump = m_controller->Jump();

	if (jump)
	{
		// �W�����v��
		move.y += 25.0f;
		jump = false;
	}

	if (GetPos().y > 0.0f)
	{
		// �d��
		move.y -= 1.0f;
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

void CPlayer::SetPos(const D3DXVECTOR3 & inPos)
{
	if (m_collisionCyinder != nullptr)
	{
		m_collisionCyinder->SetPos(inPos);
	}

	std::vector<CObjectX*> objectX = GetModel();
	if (objectX.size() > 0)
	{
		GetModel()[0]->SetPos(inPos);
	}

	CCharacter::SetPos(inPos);
}
