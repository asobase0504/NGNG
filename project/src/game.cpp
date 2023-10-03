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
#include "player.h"
#include "camera.h"
#include "light.h"

/* Sestem系統 */
#include "application.h"
#include "fade.h"
#include "sound.h"
#include "input.h"
#include "utility.h"

/* 3D系統 */

/* Object系統 */

//==============================================================
// 定数
//==============================================================

//-----------------------------------------------------------------------------
// コンストラクタ
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
CGame::CGame()
{
}

//-----------------------------------------------------------------------------
// デストラクタ
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
CGame::~CGame()
{
}

//-----------------------------------------------------------------------------
// 初期化
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
HRESULT CGame::Init(void)
{
	//カメラの設定
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//ライトの設定
	m_pLight = new CLight;
	m_pLight->Init();

	//プレイヤーの設定
	m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CGame::Uninit(void)
{
}

//-----------------------------------------------------------------------------
// 更新
// Author : Yuda Kaito
//-----------------------------------------------------------------------------
void CGame::Update(void)
{
}
