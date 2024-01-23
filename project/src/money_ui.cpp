//==================================================
// score
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "application.h"

#include "money_ui.h"
#include "procedure.h"
#include "debug_proc.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CMONEYUI::CMONEYUI(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMONEYUI::~CMONEYUI()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CMONEYUI::Init()
{
	CObject::Init();

	// �w�i�̍쐬
	m_bg = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bg->SetPos(D3DXVECTOR3(140.0f, 50.0f, 0.0f));
	m_bg->SetSize(D3DXVECTOR3(70.0f, 10.0f, 0.0f));
	m_bg->SetColor(D3DXCOLOR(0.9f, 0.9f, 0.0f, 0.25f));
	SetEndChildren(m_bg);

	m_procedure = CProcedure::Create(D3DXVECTOR3(220.0f,50.0f,0.0f),D3DXVECTOR3(10.0f, 10.0f,0.0f),0);
	m_procedure->SetAlign(CProcedure::EAlign::RIGHT);
	SetEndChildren(m_procedure);

	return S_OK;
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CMONEYUI::Update()
{
	m_procedure->SetNumber(m_money->GetCurrent());
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CMONEYUI *CMONEYUI::Create(CStatus<int>* inMoney)
{
	CMONEYUI* ui = new CMONEYUI;

	assert(ui != nullptr);

	ui->Init();
	ui->m_money = inMoney;

	return ui;
}
