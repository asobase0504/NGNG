//**************************************************************
//
// �G
// Author : ���c�喲
//
//**************************************************************

// include
#include "enemy.h"
#include "player_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"

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

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CEnemy::Uninit(void)
{
	// �I������
	CCharacter::Uninit();
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

	// �ړ�����
	Move();

	// �X�V����
	CCharacter::Update();

#ifdef _DEBUG
		CDebugProc::Print("Enemy�Fpos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
		CDebugProc::Print("Enemy�Fmove(%f,%f,%f)\n", move.x, move.y, move.z);
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
