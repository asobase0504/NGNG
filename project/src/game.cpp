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

/* サーバー */
#include "connect.h"

#include "model_skin.h"

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
	CInput::GetKey()->SetCursorErase(false);
	CInput::GetKey()->LockCursorPos(true);

	// 虚無マップ
	m_map = CMap::GetMap("data/FILE/map/map01.json");

	m_mapFade = CMapFade::Create();
	m_mapFade->NextMap("data/FILE/map/map01.json");

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
	m_camera->SetTargetPos(pPlayer->GetPos());

	CHPUI::Create(pPlayer->GetHp());
	CMONEYUI::Create(pPlayer->GetMoney());

	for (int i = 0; i < 4; i++)
	{
		CSkillUI::Create(D3DXVECTOR3(1000.0f + 55.0f * i, SCREEN_HEIGHT - 90.0f, 0.0f), pPlayer->GetSkill(i));
	}

	CSkinMeshGroup::GetInstance()->LoadAll();

	m_skin = CSkinMesh::Create("KENGOU");
	m_skin->SetPos(D3DXVECTOR3(50.f, 0.f, 0.f));

	//m_tcp = new CClient;
	//m_tcp->Init("127.0.0.1", 13567);

	CObject2d* reticle = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	reticle->SetPos(CApplication::CENTER_POS);
	reticle->SetSize(D3DXVECTOR3(32.f, 32.f,0.f));
	reticle->SetTexture("RETICLE");
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

	CItemDataBase::Uninit();

	CSkinMeshGroup::GetInstance()->Unload("KENGOU");
	CSkinMeshGroup::GetInstance()->Unload("SKE");

	CInput::GetKey()->SetCursorErase(true);
	CInput::GetKey()->LockCursorPos(false);
}

//--------------------------------------------------------------
// 更新
// Author : Yuda Kaito
//--------------------------------------------------------------
void CGame::Update()
{
	if (CApplication::GetInstance()->IsActiveWindow())
	{
		CInput::GetKey()->SetCursorErase(false);
		CInput::GetKey()->LockCursorPos(true);
	}
	else
	{
		CInput::GetKey()->SetCursorErase(true);
		CInput::GetKey()->LockCursorPos(false);
	}

	CInput* pInput;
	pInput = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();
	if (pInput->Trigger(DIK_F1))
	{
		//pFade->NextMode(CApplication::MODE_DEBUG);
	}
	if (pInput->Trigger(DIK_F5))
	{
		pFade->NextMode(CApplication::MODE_DEBUG);
	}
	if (pInput->Trigger(DIK_6))
	{
		SetChangeMap();
	}
	if (pInput->Trigger(DIK_C))
	{
		m_skin->ChangeAnim(1);
	}
	if (pInput->Trigger(DIK_V))
	{
		m_skin->ChangeAnim(0);
	}
	if (pInput->Trigger(DIK_X))
	{
		CSkinMesh* skin = CSkinMesh::Create("KENGOU");
		skin->SetPos(D3DXVECTOR3(50.f, 0.f, 50.f));
	}

	/*if (m_tcp->GetIsConnect())
	{
		CPlayer* Player = CPlayerManager::GetInstance()->GetPlayer();
		CModelData::SSendEnemy sendData;
		sendData.m_pos = Player->GetPos();
		sendData.m_rot = Player->GetRot();
		for (int j = 0; j < 5; j++)
		{
			sendData.m_haveAbnormal.abnormalData[j] = 0;
			sendData.m_haveItem.itemData[j] = 0;
		}

		sendData.m_motion = 0;
		sendData.m_log = 2;
		sendData.m_pushBomComands = 0;


		m_tcp->SendPlayerData(sendData);
	}*/
	

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
	CApplication::GetInstance()->GetTaskGroup()->AllProcess([](CTask* inTask)
	{
		if (!inTask->IsMapChangeRelese())
		{
			return;
		}

		inTask->Uninit();
	});

	if (m_map != nullptr)
	{
		m_map = nullptr;
	}

	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	player->OnUpdate();
	m_map = CMap::GetMap(inPath);
	m_map->InCharacterList(player);
}
