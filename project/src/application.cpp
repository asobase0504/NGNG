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
#include "mode_fade.h"

#include "skill_data_base.h"
#include "enemy_data_base.h"
#include "item_data_base.h"
#include "abnormal_data_base.h"

/* 外部読込み */
#include "font.h"
#include "texture.h"

/* シーンモード */
#include "title.h"
#include "game.h"
#include "character_select.h"
#include "debug_mode.h"

#include "model_skin_group.h"

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
	m_texture(nullptr),
	m_renderer(nullptr),
	m_taskGroup(nullptr),
	m_fade(nullptr),
	m_mode(nullptr),
	m_sound(nullptr)
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
	m_window = hWnd;

	// 根幹グループの初期化処理
	m_taskGroup = new CTaskGroup;
	if (FAILED(m_taskGroup->Init()))
	{
		return E_FAIL;
	}

	// レンダラーの初期化処理
	m_renderer = CRenderer::GetInstance();
	if (FAILED(m_renderer->Init(hWnd, true)))
	{
		return E_FAIL;
	}

	// 入力処理の初期化処理
	CInput::Create();
	if (FAILED(CInput::GetKey()->Init(hInstance, hWnd, D3DXVECTOR2(CENTER_POS.x, CENTER_POS.y))))
	{
		return E_FAIL;
	}

	// 音楽処理の初期化処理
	m_sound = new CSound;
	if (FAILED(m_sound->Init(hWnd)))
	{
		return E_FAIL;
	}

	// objectXの初期化処理
	m_objectXGroup = new CObjectXGroup;
	m_objectXGroup->LoadAll();

	// Textureの読込み
	m_texture = CTexture::GetInstance();
	m_texture->LoadAll();

	m_modeType = CApplication::MODE_TITLE;	//現在のモード

	m_fade = CModeFade::Create();

	//モードの設定
	SetMode(m_modeType);

	CSkillDataBase::GetInstance();
	CEnemyDataBase::GetInstance();
	CItemDataBase::GetInstance();

	CFont::Load(CFont::FONT_MYOUTYOU);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CApplication::Uninit()
{
	CSkillDataBase::Uninit();
	CEnemyDataBase::Uninit();
	CAbnormalDataBase::Uninit();

	if (m_taskGroup != nullptr)
	{// 終了処理
		m_taskGroup->Uninit();
		delete m_taskGroup;
		m_taskGroup = nullptr;
	}

	if (m_objectXGroup != nullptr)
	{// 終了処理
		m_objectXGroup->UnloadAll();
		delete m_objectXGroup;
		m_objectXGroup = nullptr;
	}
	
	if (m_texture != nullptr)
	{// 終了処理
		m_texture->UnloadAll();
		delete m_texture;
		m_texture = nullptr;
	}

	if (m_renderer != nullptr)
	{// 終了処理

		m_renderer->Uninit();
		delete m_renderer;
		m_renderer = nullptr;
	}

	if (m_sound != nullptr)
	{// 終了処理

		m_sound->Uninit();
		delete m_sound;
		m_sound = nullptr;
	}

	//入力処理の終了処理
	CInput::GetKey()->Uninit();

	CSkinMeshGroup* group = CSkinMeshGroup::GetInstance();
	delete group;
	group = nullptr;
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
	CDebugProc::Print("ポーズ【 F2 】 : %s\n", ppp ? "OFF" : "STOP");
	if (CInput::GetKey()->Trigger(DIK_F2))
	{
		m_taskGroup->Pause(ppp);
		ppp = !ppp;
	}
#endif // _DEBUG

	// 現在の最前面を保存
	HWND activeWindowHandle;
	
	activeWindowHandle = GetForegroundWindow();
	if (m_window != activeWindowHandle && m_isActiveWindowThis)
	{ // 自分が最前にいないなら
		m_isActiveWindowThis = false;
	}
	if (m_window == activeWindowHandle && !m_isActiveWindowThis)
	{ // 自分が最前なら
		m_isActiveWindowThis = true;
	}


	m_renderer->Update();
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CApplication::Draw()
{
	m_renderer->Draw();	// 描画処理
}

//--------------------------------------------------------------
// モードの設定
//--------------------------------------------------------------
void CApplication::SetMode(MODE mode)
{
	m_modeType = mode;
	m_taskGroup->AllRelease();

	switch (mode)
	{
	case CApplication::MODE_TITLE:
		m_mode = new CTitle;
		break;
	case CApplication::MODE_GAME:
		m_mode = new CGame;
		break;
	case CApplication::MODE_SELECT:
		m_mode = new CCharacterSelect;
		break;
	case CApplication::MODE_DEBUG:
		m_mode = new CGame;
		//m_mode = new CDebugMode;
	default:
		break;
	}

	// 初期化処理
	if (FAILED(m_mode->Init()))	//画面サイズ
	{
		//初期化処理が失敗した場合
		return;
	}
}
