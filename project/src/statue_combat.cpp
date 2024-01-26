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
#include "game.h"
#include "application.h"
#include "difficult.h"
#include "sound.h"

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

	SetMark("FIGHT");

	return S_OK;
}

//--------------------------------------------------------------
// 選択時
//--------------------------------------------------------------
bool CStatueCombat::Select(CCharacter * selectCharacter)
{
	using enemyType = CEnemyDataBase::EEnemyType;

	D3DXVECTOR3 pos = GetPos();

	CDifficult *pDiff = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetDifficult();
	int level = pDiff->GetEnemyLevel();

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		// 敵の生成
		float randX = FloatRandom(300.0f, -300.0f);
		float randZ = FloatRandom(300.0f, -300.0f);

		enemyType enemyType = enemyType::TENGU;
		CEnemy* enemy = CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(pos.x + randX, pos.y, pos.z + randZ), enemyType, level);
		enemy->TakeItem(CItemDataBase::ITEM_ELITE);
		enemy->SetIsElite();
	}

	DeleteMark();
	m_collisionCylinder->Uninit();
	m_collisionCylinder = nullptr;

	// sound
	CApplication::GetInstance()->GetSound()->Play(CSound::LEVEL_SE_STATUE);

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