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
	CStatue* statue = nullptr;
	switch (type)
	{
	case CStatueManager::BLOOD:
		statue = RandomCreateBlood(pos);
		break;
	case CStatueManager::CHEST:
		statue = RandomCreateChest(pos);
		break;
	case CStatueManager::LUCK:
		statue = RandomCreateLuck(pos);
		break;
	case CStatueManager::COMBAT:
		statue = RandomCreateCombat(pos);
		break;
	case CStatueManager::TELEPORTER:
		statue = CStatueTeleporter::Create(pos);
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
	}
	m_pStatue.push_back(statue);

	return statue;
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

	CStatue* statue;

	if (randomCount != 2)
	{
		statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), randomCount);
		m_pStatue.push_back(statue);
	}
	else
	{
		int rand = IntRandom(4, 1);

		if (rand == 1)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 1);
			m_pStatue.push_back(statue);
		}
		else if (rand == 2)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 3);
			m_pStatue.push_back(statue);
		}
		else
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 4);
			m_pStatue.push_back(statue);
		}
	}

	return statue;
}

//--------------------------------------------------------------
// 血の祭壇ランダム生成
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateBlood(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue = CStatueBlood::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
	m_pStatue.push_back(statue);

	return statue;
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

	CStatue* statue;
	for (int nCnt = 0; nCnt < randomCount; nCnt++)
	{
		float randomPosX = FloatRandom(400.0f, -500.0f);
		float randomPosZ = FloatRandom(500.0f,-415.0f);
		statue = CStatueChest::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
		m_pStatue.push_back(statue);
	}

	return statue;
}

//--------------------------------------------------------------
// 運の祭壇ランダム生成
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateLuck(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue = CStatueLuck::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
	m_pStatue.push_back(statue);

	return statue;
}

//--------------------------------------------------------------
// 戦いの祭壇ランダム生成
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateCombat(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue = CStatueCombat::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
	m_pStatue.push_back(statue);

	return statue;
}

void CStatueManager::AllFuncStatue(std::function<void(CStatue*inStatue)> inFunc)
{
	std::for_each(m_pStatue.cbegin(), m_pStatue.cend(), inFunc);
}