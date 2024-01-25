#include "pause.h"
#include "object2d.h"
#include "ui_bg.h"
#include "text_object.h"
#include "application.h"
#include "mode_fade.h"

CPause::CPause()
{
}

CPause::~CPause()
{
}

HRESULT CPause::Init()
{
	CInput::GetKey()->SetCursorErase(true);
	CInput::GetKey()->LockCursorPos(false);

	SetPouseUpdate(true);
	m_BG = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_BG->SetPos(CApplication::CENTER_POS);
	m_BG->SetSize(CApplication::CENTER_POS);
	m_BG->SetColor(D3DXCOLOR(0.2f,0.2f,0.2f,0.52f));
	m_BG->SetPouseUpdate(true);
	SetEndChildren(m_BG);
	
	auto CreateUI = [this](CUIBackGround** bg,D3DXVECTOR2 pos)
	{
		D3DXVECTOR2 size(CApplication::CENTER_POS.x * 0.2f, CApplication::CENTER_POS.y * 0.1f);
		*bg = CUIBackGround::Create(pos, size, 1.0f);
		(*bg)->SetPouseUpdate(true);
		SetEndChildren(*bg);
	};

	CreateUI(&m_backBG, D3DXVECTOR2(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y - 150.0f));
	m_backText = CText::Create(D3DXVECTOR2(m_backBG->GetPos().x - 30.0f, m_backBG->GetPos().y),D3DXVECTOR2(10.0f,10.0f),"–ß‚é");
	m_backText->SetPouseUpdate(true);
	SetEndChildren(m_backText);

	CreateUI(&m_retryBG, D3DXVECTOR2(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y));
	m_retryText = CText::Create(D3DXVECTOR2(m_retryBG->GetPos().x - 60.0f, m_retryBG->GetPos().y), D3DXVECTOR2(10.0f, 10.0f), "‚à‚¤ˆê“x");
	m_retryText->SetPouseUpdate(true);
	SetEndChildren(m_retryText);

	CreateUI(&m_endBG, D3DXVECTOR2(CApplication::CENTER_POS.x, CApplication::CENTER_POS.y + 150.0f));
	m_endText = CText::Create(D3DXVECTOR2(m_endBG->GetPos().x - 40.0f, m_endBG->GetPos().y), D3DXVECTOR2(10.0f, 10.0f), "I‚í‚é");
	m_endText->SetPouseUpdate(true);
	SetEndChildren(m_endText);

	CApplication::GetInstance()->GetTaskGroup()->Pause(true);
	m_lag = false;
	return S_OK;
}

void CPause::Uninit()
{
	CApplication::GetInstance()->GetTaskGroup()->Pause(false);
	CTask::Uninit();
}

void CPause::Update()
{
	if (!m_lag)
	{
		m_lag = true;
		return;
	}

	/* Back*/
	CInput* input = CInput::GetKey();
	bool KeyP = input->Trigger(DIK_P, -1);
	bool KeyEscape = input->Trigger(DIK_ESCAPE, -1);
	bool ClickBack = input->TriggerTouchClick(m_backBG->GetPos(), m_backBG->GetSize());

	if (KeyP || KeyEscape || ClickBack)
	{
		Uninit();
		return;
	}

	bool ClickRetry = input->TriggerTouchClick(m_retryBG->GetPos(), m_retryBG->GetSize());
	if (ClickRetry)
	{
		CModeFade* pFade = CApplication::GetInstance()->GetFade();
		pFade->NextMode(CApplication::MODE_GAME);
		Uninit();
		return;
	}

	bool ClickEnd = input->TriggerTouchClick(m_endBG->GetPos(), m_endBG->GetSize());
	if (ClickEnd)
	{
		CModeFade* pFade = CApplication::GetInstance()->GetFade();
		pFade->NextMode(CApplication::MODE_TITLE);
		Uninit();
		return;
	}
}
