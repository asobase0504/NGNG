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
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueManager::Update(void)
{
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CStatueManager::Draw(void)
{
}

//--------------------------------------------------------------
// 生成処理
//--------------------------------------------------------------
CStatue* CStatueManager::CreateStatue(D3DXVECTOR3 pos, int type)
{
	switch (type)
	{
	case CStatueManager::BLOOD:
		RandomCreateBlood(pos);
		break;
	case CStatueManager::CHEST:
		RandomCreateChest(pos);
		break;
	case CStatueManager::LUCK:
		RandomCreateLuck(pos);
		break;
	case CStatueManager::COMBAT:
		RandomCreateCombat(pos);
		break;
	case CStatueManager::TELEPORTER:
		m_pStatue = CStatueTeleporter::Create(pos);
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
	}

	return m_pStatue;
}

//--------------------------------------------------------------
// ランダムな像生成処理
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreate(D3DXVECTOR3 pos)
{
	// 生成
	int randomCount = IntRandom(5, 1);
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	if (randomCount != 2)
	{
		m_pStatue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), randomCount);
	}
	else
	{
		int rand = IntRandom(4, 1);

		if (rand == 1)
		{
			m_pStatue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 1);
		}
		else if (rand == 2)
		{
			m_pStatue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 3);
		}
		else
		{
			m_pStatue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 4);
		}
	}

	return m_pStatue;
}

//--------------------------------------------------------------
// 血の祭壇ランダム生成
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateBlood(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	m_pStatue = CStatueBlood::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));

	return m_pStatue;
}

//--------------------------------------------------------------
// 宝箱ランダム生成
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateChest(D3DXVECTOR3 pos)
{
	// 生成個数
	int randomCount = IntRandom(15, 8);

#ifdef _DEBUG
	randomCount = IntRandom(3, 1);
#endif // DEBUG

	for (int nCnt = 0; nCnt < randomCount; nCnt++)
	{
		float randomPosX = FloatRandom(400.0f, -500.0f);
		float randomPosZ = FloatRandom(500.0f,-415.0f);
		m_pStatue = CStatueChest::Create(D3DXVECTOR3(randomPosX,pos.y, randomPosZ));
	}
	
	return m_pStatue;
}

//--------------------------------------------------------------
// 運の祭壇ランダム生成
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateLuck(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	m_pStatue = CStatueLuck::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));

	return m_pStatue;
}

//--------------------------------------------------------------
// 戦いの祭壇ランダム生成
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateCombat(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	m_pStatue = CStatueCombat::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));

	return m_pStatue;
}


