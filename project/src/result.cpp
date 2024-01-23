//**************************************************************
//
// result
// Author : Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "result.h"

#include "object2d.h"
#include "text_object.h"

#include "application.h"
#include "input.h"
#include "mode_fade.h"
#include "ui_bg.h"

//--------------------------------------------------------------
// �R���X�g���N�^
// Author : Buriya Kota
//--------------------------------------------------------------
CResult::CResult(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
// Author : Buriya Kota
//--------------------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------------------
// ������
// Author : Buriya Kota
//--------------------------------------------------------------
HRESULT CResult::Init()
{
	CInput::GetKey()->SetCursorErase(true);
	CInput::GetKey()->LockCursorPos(false);

	D3DXVECTOR3 center = CApplication::CENTER_POS;

	{// ��������Ƃ����w�i
		m_bg = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_bg->SetPos(center);
		m_bg->SetSize(center);
		m_bg->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f));
	}

	{// ���I��
		m_loseBG = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_loseBG->SetPos(D3DXVECTOR3(center.x, 50.0f, 0.0f));
		m_loseBG->SetSize(D3DXVECTOR3(center.x * 0.8f, 20.0f, 0.0f));
		m_loseBG->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));

		m_loseText = CText::Create(D3DXVECTOR2(center.x - center.x * 0.8f, 50.0f), D3DXVECTOR2(20.0f, 20.0f), "�s�k");
	}

	{
		D3DXVECTOR2 pos(CApplication::CENTER_POS.x * 1.5f, CApplication::CENTER_POS.y - 15.0f);
		float posTextY = pos.y - 260.0f + 30.0f;

		m_infoBG = CUIBackGround::Create(D3DXVECTOR2(CApplication::CENTER_POS.x * 1.5f, CApplication::CENTER_POS.y - 15.0f), D3DXVECTOR2(240.0f, 260.0f), 1.0f);
		m_infoTextBGOutLine = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_infoTextBGOutLine->SetPos(D3DXVECTOR3(pos.x, posTextY, 0.0f));
		m_infoTextBGOutLine->SetSize(D3DXVECTOR3(240.0f - 5.0f + 1.5f, 20.0f + 1.5f, 0.0f));
		m_infoTextBGOutLine->SetColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
		m_infoTextBG = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_infoTextBG->SetPos(D3DXVECTOR3(pos.x, posTextY, 0.0f));
		m_infoTextBG->SetSize(D3DXVECTOR3(240.0f - 5.0f, 20.0f, 0.0f));
		m_infoTextBG->SetColor(D3DXCOLOR(0.4f, 0.3f, 0.2f, 1.0f));
		m_infoText = CText::Create(D3DXVECTOR2(pos.x - 60.0f + 12.5f, posTextY), D3DXVECTOR2(12.5f, 12.5f), "���");
	}

	{
		D3DXVECTOR2 pos(CApplication::CENTER_POS.x * 0.5f, CApplication::CENTER_POS.y + 25.0f);
		float posTextY = pos.y - 300.0f + 30.0f;
		m_dataBG = CUIBackGround::Create(D3DXVECTOR2(pos), D3DXVECTOR2(240.0f, 300.0f), 1.0f);
		m_dataTextBGOutLine = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_dataTextBGOutLine->SetPos(D3DXVECTOR3(pos.x, posTextY, 0.0f));
		m_dataTextBGOutLine->SetSize(D3DXVECTOR3(240.0f - 5.0f + 1.5f, 20.0f + 1.5f, 0.0f));
		m_dataTextBGOutLine->SetColor(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
		m_dataTextBG = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_dataTextBG->SetPos(D3DXVECTOR3(pos.x, posTextY, 0.0f));
		m_dataTextBG->SetSize(D3DXVECTOR3(240.0f - 5.0f, 20.0f, 0.0f));
		m_dataTextBG->SetColor(D3DXCOLOR(0.4f, 0.3f, 0.2f, 1.0f));
		m_dataText = CText::Create(D3DXVECTOR2(pos.x - 60.0f, posTextY), D3DXVECTOR2(12.5f, 12.5f), "�f�[�^");

	}

	{
		D3DXVECTOR2 pos(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.925f);

		m_backBGOutLine = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_backBGOutLine->SetPos(D3DXVECTOR3(pos.x,pos.y, 0.0f));
		m_backBGOutLine->SetSize(D3DXVECTOR3(60.0f, 30.0f, 0.0f));
		m_backBGOutLine->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_backBG = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_backBG->SetPos(D3DXVECTOR3(pos.x, pos.y,0.0f));
		m_backBG->SetSize(D3DXVECTOR3(57.0f, 27.0f, 0.0f));
		m_backBG->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
		m_backText = CText::Create(D3DXVECTOR2(pos.x - 30.0f, pos.y),D3DXVECTOR2(10.0f,10.0f),"�I��");
	}

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
// Author : Buriya Kota
//--------------------------------------------------------------
void CResult::Update()
{
	CInput* input;
	input = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();

	if (input->TriggerTouchClick(m_backBG->GetPos(), m_backBG->GetSize()))
	{
		pFade->NextMode(CApplication::MODE_TITLE);
	}
}

//--------------------------------------------------------------
// ����
// Author : Buriya Kota
//--------------------------------------------------------------
CResult* CResult::Create()
{
	CResult* pResult = nullptr;
	pResult = new CResult;

	if (pResult != nullptr)
	{
		pResult->Init();
	}
	else
	{
		assert(false);
	}

	return pResult;
}
