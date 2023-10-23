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
#include "statue.h"
#include "statue_manager.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "Controller.h"
#include "skill_data_base.h"
#include "application.h"
#include "objectX.h"
#include "collision_cylinder.h"
#include "utility.h"
#include "skill.h"
#include <sstream>
#include "item_data_base.h"
#include "item.h"

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

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		// XLð¶¬
		m_Skill[nCnt] = CSkill::Create();
		// intðstring^ÉÏ··é
		std::ostringstream  name;
		name << "YAMATO_SKILL_" << nCnt+1;
		// XLÌÝè
		m_Skill[nCnt]->SetSkill(name.str(), this);
	}

	// fÌÇÝÝ
	m_apModel[0]->LoadModel("PLAYER01");
	m_apModel[0]->CalculationVtx();

	// ÀWÌæ¾
	D3DXVECTOR3 pos = GetPos();

	m_collision.push_back(CCollisionCylinder::Create(pos, 10.0f, 10.0f));

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

	if (m_controller == nullptr)
	{
		return;
	}

	// Ú®
	Move();

	// XV
	CCharacter::Update();

	// Wv
	Jump();

	// _bV
	Dash();

	// U
	Attack();
	
	
	TakeItem();

	if (m_collision[0]->ToBox(CEnemyManager::GetInstance()->GetEnemyBox(), true))
	{
		// µoµ½Êu
		D3DXVECTOR3 extrusion = ((CCollisionCylinder*)m_collision[0])->GetExtrusion();
		SetPos(D3DXVECTOR3(extrusion));
		m_collision[0]->SetPos(D3DXVECTOR3(extrusion));
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//if (m_collisionCyinder->ToBox(CStatueManager::GetInstance()->GetStatue(), true))
	//{
	//	// µoµ½Êu
	//	D3DXVECTOR3 extrusion = m_collisionCyinder->GetExtrusion();
	//	SetPos(D3DXVECTOR3(extrusion));
	//	m_collisionCyinder->SetPos(D3DXVECTOR3(extrusion));
	//	DEBUG_PRINT("pos2 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);
	//	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}

	DEBUG_PRINT("pos3 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);

#ifdef _DEBUG
	CDebugProc::Print("PlayerFpos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
	CDebugProc::Print("PlayerFmove(%f,%f,%f)\n", move.x, move.y, move.z);
	CDebugProc::Print("PlayerCollisionFpos(%f,%f,%f)\n", m_collision[0]->GetPos().x, m_collision[0]->GetPos().y, m_collision[0]->GetPos().z);
#endif // _DEBUG
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
	if (m_controller->Skill_1())
	{
		// ­®É¶¬

	}

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
// Wv
//--------------------------------------------------------------
void CPlayer::Jump()
{
	// Ú®ÊÌæ¾
	D3DXVECTOR3 move(0.0f,0.0f,0.0f);

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
		move.y -= 0.18f;
	}
	else
	{
		SetMoveY(0.0f);
	}

	// Ú®ÊÌÝè
	AddMove(move);
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
// ACeÌæ¾
//--------------------------------------------------------------
void CPlayer::TakeItem()
{
	int id = m_controller->TakeItem();

	if (id < 0)
	{
		return;
	}

	m_haveItem[id]++;
	CItem::ITEM_FUNC itemFunc = CItemDataBase::GetInstance()->GetItemData((CItemDataBase::EItemType)id)->GetWhenPickFunc();

	if (itemFunc != nullptr)
	{
		itemFunc(this, m_haveItem[id]);
	}
}

//--------------------------------------------------------------
// Rg[[ÌÝè
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}

//--------------------------------------------------------------
// ÊuÌÝè
//--------------------------------------------------------------
void CPlayer::SetPos(const D3DXVECTOR3 & inPos)
{
	if (m_collision.size() > 0)
	{
		if (m_collision[0] != nullptr)
		{
			m_collision[0]->SetPos(inPos);
		}
	}

	std::vector<CObjectX*> objectX = GetModel();
	if (objectX.size() > 0)
	{
		GetModel()[0]->SetPos(inPos);
	}

	CCharacter::SetPos(inPos);
}
