//**************************************************************
//
// 敵管理
// Author : 梶田大夢
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
//静的メンバ変数宣言
//--------------------------------------------------------------
CEnemyManager* CEnemyManager::m_enemyManager = nullptr;

//--------------------------------------------------------------
// シングルトンでのインスタンスの取得
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
// コンストラクタ
//--------------------------------------------------------------
CEnemyManager::CEnemyManager()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CEnemyManager::~CEnemyManager()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CEnemyManager::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CEnemyManager::Uninit(void)
{
}

//--------------------------------------------------------------
// 敵の作成
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
//エネミーのランダム生成
//--------------------------------------------------------------
CEnemy* CEnemyManager::RandomSpawn()
{
	// 生成
	int randomCount = IntRandom(5, 1);
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	// エネミータイプのランダム化
	int enemyType = IntRandom(1, 1);

	CDifficult *pDiff =  ((CGame*)CApplication::GetInstance()->GetModeClass())->GetDifficult();

	return CreateEnemy(D3DXVECTOR3(randomPosX, 0.0f, randomPosZ), D3DXVECTOR3(50.0f, 50.0f, 50.0f), (EType)enemyType, pDiff->GetEnemyLevel());
}