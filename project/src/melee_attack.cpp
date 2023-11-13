//**************************************************************
//
// 近接攻撃
// Author : 梶田大夢
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "melee_attack.h"
#include "character.h"
#include "utility.h"
#include "application.h"
#include "collision.h"
#include "collision_cylinder.h"
#include "player_manager.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CMeleeAttack::CMeleeAttack() : m_life(1)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CMeleeAttack::~CMeleeAttack()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CMeleeAttack::Init()
{
	CObject::Init();

	m_collision = CCollisionCylinder::Create(GetPos(), 10.0f, 10.0f);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CMeleeAttack::Uninit()
{
	CObject::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CMeleeAttack::Update()
{
	CObject::Update();
	m_collision->SetPos(GetPos());

	m_life--;

	if (m_life <= 0)
	{
		Uninit();
	}

	// プレイヤーの取得
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerHp = pPlayer->GetHp();

	if (m_collision->ToCylinder((CCollisionCylinder*)pPlayer->GetCollision()))
	{
		playerHp->AddCurrent(-10);
		Uninit();
	}
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CMeleeAttack::Draw()
{
	CObject::Draw();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CMeleeAttack* CMeleeAttack::Create(D3DXVECTOR3 pos)
{
	CMeleeAttack* pObject = nullptr;
	pObject = new CMeleeAttack();

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(pos);
	}

	return pObject;
}
