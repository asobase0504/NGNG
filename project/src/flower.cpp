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
// �萔�錾
//==============================================================
const int CFlower::INTERVAL(300);

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CFlower::CFlower(CTaskGroup::EPriority list) : m_collision(nullptr), m_healingCount(0)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CFlower::~CFlower()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CFlower::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// ������(�I�[�o�[���[�h)
//--------------------------------------------------------------
HRESULT CFlower::Init(const D3DXVECTOR3& inPos, const float& inHeight)
{
	CObjectX::Init();

	LoadModel("BOX");
	m_collision = CCollisionSphere::Create(inPos, inHeight);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CFlower::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// �X�V
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
// ����
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
// �񕜂���G���A
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
