//**************************************************************
//
// フェード設定
// Author : Hamada Ryuuga
//
//**************************************************************
//==============================================================
// include
//==============================================================
#include "fade.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CFade::CFade() : CObject2d(CTaskGroup::LEVEL_FADE)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CFade::~CFade()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CFade::Init(void)
{
	AttachProtect();
	// 現在のモーション番号の保管
	CObject2d::Init();
	m_fadeSp = 0.07f;
	m_fadeSet = 0.0f;
	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSize(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	SetType(CObject::EType::MODE);
	m_fade = FADENON;
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CFade::Uninit(void)
{
	// 現在のモーション番号の保管
	 CObject2d::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CFade::Update(void)
{
	CObject2d::Update();
	if (m_fade != FADENON)
	{
		// 現在のモーション番号の保管
		if (m_fade == FADEOUT)
		{
			AddColorAlpha(-m_fadeSp);
		}

		if (m_fade == FADEIN)
		{
			AddColorAlpha(m_fadeSp);
		}

		if (GetColorAlpha() >= 1.0f)
		{
			m_fade = FADEOUT;
			SetColorAlpha(1.0f);
			Change();
		}
		if (GetColorAlpha() <= 0.0f)
		{
			m_fade = FADENON;
			SetColorAlpha(0.0f);
		}
	}
}

void CFade::Start()
{
	if (m_fade != FADENON)
	{
		return;
	}

	/* ↓フェードを移行する場合↓ */

	Init();
	m_fade = FADEIN;
}
