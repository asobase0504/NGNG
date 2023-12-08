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
// �R���X�g���N�^
//--------------------------------------------------------------
CArrow::CArrow(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CArrow::~CArrow()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CArrow::Init()
{
	CObjectX::Init();

	LoadModel("BOX");

	// �����蔻��
	m_collision = CCollisionBox::Create(GetPos(), GetRot(), D3DXVECTOR3(10.0f, 10.0f, 10.0f), GetMtxWorld());
	m_collision->SetParent(&m_pos);

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CArrow::Update()
{
	CObjectX::Update();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CArrow* CArrow::Create()
{
	CArrow* arrow = nullptr;
	arrow = new CArrow;

	if (arrow != nullptr)
	{
		arrow->Init();
	}
	else
	{
		assert(false);
	}

	return arrow;
}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
//bool CArrow::HitEnemy(CCharacter* enemy)
//{
//	//CGame* game = (CGame*)CApplication::GetInstance()->GetModeClass();
//	//return m_collision->ToCylinder(enemy->GetCollision());
//}