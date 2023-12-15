//**************************************************************
//
// 戦いの祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_combat.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "input.h"
#include "utility.h"
#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueCombat::CStatueCombat()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueCombat::~CStatueCombat()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueCombat::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	CStatue::Init(pos, rot);
	LoadModel("STATUE_COMBAT");
	m_uiText = "戦いを始める";

	return S_OK;
}

//--------------------------------------------------------------
// 選択時
//--------------------------------------------------------------
bool CStatueCombat::Select(CCharacter * selectCharacter)
{
	D3DXVECTOR3 pos = GetPos();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		// 敵の生成
		float randX = FloatRandom(1.5f, 0.5f);
		float randZ = FloatRandom(1.5f, 0.5f);

		CEnemy* enemy = CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(pos.x * randX, pos.y, pos.z * randZ), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);
		enemy->TakeItem(CItemDataBase::ITEM_ELITE);
	}

	m_collisionCylinder->Uninit();
	m_collisionCylinder = nullptr;

	return true;
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueCombat* CStatueCombat::Create(D3DXVECTOR3 pos)
{
	CStatueCombat* pStatuecombat;
	pStatuecombat = new CStatueCombat;
	pStatuecombat->SetPos(pos);
	pStatuecombat->Init();

	return pStatuecombat;
}