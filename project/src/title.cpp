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

	// カメラ
	CCamera* camera = new CCamera;
	camera->Init();

	{
		CObjectX* testX = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		testX->LoadModel("BOX");
		testX->SetMoveRot(D3DXVECTOR3(0.0f, 0.01f, 0.0f));
		testX->CalculationVtx();
	}

	{
		CObject2d* titleBg = CObject2d::Create();
		titleBg->SetPos(CApplication::CENTER_POS);
		titleBg->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.25f));
		titleBg->SetSize(CApplication::CENTER_POS * 0.9f);
	}

	//{
	//	CObjectPolygon3D* test = CObjectPolygon3D::Create();
	//	test->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	test->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//}
	return S_OK;
}

//--------------------------------------------------------------
// 破棄
//--------------------------------------------------------------
void CTitle::Uninit(void)
{
	CApplication::GetInstance()->GetSound()->Stop();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CTitle::Update(void)
{
	CInput* pInput;
	pInput = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();

	if (pInput->Trigger(DIK_F1))
	{
		pFade->NextMode(CApplication::MODE_DEBUG);
	}

	if (pInput->Trigger(DIK_K))
	{
		pFade->NextMode(CApplication::MODE_SELECT);
	}
}
