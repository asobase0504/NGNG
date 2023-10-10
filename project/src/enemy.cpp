//**************************************************************
//
// �G
// Author : ���c�喲
//
//**************************************************************

// include
#include "enemy.h"
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
	CCharacter::Init();

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CEnemy::Uninit(void)
{
	CCharacter::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CEnemy::Update(void)
{
	// ���W�X�V
	Updatepos();

	CCharacter::Update();

#ifdef _DEBUG
	CDebugProc::Print("Enemy�Fpos(%f,%f,%f)\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("Enemy�Fmove(%f,%f,%f)\n", m_move.x, m_move.y, m_move.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CEnemy::Draw(void)
{
	CCharacter::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy* pEnemy;
	pEnemy = new CEnemy(CObject::ENEMY);
	pEnemy->m_pos = pos;
	pEnemy->m_rot = rot;
	pEnemy->Init();

	return pEnemy;
}

//--------------------------------------------------------------
// ���W�̍X�V
//--------------------------------------------------------------
void CEnemy::Updatepos()
{
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_posold = m_pos;	// �O��̈ʒu�̕ۑ�
	m_pos += m_move;	// �ʒu�̍X�V

	SetPos(m_pos);
}