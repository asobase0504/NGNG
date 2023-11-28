//**************************************************************
//
// item_data
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "gold_nugget.h"

#include "application.h"
#include "game.h"
#include "player.h"
#include "PlayerController.h"

#include "collision_box.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CGoldNugget::CGoldNugget(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CGoldNugget::~CGoldNugget()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CGoldNugget::Init()
{
	LoadModel("BOX");

	// 当たり判定
	m_collision = CCollisionBox::Create(GetPos(), GetRot(), D3DXVECTOR3(10.0f, 10.0f, 10.0f), GetMtxWorld());
	m_collision->SetParent(&m_pos);

	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CGoldNugget::Update()
{
	CGame* game = (CGame*)CApplication::GetInstance()->GetModeClass();
	CPlayer* player = game->GetController()->GetToOrder();
	if (m_collision->ToCylinder(player->GetCollision()))
	{
		player->GetMoney()->AddItemEffect(30);
	}
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CGoldNugget* CGoldNugget::Create()
{
	CGoldNugget* pGoldNugget = nullptr;
	pGoldNugget = new CGoldNugget;

	if (pGoldNugget != nullptr)
	{
		pGoldNugget->Init();
	}

	return pGoldNugget;
}
