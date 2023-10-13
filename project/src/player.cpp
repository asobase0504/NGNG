//**************************************************************
//
// vC[
// Author : ûüì]
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "player.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_cylinder.h"

//--------------------------------------------------------------
// RXgN^
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{

}

//--------------------------------------------------------------
// fXgN^
//--------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//--------------------------------------------------------------
// ú»
//--------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// ú»
	CCharacter::Init();

	// ÀWÌæ¾
	D3DXVECTOR3 pos = GetPos();

	m_collisionCyinder = CCollisionCyinder::Create(pos, 10.0f, 50.0f);

	return S_OK;
}

//--------------------------------------------------------------
// I¹
//--------------------------------------------------------------
void CPlayer::Uninit(void)
{
	// Rg[[Ìjü
	if (m_controller != nullptr)
	{
		delete m_controller;
		m_controller = nullptr;
	}

	m_collisionCyinder->Uninit();

	// I¹
	CCharacter::Uninit();
}

//--------------------------------------------------------------
// XV
//--------------------------------------------------------------
void CPlayer::Update(void)
{
	// Ú®ÊÌæ¾
	D3DXVECTOR3 move = GetMove();
	// ÀWÌæ¾
	D3DXVECTOR3 pos = GetPos();

	if (m_controller == nullptr)
	{
		return;
	}

	// Ú®
	Move();

	// Wv
	Jump();

	// _bV
	Dash();

	m_collisionCyinder->SetPos(pos);
	bool a = m_collisionCyinder->ToSphere(CEnemyManager::GetInstance()->GetEnemySphere());
	// U
	Attack();


	if (a)
	{
		int b = 0;
	}

	// XV
	CCharacter::Update();

#ifdef _DEBUG
	CDebugProc::Print("PlayerFpos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("PlayerFmove(%f,%f,%f)\n", move.x, move.y, move.z);
	CDebugProc::Print("PlayerCollisionFpos(%f,%f,%f)\n", m_collisionCyinder->GetPos().x, m_collisionCyinder->GetPos().y, m_collisionCyinder->GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// `æ
//--------------------------------------------------------------
void CPlayer::Draw(void)
{
	// `æ
	CCharacter::Draw();
}

//--------------------------------------------------------------
// ¶¬
//--------------------------------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos);
	pPlayer->Init();

	return pPlayer;
}

//--------------------------------------------------------------
// U
//--------------------------------------------------------------
void CPlayer::Attack()
{
	// ÊíU(¶NbN)
	m_controller->Skill_1();

	// XL1(ENbN)
	m_controller->Skill_2();
	
	// XL2(Vtg)
	m_controller->Skill_3();

	// XL3(R)
	m_controller->Skill_4();
}

//--------------------------------------------------------------
// Ú®
//--------------------------------------------------------------
void CPlayer::Move()
{
	// Ú®Ê
	SetMove(m_controller->Move());
}

//--------------------------------------------------------------
// Wv
//--------------------------------------------------------------
void CPlayer::Jump()
{
	// Ú®ÊÌæ¾
	D3DXVECTOR3 move = GetMove();

	bool jump = false;

	// Wv
	jump = m_controller->Jump();

	if (jump)
	{
		// WvÍ
		move.y += JUMP;
	}

	if (GetPos().y > 0.0f)
	{
		// dÍ
		move.y -= 0.1f;
	}

	// Ú®ÊÌÝè
	SetMove(move);
}

//--------------------------------------------------------------
// _bV
//--------------------------------------------------------------
void CPlayer::Dash()
{
	// Ú®ÊÌæ¾
	D3DXVECTOR3 move = GetMove();

	// _bV
	m_isdash = m_controller->Dash();

	if (m_isdash)
	{
		// _bV¬x
		move.x *= DASH_SPEED;
		move.z *= DASH_SPEED;
	}

	// Ú®ÊÌÝè
	SetMove(move);
}

//--------------------------------------------------------------
// Rg[[ÌÝè
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}