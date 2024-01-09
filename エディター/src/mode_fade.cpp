#include "mode_fade.h"

CModeFade::CModeFade()
{
}

CModeFade::~CModeFade()
{
}

CModeFade * CModeFade::Create()
{
	CModeFade * pObject = new CModeFade;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->m_nextMode = CApplication::MODE_TITLE;
	}
	return pObject;
}

void CModeFade::NextMode(CApplication::MODE nextMode)
{
	if (m_fade != FADENON)
	{
		return;
	}

	/* ↓フェードを移行する場合↓ */

	Init();
	m_nextMode = nextMode;
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_fade = FADEIN;
}

void CModeFade::Change()
{
	CApplication::GetInstance()->SetMode(m_nextMode);
}
