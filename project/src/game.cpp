﻿//**************************************************************
//
// ゲーム画面
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "statue.h"
#include "statue_manager.h"
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

//==============================================================
// 定数
//==============================================================

//--------------------------------------------------------------
// コンストラクタ
// Author : Yuda Kaito
//--------------------------------------------------------------
CGame::CGame()
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
HRESULT CGame::Init(void)
{
	m_camera = new CCameraGame;
	m_camera->Init();

	m_light = new CLight;
	m_light->Init();

	// プレイヤーの設定
	CPlayer* pPlayer = CPlayerManager::GetInstance()->CreatePlayer(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	m_camera->SetTargetPos(pPlayer->GetPos());

	CHPUI::Create(pPlayer->GetHp());

	// エネミーの生成
	CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);

	// マップの生成
	CMap::Create();

	// アイテムのｓ衛星
	CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(200.0f, 0.0f, 0.0f), CItemDataBase::ITEM_POWER_UP);

	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f),CStatueManager::BLOOD);
	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f), CStatueManager::LUCK);
	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f), CStatueManager::CHEST);
	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f), CStatueManager::COMBAT);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Uninit(void)
{

}

//--------------------------------------------------------------
// 更新
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Update(void)
{
}