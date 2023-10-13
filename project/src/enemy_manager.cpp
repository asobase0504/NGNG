//**************************************************************
//
// 敵管理
// Author : 梶田大夢
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
// 更新処理
//--------------------------------------------------------------
void CEnemyManager::Update(void)
{
}

//--------------------------------------------------------------
// 描画処理
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