//**************************************************************
//
// �L�����N�^�[�I�����
// Author : ���c�喲
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "character_select.h"
#include "application.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

#include "camera.h"
#include "light.h"
#include "objectX.h"
#include "object_polygon3d.h"

//=============================================================================
// �R���X�g���N�^
//--------------------------------------------------------------
CCharacterSelect::CCharacterSelect()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CCharacterSelect::~CCharacterSelect()
{
}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CCharacterSelect::Init(void)
{
	// ���C�g
	CLight* light = new CLight;
	light->Init();

	// �J����
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
// �j��
//--------------------------------------------------------------
void CCharacterSelect::Uninit(void)
{
	CApplication::GetInstance()->GetSound()->Stop();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CCharacterSelect::Update(void)
{
	CInput* pInput;
	pInput = CInput::GetKey();

	CFade* pFade = CApplication::GetInstance()->GetFade();

	if (pInput->Trigger(DIK_K))
	{
		pFade->NextMode(CApplication::MODE_DEBUG);
	}
}
