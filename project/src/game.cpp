//**************************************************************
//
// ゲーム画面
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "game.h"

/* System系統 */
#include "application.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "camera_game.h"
#include "light.h"
#include "light.h"
#include "utility.h"
#include "mode_fade.h"
#include "map_fade.h"

/* Object系統 */
#include "object_polygon3d.h"
#include "objectX.h"
#include "object_mesh.h"
#include "object_polygon3d.h"

/* Game系統 */
#include "player.h"
#include "enemy.h"
#include "statue.h"
#include "enemy_manager.h"
#include "item_manager.h"
#include "item_data_base.h"
#include "player_manager.h"
#include "map.h"
#include "PlayerController.h"

/* UI系統 */
#include "hp_ui.h"
#include "money_ui.h"
#include "skill_ui.h"

//==============================================================
// 定数
//==============================================================

//--------------------------------------------------------------
// コンストラクタ
// Author : Yuda Kaito
//--------------------------------------------------------------
CGame::CGame() :
	m_map(nullptr)
{
}

//--------------------------------------------------------------
// デストラクタ
// Author : Yuda Kaito
//--------------------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------------------
// 初期化
// Author : Yuda Kaito
//--------------------------------------------------------------
HRESULT CGame::Init()
{
	m_mapFade = CMapFade::Create();
	m_mapFade->NextMap("data/FILE/map/map01.json");

	m_camera = new CCameraGame;
	m_camera->Init();

	m_light = new CLight;
	m_light->Init();

	// プレイヤーの設定
	CPlayer* pPlayer = CPlayerManager::GetInstance()->CreatePlayer(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	pPlayer->OffUpdate();
	m_camera->SetTargetPos(pPlayer->GetPos());

	CHPUI::Create(pPlayer->GetHp());
	CMONEYUI::Create(pPlayer->GetMoney());

	CHPUI::Create(pPlayer->GetHp());
	CMONEYUI::Create(pPlayer->GetMoney());
	CSKILLUI::Create(pPlayer->GetSkill(0));

	// エネミーの生成
	//CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);

//	CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(200.0f, 0.0f, 0.0f), CItemDataBase::ITEM_POWER_UP);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Uninit()
{

}

//--------------------------------------------------------------
// 更新
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Update()
{
	CInput* pInput;
	pInput = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();
	if (pInput->Trigger(DIK_F1))
	{
		pFade->NextMode(CApplication::MODE_DEBUG);
	}
	if (pInput->Trigger(DIK_F5))
	{
		pFade->NextMode(CApplication::MODE_DEBUG);
	}
	if (pInput->Trigger(DIK_6))
	{
		SetChangeMap();
	}
}

void CGame::SetChangeMap()
{
	CPlayerManager::GetInstance()->GetPlayer()->OffUpdate();
	m_mapFade->NextMap(m_map->GetNextMapPath());
}

//--------------------------------------------------------------
// マップの作成
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::ChangeMap(std::string inPath)
{
	if (m_map != nullptr)
	{
		m_map->Uninit();
		m_map = nullptr;
	}

	CPlayerManager::GetInstance()->GetPlayer()->OnUpdate();
	m_map = CMap::Create(inPath);
}
