//**************************************************************
//
// HPバー
// Author : Yuda Kaito
//
//**************************************************************

// include
#include "hp_ui.h"
#include "object2d.h"
#include "procedure.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CHPUI::CHPUI(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CHPUI::~CHPUI()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CHPUI::Init()
{
	m_ground = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ground->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_ground->SetSize(D3DXVECTOR3(200.0f, 15.0f, 0.0f));
	m_ground->SetPos(D3DXVECTOR3(50.0f, SCREEN_HEIGHT - 70.0f, 0.0f));
	m_ground->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));

	m_bar = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bar->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_bar->SetSize(D3DXVECTOR3(200.0f,15.0f,0.0f));
	m_bar->SetPos(D3DXVECTOR3(50.0f, SCREEN_HEIGHT - 70.0f,0.0f));
	m_bar->SetColor(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f));

	m_current = CProcedure::Create(D3DXVECTOR3(180.0f, SCREEN_HEIGHT - 70.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), 0);
	m_max = CProcedure::Create(D3DXVECTOR3(270.0f, SCREEN_HEIGHT - 70.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), 0);
	return S_OK;
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CHPUI::Update()
{
	float rate = (float)m_hp->GetCurrent() / (float)m_hp->GetMax();

	D3DXVECTOR3 size = D3DXVECTOR3(200.0f, 15.0f, 0.0f);
	size.x *= rate;
	m_bar->SetSize(size);

	m_current->SetNumber(m_hp->GetCurrent());
	m_max->SetNumber(m_hp->GetMax());

}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CHPUI* CHPUI::Create(CStatus<int>* inHp)
{
	CHPUI* ui = new CHPUI;

	assert(ui != nullptr);

	ui->Init();
	ui->m_hp = inHp;

	return ui;
}
