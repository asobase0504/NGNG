//**************************************************************
//
// ���� ( �^�C�g�� )
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

#include "mouse_object.h"

#include "ui_bg.h"
#include "text_object.h"

//=============================================================================
// �R���X�g���N�^
//--------------------------------------------------------------
CTitle::CTitle()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CTitle::Init(void)
{
	CMouseObject* mouseObj = new CMouseObject;
	mouseObj->Init();
	SetEndChildren(mouseObj);

	// ���C�g
	CLight* light = new CLight;
	light->Init();

	{
		m_camera = new CTitleCamera;
		m_camera->Init();

		// �J�����̐ݒ�
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

		// �����}�b�v
		CApplication::GetInstance()->GetModeClass()->CreateMap("data/FILE/map/forest_map_title.json");
	}

	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_CRY);

	{
		D3DXVECTOR2 pos(CApplication::CENTER_POS.x + 400.0f, 600.0f);
		CUIBackGround::Create(pos, D3DXVECTOR2(200.0f, 30.0f), 1.0f);
		CText::Create(pos, D3DXVECTOR2(25.0f, 25.0f), "�n�߂�");
	}

	return S_OK;
}

//--------------------------------------------------------------
// �j��
//--------------------------------------------------------------
void CTitle::Uninit()
{
	CMode::Uninit();
	CApplication::GetInstance()->GetSound()->Stop();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CTitle::Update()
{
	CInput* pInput;
	pInput = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();

	bool ClickRetry = pInput->TriggerTouchClick(D3DXVECTOR3(CApplication::CENTER_POS.x + 400.0f, 600.0f,0.0f), D3DXVECTOR3(200.0f, 30.0f,0.0f));
	if (pInput->Trigger(DIK_RETURN,-1) || ClickRetry)
	{
		pFade->NextMode(CApplication::MODE_GAME);
	}

}
