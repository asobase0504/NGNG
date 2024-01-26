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

// enemy
#include "dullahan.h"
#include "fox.h"
#include "gasyadokuro.h"
#include "gyuuki.h"
#include "kappa.h"
#include "karakasa.h"
#include "monster.h"
#include "monster_sky.h"
#include "nine_fox.h"
#include "nurikabe.h"
#include "oni.h"
#include "oni_child.h"
#include "skelton.h"
#include "tengu.h"
#include "tengu_child.h"

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
CEnemy* CEnemyManager::CreateEnemy(D3DXVECTOR3 pos, CEnemyDataBase::EEnemyType type, int level)
{
	CEnemy* enemy;
	switch (type)
	{
	case CEnemyDataBase::SKELTON:
		enemy = new CSkelton;
		break;
	case CEnemyDataBase::TENGU:
		enemy = new CTengu;
		break;
	case CEnemyDataBase::TENGU_CHILD:
		enemy = new CTenguChild;
		break;
	case CEnemyDataBase::MONSTER:
		enemy = new CMonster;
		break;
	case CEnemyDataBase::SKY_MONSTER:
		enemy = new CMonsterSky;
		break;
	case CEnemyDataBase::NURIKABE:
		enemy = new CNurikabe;
		break;
	case CEnemyDataBase::ONI_BIG:
		enemy = new COni;
		break;
	case CEnemyDataBase::ONI:
		enemy = new COniChild;
		break;
	case CEnemyDataBase::KARAKASA:
		enemy = new CKarakasa;
		break;
	case CEnemyDataBase::KAPPA:
		enemy = new CKappa;
		break;
	//case CEnemyDataBase::GYUUKI:
	//	enemy = new CGyuuki;
	//	break;
	case CEnemyDataBase::FOX:
		enemy = new CFox;
		break;
	case CEnemyDataBase::DULLAHAN:
		enemy = new CDullahan;
		break;
	case CEnemyDataBase::GASYADOKURO:
		enemy = new CGasyadokuro;
		break;
	case CEnemyDataBase::NINE_FOX:
		enemy = new CNineFox;
		break;
	case CEnemyDataBase::MAX_TYPE:
	default:
		assert(false);
		break;
	}

	enemy->Init();
	enemy->SetPos(pos);
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
	int enemyType = IntRandom(CEnemyDataBase::EEnemyType::MAX_TYPE - 1, 0);

	CDifficult *pDiff =  ((CGame*)CApplication::GetInstance()->GetModeClass())->GetDifficult();
	return CreateEnemy(D3DXVECTOR3(randomPosX, 0.0f, randomPosZ), (CEnemyDataBase::EEnemyType)enemyType, pDiff->GetEnemyLevel());
}