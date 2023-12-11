//**************************************************************
//
// arrow.cpp
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "flower.h"

// main
#include "application.h"

// mode
#include "game.h"

// collision
#include "collision_sphere.h"

// object
#include "player.h"
#include "PlayerController.h"

//==============================================================
// 定数宣言
//==============================================================
const int CFlower::INTERVAL(300);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CFlower::CFlower(CTaskGroup::EPriority list) : m_collision(nullptr), m_healingCount(0)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CFlower::~CFlower()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CFlower::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 初期化(オーバーロード)
//--------------------------------------------------------------
HRESULT CFlower::Init(const D3DXVECTOR3& inPos, const float& inHeight)
{
	CObjectX::Init();

	LoadModel("BOX");
	m_collision = CCollisionSphere::Create(inPos, inHeight);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CFlower::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CFlower::Update()
{
	CObjectX::Update();

	m_healingCount++;
	if (m_healingCount > INTERVAL)
	{
		HealingArea_();
		m_healingCount = 0;
	}
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CFlower* CFlower::Create(const D3DXVECTOR3& inPos, const float& inHeight)
{
	CFlower* pFlower = nullptr;
	pFlower = new CFlower;

	if (pFlower != nullptr)
	{
		pFlower->Init(inPos, inHeight);
		pFlower->SetPos(inPos);
	}
	else
	{
		assert(false);
	}

	return pFlower;
}

//--------------------------------------------------------------
// 回復するエリア
//--------------------------------------------------------------
void CFlower::HealingArea_()
{
	CGame* game = (CGame*)CApplication::GetInstance()->GetModeClass();
	CPlayer* player = game->GetController()->GetToOrder();

	CInput* input = CInput::GetKey();
	if (player->GetCollision()->ToSphere(m_collision))
	{
		player->Heal(20);
	}
}
