//**************************************************************
//
// �ߐڍU��
// Author : ���c�喲
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
// �R���X�g���N�^
//--------------------------------------------------------------
CMeleeAttack::CMeleeAttack() : m_life(1)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CMeleeAttack::~CMeleeAttack()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CMeleeAttack::Init()
{
	CObject::Init();

	m_collision = CCollisionCylinder::Create(GetPos(), 10.0f, 10.0f);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CMeleeAttack::Uninit()
{
	CObject::Uninit();
}

//--------------------------------------------------------------
// �X�V
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

	// �v���C���[�̎擾
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerHp = pPlayer->GetHp();

	if (m_collision->ToCylinder((CCollisionCylinder*)pPlayer->GetCollision()))
	{
		playerHp->AddCurrent(-10);
		Uninit();
	}
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CMeleeAttack::Draw()
{
	CObject::Draw();
}

//--------------------------------------------------------------
// ����
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
