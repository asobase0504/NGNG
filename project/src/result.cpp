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

//--------------------------------------------------------------
// コンストラクタ
// Author : Buriya Kota
//--------------------------------------------------------------
CResult::CResult(CTaskGroup::EPriority list) : m_title(nullptr)
{
}

//--------------------------------------------------------------
// デストラクタ
// Author : Buriya Kota
//--------------------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------------------
// 初期化
// Author : Buriya Kota
//--------------------------------------------------------------
HRESULT CResult::Init()
{
	CInput::GetKey()->SetCursorErase(true);
	CInput::GetKey()->LockCursorPos(false);

	D3DXVECTOR3 center = CApplication::CENTER_POS;

	{// タイトルへ行くボタンの位置
		m_bg = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_bg->SetPos(center);
		m_bg->SetSize(center);
		m_bg->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f));
	}

	{// タイトルへ行くボタンの位置
		m_title = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_title->SetPos(center);
		m_title->SetSize(D3DXVECTOR3(100.0f, 30.0f, 0.0f));
	}

	{
		m_text = CText::Create(D3DXVECTOR2(center.x + 200.0f,center.y + 200.0f),D3DXVECTOR2(25.0f,25.0f),"終了");
	}

	return S_OK;
}

//--------------------------------------------------------------
// 更新
// Author : Buriya Kota
//--------------------------------------------------------------
void CResult::Update()
{
	CInput* input;
	input = CInput::GetKey();

	CModeFade* pFade = CApplication::GetInstance()->GetFade();

	if (input->TriggerTouchClick(m_title->GetPos(), m_title->GetSize() * 0.5f))
	{
		pFade->NextMode(CApplication::MODE_TITLE);
	}
}

//--------------------------------------------------------------
// 生成
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
