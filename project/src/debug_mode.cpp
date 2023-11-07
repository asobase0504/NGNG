//**************************************************************
//
// デバッグモード
// Author : 梶田大夢
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "debug_mode.h"
#include "player.h"
#include "enemy.h"
#include "statue.h"
#include "enemy_manager.h"
#include "item_manager.h"
#include "item_data_base.h"
#include "player_manager.h"
#include "camera.h"
#include "light.h"
#include "object_polygon3d.h"
#include "PlayerController.h"

/* System系統 */
#include "application.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "camera_game.h"
#include "light.h"
#include "utility.h"

/* 3D系統 */
#include "map.h"

/* Object系統 */
#include "object_polygon3d.h"
#include "objectX.h"
#include "object_mesh.h"

#include "hp_ui.h"
#include "money_ui.h"

//==============================================================
// 定数
//==============================================================

//--------------------------------------------------------------
// コンストラクタ
// Author : 梶田大夢
//--------------------------------------------------------------
CDebugMode::CDebugMode()
{
}

//--------------------------------------------------------------
// デストラクタ
// Author : 梶田大夢
//--------------------------------------------------------------
CDebugMode::~CDebugMode()
{
}

//--------------------------------------------------------------
// 初期化
// Author : 梶田大夢
//--------------------------------------------------------------
HRESULT CDebugMode::Init(void)
{
	m_camera = new CCameraGame;
	m_camera->Init();

	m_light = new CLight;
	m_light->Init();

	// プレイヤーの設定
	CPlayer* pPlayer = CPlayerManager::GetInstance()->CreatePlayer(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	m_camera->SetTargetPos(pPlayer->GetPos());

	CHPUI::Create(pPlayer->GetHp());
	CMONEYUI::Create(pPlayer->GetMoney());

	// エネミーの生成
	//CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);

	// マップの生成
	CMap::Create();

	// アイテムのｓ衛星
	//	CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(200.0f, 0.0f, 0.0f), CItemDataBase::ITEM_POWER_UP);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
// Author : 梶田大夢
//--------------------------------------------------------------
void CDebugMode::Uninit(void)
{

}

//--------------------------------------------------------------
// 更新
// Author : 梶田大夢
//--------------------------------------------------------------
void CDebugMode::Update(void)
{
	CInput* pInput;
	pInput = CInput::GetKey();

	CFade* pFade = CApplication::GetInstance()->GetFade();

	// Tキーでタイトル
	if (pInput->Trigger(DIK_T))
	{
		pFade->NextMode(CApplication::MODE_TITLE);
	}

	// Sキーで選択画面
	if (pInput->Trigger(DIK_C))
	{
		pFade->NextMode(CApplication::MODE_SELECT);
	}
}