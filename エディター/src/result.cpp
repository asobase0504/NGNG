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

#include "application.h"
#include "input.h"
#include "mode_fade.h"

//--------------------------------------------------------------
// �R���X�g���N�^
// Author : Buriya Kota
//--------------------------------------------------------------
CResult::CResult(CTaskGroup::EPriority list) : m_title(nullptr)
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

	{// �^�C�g���֍s���{�^���̈ʒu
		m_title = CObject2d::Create();
		m_title->SetPos(center);
		m_title->SetSize(D3DXVECTOR3(100.0f, 30.0f, 0.0f));
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

	if (input->TriggerTouchClick(m_title->GetPos(), m_title->GetSize() * 0.5f))
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
