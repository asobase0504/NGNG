//**************************************************************
//
// vC[
// Author : ûüì]
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

	// fÌÇÝÝ
	m_apModel[0]->LoadModel("PLAYER01");
	m_apModel[0]->CalculationVtx();

	// ÀWÌæ¾
	D3DXVECTOR3 pos = GetPos();

	m_collisionCyinder = CCollisionCyinder::Create(pos, 10.0f, 50.0f);
	m_collision.push_back(m_collisionCyinder);

	return S_OK;
}

//--------------------------------------------------------------
// I¹
//--------------------------------------------------------------
void CPlayer::Uninit()
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
void CPlayer::Update()
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

	m_controller->TakeItem();
	
	bool a = m_collisionCyinder->ToBox(CEnemyManager::GetInstance()->GetEnemyBox(),true);
	m_collisionCyinder->SetPos(pos);

	if (a)
	{
		//D3DXVECTOR3 pos = GetPos();
		//SetPos(D3DXVECTOR3(m_collisionCyinder->GetExtrusion().x, pos.y, pos.z));
		//m_collisionCyinder->SetPos(D3DXVECTOR3(m_collisionCyinder->GetExtrusion().x, pos.y, pos.z));
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
// ¶¬
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

	// Wv
	bool jump = m_controller->Jump();

	if (jump && !m_jumpCount.MaxCurrentSame())
	{
 		m_jumpCount.AddCurrent(1);

		// WvÍ
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
		// dÍ
		move.y -= 0.175f;
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