//**************************************************************
//
// マネージャー
// Author : 浜田琉雅
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "task_group.h"
#include "objectX_group.h"
#include "texture.h"
#include "fade.h"

/* シーンモード */
#include "title.h"
#include "game.h"

//==============================================================
// 静的メンバー変数の初期化
//==============================================================
CApplication* CApplication::m_pApplication = nullptr;
const D3DXVECTOR3 CApplication::CENTER_POS = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);

//--------------------------------------------------------------
// シングルトンでのインスタンスの取得
//--------------------------------------------------------------
CApplication * CApplication::GetInstance()
{
	return m_pApplication != nullptr ? m_pApplication : m_pApplication = new CApplication;
}

//--------------------------------------------------------------
// コンストラクト関数
//--------------------------------------------------------------
CApplication::CApplication() :
	m_pTexture(nullptr),
	m_pRenderer(nullptr),
	m_pTaskGroup(nullptr),
	m_pFade(nullptr),
	m_pMode(nullptr),
	m_pSound(nullptr)
{
}

//--------------------------------------------------------------
// デストラクト関数
//--------------------------------------------------------------
CApplication::~CApplication()
{

}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	// Window情報のポインタ保存
	m_hWindow = hWnd;

	// 根幹グループの初期化処理
	m_pTaskGroup = new CTaskGroup;
	if (FAILED(m_pTaskGroup->Init()))
	{
		return E_FAIL;
	}

	// レンダラーの初期化処理
	m_pRenderer = CRenderer::GetInstance();
	if (FAILED(m_pRenderer->Init(hWnd, true)))
	{
		return E_FAIL;
	}

	// 入力処理の初期化処理
	CInput::Create();
	if (FAILED(CInput::GetKey()->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// 音楽処理の初期化処理
	m_pSound = new CSound;
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// objectXの初期化処理
	m_pObjectXGroup = new CObjectXGroup;
	m_pObjectXGroup->LoadAll();

	// Textureの読込み
	m_pTexture = CTexture::GetInstance();
	m_pTexture->LoadAll();

	m_mode = CApplication::MODE_TITLE;	//現在のモード

	//モードの設定
	SetMode(m_mode);

	m_pFade = CFade::Create();

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CApplication::Uninit()
{
	if (m_pTaskGroup != nullptr)
	{// 終了処理
		m_pTaskGroup->Uninit();
		delete m_pTaskGroup;
		m_pTaskGroup = nullptr;
	}

	if (m_pObjectXGroup != nullptr)
	{// 終了処理
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}
	
	if (m_pTexture != nullptr)
	{// 終了処理
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pRenderer != nullptr)
	{// 終了処理

		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pSound != nullptr)
	{// 終了処理

		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//入力処理の終了処理
	CInput::GetKey()->Uninit();

}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CApplication::Update()
{
	//入力処理の更新処理
	CInput::GetKey()->Update();

#ifdef _DEBUG
	static bool ppp = true;
	CDebugProc::Print("ポーズ【 2 】 : %s\n", ppp ? "OFF" : "STOP");
	if (CInput::GetKey()->Trigger(DIK_2))
	{
		m_pTaskGroup->Pause(ppp);
		ppp = !ppp;
	}
#endif // _DEBUG

	m_pRenderer->Update();
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CApplication::Draw()
{
	m_pRenderer->Draw();	// 描画処理
}

//--------------------------------------------------------------
// モードの設定
//--------------------------------------------------------------
void CApplication::SetMode(MODE mode)
{
	m_mode = mode;
	m_pTaskGroup->AllRelease();

	switch (mode)
	{
	case CApplication::MODE_TITLE:
		m_pMode = new CTitle;
		break;
	case CApplication::MODE_GAME:
		m_pMode = new CGame;
		break;
	default:
		break;
	}

	// 初期化処理
	if (FAILED(m_pMode->Init()))	//画面サイズ
	{
		//初期化処理が失敗した場合
		return;
	}
}
