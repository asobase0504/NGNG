#include "timer.h"
#include "procedure.h"
#include "text_object.h"
#include "application.h"

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
}

HRESULT CTimer::Init()
{
	CObject::Init();
	m_second = CProcedure::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f + 20.0f, 60.0f, 0.0f), D3DXVECTOR3(18.0f, 18.0f, 0.0f), 0);
	m_second->SetAlign(CProcedure::EAlign::LEFT);
	m_second->SetMinimumDigit(2);

	m_koron = CText::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.9f - 30.0f, 60.0f), D3DXVECTOR2(12.0f, 12.0f),"F");

	m_minutes = CProcedure::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f + 10.0f, 60.0f, 0.0f), D3DXVECTOR3(18.0f, 18.0f, 0.0f), 0);
	m_minutes->SetAlign(CProcedure::EAlign::RIGHT);
	m_minutes->SetMinimumDigit(2);

	SetEndChildren(m_second);
	SetEndChildren(m_minutes);
	SetEndChildren(m_koron);
	return S_OK;
}

void CTimer::Update()
{
	m_time++;
	if (m_time % 60 == 0)
	{
		m_second->AddNumber(1);
		if (m_second->GetNumber() >= 60)
		{
			m_second->SetNumber(0);
			m_minutes->AddNumber(1);
		}
	}
}

CTimer * CTimer::Create()
{
	CTimer* timer = new CTimer;
	timer->Init();
	return timer;
}
