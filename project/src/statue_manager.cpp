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
#include "statue.h"
#include "collision_box.h"
#include "application.h"
#include "utility.h"

#include "map.h"
#include "object_mesh.h"

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
CStatue* CStatueManager::CreateStatue(D3DXVECTOR3 pos, EType type)
{
	CMap* pMap = CMap::GetMap();
	CMesh* pMesh = pMap->GetMapMesh(0);

	D3DXVECTOR3 Meshpos = pMesh->GetPos();

	switch (type)
	{
	case CStatueManager::NONE:
		m_pStatue = CStatue::Create(pos,D3DXVECTOR3(0.0f,0.0f,0.0f));
		break;
	case CStatueManager::BLOOD:
		RandomCreateBlood(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::CHEST:
		RandomCreateChest(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::LUCK:
		RandomCreateLuck(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::COMBAT:
		RandomCreateCombat(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
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


