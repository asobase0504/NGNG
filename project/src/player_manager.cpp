//**************************************************************
//
// プレイヤー管理
// Author : 梶田大夢
//
//**************************************************************

// include
#include "player_manager.h"
#include "collision_sphere.h"
#include "PlayerController.h"
#include "player.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"

//--------------------------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------------------------
CPlayerManager* CPlayerManager::m_playerManager = nullptr;

//--------------------------------------------------------------
// シングルトンでのインスタンスの取得
//--------------------------------------------------------------
CPlayerManager* CPlayerManager::GetInstance()
{
	if (m_playerManager == nullptr)
	{
		m_playerManager = new CPlayerManager;
	}
	return m_playerManager;
}

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CPlayerManager::CPlayerManager()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CPlayerManager::~CPlayerManager()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CPlayerManager::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CPlayerManager::Uninit()
{
	if (m_playerManager != nullptr)
	{
		m_playerManager = nullptr;
	}
	CTask::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CPlayerManager::Update()
{
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CPlayerManager::Draw()
{
}

//--------------------------------------------------------------
// 生成処理
//--------------------------------------------------------------
CPlayer* CPlayerManager::CreatePlayer(D3DXVECTOR3 pos)
{
	m_pPlayer = CPlayer::Create(pos);

	return m_pPlayer;
}