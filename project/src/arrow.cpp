//**************************************************************
//
// arrow.cpp
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "arrow.h"

#include "application.h"
#include "game.h"
#include "enemy.h"
#include "PlayerController.h"

#include "collision_box.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CArrow::CArrow(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CArrow::~CArrow()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CArrow::Init()
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
// 更新
//--------------------------------------------------------------
void CArrow::Update()
{
	CObjectX::Update();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CArrow* CArrow::Create(const D3DXVECTOR3& move)
{
	CArrow* arrow = nullptr;
	arrow = new CArrow;

	if (arrow != nullptr)
	{
		arrow->Init();
		arrow->SetMove(move);
	}
	else
	{
		assert(false);
	}

	return arrow;
}

//--------------------------------------------------------------
// エネミーに当たったら
//--------------------------------------------------------------
//void CArrow::HitEnemy_(CCharacter* inEnemy,int damage)
//{
//	if (inEnemy->GetCollision->ToBox(m_collision, false))
//	{
//		inEnemy->TakeDamage(damage);
//		this->Uninit();
//	}
//}
