//**************************************************************
//
// �G
// Author : ���c�喲
//
//**************************************************************

// include
#include "enemy.h"
#include "player.h"
#include "player_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_sphere.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CEnemy::CEnemy(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CEnemy::~CEnemy()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CEnemy::Init()
{
	// ����������
	CCharacter::Init();

	D3DXVECTOR3 pos = GetPos();

	m_collisionSphere = CCollisionSphere::Create(pos, 10.0f);

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CEnemy::Uninit(void)
{
	// �I������
	CCharacter::Uninit();

	m_collisionSphere->Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CEnemy::Update(void)
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = GetMove();

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	m_collisionSphere->SetPos(pos);

	//if (m_collisionSphere->ToMesh(CPlayerManager::GetInstance()->GetPlayerCylinder(), true))
	//{
	//	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//	D3DXVECTOR3 pos = player->GetPos();
	//	player->SetPos(D3DXVECTOR3(pos.x, m_collisionSphere->GetExtrusionHeight(), pos.z));
	//	m_collisionSphere->SetPos(D3DXVECTOR3(pos.x, m_collisionSphere->GetExtrusionHeight(), pos.z));
	//}


	// �ړ�����
	Move();

	// �X�V����
	CCharacter::Update();

#ifdef _DEBUG
	CDebugProc::Print("Enemy�Fpos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("Enemy�Fmove(%f,%f,%f)\n", move.x, move.y, move.z);
	CDebugProc::Print("EnemyCollision�Fpos(%f,%f,%f)\n", m_collisionSphere->GetPos().x, m_collisionSphere->GetPos().y, m_collisionSphere->GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CEnemy::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CEnemy* CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy* pEnemy;
	pEnemy = new CEnemy(CObject::ENEMY);
	pEnemy->SetPos(pos);
	pEnemy->Init();

	return pEnemy;
}

//--------------------------------------------------------------
// �ړ�
//--------------------------------------------------------------
void CEnemy::Move()
{
	// �ړ��ʂ̎擾
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���W�̎擾
	D3DXVECTOR3 pos = GetPos();

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

	// �G�̒Ǐ]
	if (pos.x <= PlayerPos.x)
	{
		move.x += MAX_SPEED;
	}
	else
	{
		move.x -= MAX_SPEED;
	}

	if (pos.y <= PlayerPos.y)
	{
		move.y += MAX_SPEED;
	}
	else
	{
		move.y -= MAX_SPEED;
	}

	if (pos.z <= PlayerPos.z)
	{
		move.z += MAX_SPEED;
	}
	else
	{
		move.z -= MAX_SPEED;
	}

	SetMove(move);
}