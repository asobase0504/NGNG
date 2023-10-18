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
#include "enemy.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_cylinder.h"
#include "utility.h"
//#include "skill.h"

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

	// �U��
	Attack();
	
	
	TakeItem();

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
	if (m_controller->Skill_1())
	{
		// �X�L���̐���
	//	CSkill::YamatoSkill("YAMATO_SKILL_1",this);
	}

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
	D3DXVECTOR3 move = m_controller->Move() * m_movePower.GetCurrent();

	if (D3DXVec3Length(&move) != 0.0f)
	{
		SetMoveXZ(move.x, move.z);
	}
	else
	{
		D3DXVECTOR3 nowMove = GetMove();
		AddMoveXZ(nowMove.x * -0.15f, nowMove.z * -0.15f);
	}
}

//--------------------------------------------------------------
// �W�����v
//--------------------------------------------------------------
void CPlayer::Jump()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move(0.0f,0.0f,0.0f);

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
		move.y -= 0.18f;
	}
	else
	{
		SetMoveY(0.0f);
	}

	// �ړ��ʂ̐ݒ�
	AddMove(move);
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
// �A�C�e���̎擾
//--------------------------------------------------------------
void CPlayer::TakeItem()
{
	int id = m_controller->TakeItem();

	if (id < 0)
	{
		return;
	}

	m_haveItem[id]++;
}

//--------------------------------------------------------------
// �R���g���[���[�̐ݒ�
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}

//--------------------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------------------
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
