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
// 静的メンバ変数
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CMONEYUI::CMONEYUI(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMONEYUI::~CMONEYUI()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CMONEYUI::Init()
{
	m_procedure = CProcedure::Create(D3DXVECTOR3(220.0f,50.0f,0.0f),D3DXVECTOR3(15.0f,15.0f,0.0f),0);
	m_procedure->SetAlign(CProcedure::EAlign::RIGHT);
	SetEndChildren(m_procedure);

	return S_OK;
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CMONEYUI::Update()
{
	m_procedure->SetNumber(m_money->GetCurrent());
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CMONEYUI *CMONEYUI::Create(CStatus<int>* inMoney)
{
	CMONEYUI* ui = new CMONEYUI;

	assert(ui != nullptr);

	ui->Init();
	ui->m_money = inMoney;

	return ui;
}
