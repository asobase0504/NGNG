//**************************************************************
//
// 制作 ( タイトル )
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "title.h"
#include "application.h"
#include "input.h"
#include "sound.h"
#include "mode_fade.h"

#include "camera.h"
#include "light.h"
#include "objectX.h"
#include "object_polygon3d.h"

#include "map.h"
#include "map_fade.h"
#include "camera_title.h"

//=============================================================================
// コンストラクタ
//--------------------------------------------------------------
CTitle::CTitle()
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CTitle::Init(void)
{
	// ライト
	CLight* light = new CLight;
	light->Init();

	{
		m_camera = new CTitleCamera;
		m_camera->Init();

		// カメラの設定
		((CTitleCamera*)m_camera)->SetPosR(D3DXVECTOR3(0.0f,500.0f,0.0f));
	}

	{
		D3DXVECTOR3 pos = CApplication::CENTER_POS;

		CObject2d* sky = CObject2d::Create();
		sky->SetSize(CApplication::CENTER_POS);
		sky->SetPos(CApplication::CENTER_POS);
		sky->SetColor(D3DXCOLOR(0.8f, 0.8f, 1.0f, 1.0f));

		CObject2d* titleLogo = CObject2d::Create(CTaskGroup::LEVEL_2D_UI);
		titleLogo->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		titleLogo->SetSize(CApplication::CENTER_POS * 0.5f);
		titleLogo->SetPos(D3DXVECTOR3(pos.x, titleLogo->GetSize().y, 0.0f));
		titleLogo->SetTexture("TITLE_LOGO");

		// 虚無マップ
		CApplication::GetInstance()->GetModeClass()->CreateMap("data/FILE/map/map03.json");
	}

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CRY);

	return S_OK;
}

//--------------------------------------------------------------
// 破棄
//--------------------------------------------------------------
void CTitle::Uninit()
{
	CMode::Uninit();
	CApplication::GetInstance()->GetSound()->Stop();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CTitle::Update()
{
	CInput* pInput;
	pInput = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();

	if (pInput->Trigger(DIK_RETURN,-1))
	{
		pFade->NextMode(CApplication::MODE_GAME);
	}
}
