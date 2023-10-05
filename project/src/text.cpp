//**************************************************************
//
// テキスト表示するべんり
// Author:hamada ryuuga
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "text.h"
#include "application.h"
#include "renderer.h"
#include <Shlwapi.h>

//--------------------------------------------------------------
// コンストラクト関数
//--------------------------------------------------------------
CText::CText(CTaskGroup::EPriority list) : CObject2d(list)
{
}

//--------------------------------------------------------------
// デストラクト関数
//--------------------------------------------------------------
CText::~CText()
{
}

//--------------------------------------------------------------
// 初期化関数
//--------------------------------------------------------------
HRESULT CText::Init()
{
	m_text = "";
	CObject2d::Init();
	
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	SetTex(PositionVec4(
		0.0f, 1.0f, 0.0f, 1.0f));

	
	// フォントを使えるようにする
	DESIGNVECTOR design;

	AddFontResourceEx(
		"data/font/FZゴンタかな.otf", //ttfファイルへのパス
		FR_PRIVATE,
		&design
	);

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(CApplication::GetInstance()->GetRenderer()->GetDevice(), 38, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("FZゴンタかな"), &m_font);

	m_isRelease = false;
	m_desTimar = 0;

	return S_OK;
}

//--------------------------------------------------------------
// 破棄関数
//--------------------------------------------------------------
void CText::Uninit()
{
	CObject2d::Uninit();

	DESIGNVECTOR design;

	RemoveFontResourceEx(
		TEXT("Data/font/FZゴンタかな.otf"), //ttfファイルへのパス
		FR_PRIVATE,
		&design
	);
	
}

//--------------------------------------------------------------
// 更新関数
//--------------------------------------------------------------
void CText::Update()
{
	CObject2d::Update();

	if (m_isRelease)
	{
		m_desTimar--;

		m_addCount++;

		if (m_addCount >= m_addNumber)
		{
			if (m_addLetter <= m_textSize)
			{
				m_text+=m_allText[m_addLetter];
				if (m_addLetter + 1 <= m_textSize)
				{
					m_text += m_allText[m_addLetter + 1];
				}
				m_addLetter+=2;
			}
			m_addCount = 0;
		}

		CObject2d::SetColor(m_col);

		if (m_desTimar <= 0)
		{
			Uninit();
		}
	}
}

//--------------------------------------------------------------
// 描画関数
//--------------------------------------------------------------
void CText::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();

	RECT rect = { 60, 500, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T(m_text.c_str()));

	m_font->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	// 新規深度値 <= Zバッファ深度値 (初期設定)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//--------------------------------------------------------------
// 生成関数
//--------------------------------------------------------------
CText *CText::Create(Type talkType,int DeleteTime, int SpeedText,const char* Text)
{
	CText * pObject = nullptr;
	pObject = new CText();

	if (pObject != nullptr)
	{
		pObject->Init();

		switch (talkType)
		{
		case CText::GON:
			pObject->SetTexture("GONBOX");
			break;
		case CText::MASUO:
			pObject->SetTexture("MASUOBOX");
			break;
		case CText::MAX:
			break;
		default:
			break;
		}
		pObject->SetPos(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
		pObject->SetSize(D3DXVECTOR3(640.0f, 200.0f, 0.0f));

		pObject->ReleaseTimer(DeleteTime);
		pObject->TextLetter(Text, SpeedText);
	}

	return pObject;
}

//--------------------------------------------------------------
// けすまでの時間設定関数
//--------------------------------------------------------------
void CText::ReleaseTimer(int nTimar)
{
	m_desTimar = nTimar;
	m_desTimarMax = m_desTimar;
	m_isRelease = true;
}

//--------------------------------------------------------------
// けすまでの時間設定関数
//--------------------------------------------------------------
void CText::TextLetter(const char* Text, int SpeedText)
{
	m_allText = Text;
	m_textSize = m_allText.size();
	m_addNumber = SpeedText;
	m_addLetter = 0;
}
