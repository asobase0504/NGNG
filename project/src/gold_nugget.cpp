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
// �R���X�g���N�^
//--------------------------------------------------------------
CGoldNugget::CGoldNugget(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CGoldNugget::~CGoldNugget()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CGoldNugget::Init()
{
	LoadModel("BOX");

	// �����蔻��
	m_collision = CCollisionBox::Create(GetPos(), GetRot(), D3DXVECTOR3(10.0f, 10.0f, 10.0f), GetMtxWorld());
	m_collision->SetParent(&m_pos);

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
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
// ����
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
