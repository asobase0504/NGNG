//**************************************************************
//
// �v���C���[
// Author : ����]��
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "player.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"

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

	// �U��
	Attack();

	// �X�V����
	CCharacter::Update();

#ifdef _DEBUG
	CDebugProc::Print("Player�Fpos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("Player�Fmove(%f,%f,%f)\n", move.x, move.y, move.z);
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
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos);
	pPlayer->Init();

	return pPlayer;
}

//--------------------------------------------------------------
// �U��
//--------------------------------------------------------------
void CPlayer::Attack()
{
	// �ʏ�U��(���N���b�N)
	m_controller->Skill_1();

	// �X�L��1(�E�N���b�N)
	m_controller->Skill_2();
	
	// �X�L��2(�V�t�g)
	m_controller->Skill_3();

	// �X�L��3(R)
	m_controller->Skill_4();
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
		move.y += JUMP;
	}

	if (GetPos().y > 0.0f)
	{
		// �d��
		move.y -= 0.1f;
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