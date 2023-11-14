//**************************************************************
//
// 像管理
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_manager.h"
#include "statue_blood.h"
#include "statue_chest.h"
#include "statue_luck.h"
#include "statue_combat.h"
#include "statue_teleporter.h"
#include "statue.h"
#include "collision_box.h"
#include "application.h"
#include "utility.h"

#include "map.h"
#include "object_mesh.h"
#include "collision_mesh.h"

//--------------------------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------------------------
CStatueManager* CStatueManager::m_statueManager = nullptr;

//--------------------------------------------------------------
// シングルトンでのインスタンスの取得
//--------------------------------------------------------------
CStatueManager* CStatueManager::GetInstance()
{
	if (m_statueManager == nullptr)
	{
		m_statueManager = new CStatueManager;
	}
	return m_statueManager;
}

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueManager::CStatueManager()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueManager::~CStatueManager()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueManager::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CStatueManager::Uninit(void)
{
	if (m_statueManager != nullptr)
	{
		m_statueManager = nullptr;
	}
	CTask::Uninit();
}

//--------------------------------------------------------------
// 生成処理
//--------------------------------------------------------------
CStatue* CStatueManager::CreateStatue(D3DXVECTOR3 pos, int type)
{
	CStatue* statue = nullptr;
	switch (type)
	{
	case CStatueManager::BLOOD:
		statue = CStatueBlood::Create(pos);
		break;
	case CStatueManager::CHEST:
		statue = CStatueChest::Create(pos);
		break;
	case CStatueManager::LUCK:
		statue = CStatueLuck::Create(pos);
		break;
	case CStatueManager::COMBAT:
		statue = CStatueCombat::Create(pos);
		break;
	case CStatueManager::TELEPORTER:
		statue = CStatueTeleporter::Create(pos);
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
	}

	return statue;
}

//--------------------------------------------------------------
// 生成処理
//--------------------------------------------------------------
CStatue * CStatueManager::CreateStatue(int type)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	D3DXVECTOR3 pos(randomPosX, -FLT_MAX, randomPosZ);

	return CreateStatue(pos, type);
}

//--------------------------------------------------------------
// ランダムな像生成処理
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreate()
{
	// 生成
	int randomCount = IntRandom(5, 1);
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue;

	if (randomCount != 2)
	{
		statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), randomCount);
	}
	else
	{
		int rand = IntRandom(4, 1);

		if (rand == 1)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), 1);
		}
		else if (rand == 2)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), 3);
		}
		else
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), 4);
		}
	}

	return statue;
}
