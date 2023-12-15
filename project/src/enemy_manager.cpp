//**************************************************************
//
// �G�Ǘ�
// Author : ���c�喲
//
//**************************************************************

// include
#include "game.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "collision_sphere.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "utility.h"
#include "difficult.h"

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
// �G�̍쐬
//--------------------------------------------------------------
CEnemy* CEnemyManager::CreateEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 size, EType type, int level)
{
	CEnemy* enemy = new CEnemy;
	enemy->Init();
	enemy->SetPos(pos);
	enemy->SetSize(size);
	enemy->SetLevel(level);
	return enemy;
}

//--------------------------------------------------------------
//�G�l�~�[�̃����_������
//--------------------------------------------------------------
CEnemy* CEnemyManager::RandomSpawn()
{
	// ����
	int randomCount = IntRandom(5, 1);
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	// �G�l�~�[�^�C�v�̃����_����
	int enemyType = IntRandom(1, 1);

	CDifficult *pDiff =  ((CGame*)CApplication::GetInstance()->GetModeClass())->GetDifficult();

	return CreateEnemy(D3DXVECTOR3(randomPosX, 0.0f, randomPosZ), D3DXVECTOR3(50.0f, 50.0f, 50.0f), (EType)enemyType, pDiff->GetEnemyLevel());
}