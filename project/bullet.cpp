//**************************************************************
//
// �|���S���o���b�g
// Author : �y���m��
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "bullet.h"
#include "character.h"
#include "utility.h"
#include "application.h"
#include "collision.h"
#include "collision_cylinder.h"
#include "player_manager.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CBullet::CBullet() : m_life(100)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CBullet::Init()
{
	CObjectPolygon3D::Init();
	SetAnchor(CObjectPolygon3D::ANCHOR_CENTER);
	SetBillboard(true);
	SetSize(D3DXVECTOR3(10.0f,10.0f,0.0f));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	m_collision = CCollisionCylinder::Create(GetPos(),10.0f,10.0f);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CBullet::Uninit()
{
	CObjectPolygon3D::Uninit();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CBullet::Update()
{

	CObjectPolygon3D::Update();
	m_collision->SetPos(GetPos());

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&move,&GetMove());
	move *= m_speed;

	// �ړ�
	AddPos(move);

	m_life--;

	if (m_life <= 0)
	{
		Uninit();
	}

	// �v���C���[�̊l��
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	
	if (m_collision->ToCylinder((CCollisionCylinder*)pPlayer->GetCollision()))
	{
		pPlayer->Damage(50);
		Uninit();
	}
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CBullet::Draw()
{
	CObjectPolygon3D::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,float speed)
{
	CBullet* pObject = nullptr;
	pObject = new CBullet();

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(pos);
		pObject->SetMove(move);
		pObject->SetSpeed(speed);
	}

	return pObject;
}
