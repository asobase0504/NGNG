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
#include "model_skin_group.h"
#include "model_skin.h"

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
#include "difficult.h"

/* サーバー */
#include "connect.h"

/*  */
#include "pause.h"

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
HRESULT CGame::Init()
{
	CAbnormalDataBase::GetInstance();

	CSkinMeshGroup::GetInstance()->LoadAll();

	m_camera = new CCameraGame;
	m_camera->Init();

	m_light = new CLight;
	m_light->Init();

	// プレイヤーの設定
	CPlayer* pPlayer = CPlayerManager::GetInstance()->CreatePlayer(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	m_controller = new CPlayerController(-1);
	m_controller->Init();
	m_controller->SetToOrder(pPlayer);
	pPlayer->SetController(m_controller);
	pPlayer->OffUpdate();

	((CCameraGame*)m_camera)->SetTargetPos(pPlayer->GetPos());

	/*m_tcp = new ConnectManager;
	m_tcp->Init("127.0.0.1", 13678);*/

	CObject2d* reticle = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	reticle->SetPos(CApplication::CENTER_POS);
	reticle->SetSize(D3DXVECTOR3(16.f, 16.f,0.f));
	reticle->SetTexture("RETICLE");

	m_difficult = CDifficult::Create(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	CreateMap("data/FILE/map/forest_map.json");
	GetMap()->RandomStatueSummon();
	GetMap()->InCharacterList(pPlayer);
	GetMap()->SetIsGame(true);

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CRY);
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Uninit()
{
	/*if (m_tcp != nullptr)
	{
		m_tcp->Uninit();
		delete m_tcp;
		m_tcp = nullptr;
	}*/

	CAbnormalDataBase::Uninit();

	CSkinMeshGroup::GetInstance()->UnloadAll();

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CRY);
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);
}

//--------------------------------------------------------------
// 更新
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Update()
{
	if(CInput::GetKey()->Trigger(DIK_P, -1))
	{
		CPause* pause = new CPause;
		pause->Init();
	}

	//if (m_tcp->GetIsConnect())
	//{
	//	CPlayer* Player = CPlayerManager::GetInstance()->GetPlayer();
	//	CModelData::SSendPack sendData;
	//	sendData.m_PlayData.m_pos = Player->GetPos();
	//	sendData.m_PlayData.m_rot = Player->GetRot();
	//	for (int j = 0; j < 5; j++)
	//	{
	//		sendData.m_haveAbnormal.abnormalData[j] = 0;
	//		sendData.m_haveItem.itemData[j] = 0;
	//	}

	//	sendData.m_PlayData.m_motion = 0;
	//	sendData.m_log = 2;
	//	sendData.m_PlayData.m_pushBomComands = 0;


	//	m_tcp->SendPlayerData(sendData);
	//}
}

