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
	CObjectX::Init();

	LoadModel("BOX");

	// 当たり判定
	m_collision = CCollisionBox::Create(GetPos(), GetRot(), D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	m_collision->SetMtxWorld(GetMtxWorld());
	m_collision->SetParent(&m_pos);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CGoldNugget::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CGoldNugget::Update()
{
	Get_();

	CObjectX::Update();
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
	else
	{
		assert(false);
	}

	return pGoldNugget;
}

//--------------------------------------------------------------
// 取得したとき
//--------------------------------------------------------------
void CGoldNugget::Get_()
{
	CGame* game = (CGame*)CApplication::GetInstance()->GetModeClass();
	CPlayer* player = game->GetController()->GetToOrder();

	CInput* input = CInput::GetKey();
	if (player->GetCollision()->ToBox(m_collision, false))
	{
		player->GetMoney()->AddCurrent(30);
		this->Uninit();
	}
}
