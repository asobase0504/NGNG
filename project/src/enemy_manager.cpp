//**************************************************************
//
// �G�Ǘ�
// Author : ���c�喲
//
//**************************************************************

// include
#include "enemy_manager.h"
#include "enemy.h"
#include "collision_sphere.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"

//--------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------------------------
CEnemyManager* CEnemyManager::m_enemyManager = nullptr;

//--------------------------------------------------------------
// �V���O���g���ł̃C���X�^���X�̎擾
//--------------------------------------------------------------
CEnemyManager* CEnemyManager::GetInstance()
{
	if (m_enemyManager == nullptr)
	{
		m_enemyManager = new CEnemyManager;
	}
	return m_enemyManager;
}

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CEnemyManager::CEnemyManager()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CEnemyManager::~CEnemyManager()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CEnemyManager::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CEnemyManager::Uninit(void)
{
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CEnemyManager::Update(void)
{
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CEnemyManager::Draw(void)
{
}

CEnemy* CEnemyManager::CreateEnemy(D3DXVECTOR3 pos, EType type)
{
	switch (type)
	{
	case CEnemyManager::NONE:
		m_pEnemy = CEnemy::Create(pos);
		break;
	case CEnemyManager::SKELETON:
		break;
	case CEnemyManager::MAX:
		break;
	default:
		break;
	}

	return m_pEnemy;
}