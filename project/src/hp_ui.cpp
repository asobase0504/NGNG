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
	CObject::Init();

	m_size = D3DXVECTOR3(200.0f, 15.0f, 0.0f);
	m_ground = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ground->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_ground->SetSize(m_size);
	m_ground->SetPos(D3DXVECTOR3(50.0f, SCREEN_HEIGHT - 70.0f, 0.0f));
	m_ground->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	m_ground->SetTexture("HP_BAR");

	m_bar = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bar->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_bar->SetSize(m_size);
	m_bar->SetPos(D3DXVECTOR3(50.0f, SCREEN_HEIGHT - 70.0f,0.0f));
	m_bar->SetColor(D3DXCOLOR(0.9f,0.3f,0.3f,1.0f));
	m_bar->SetTexture("HP_BAR");

	m_current = CProcedure::Create(D3DXVECTOR3(190.0f + 50.0f, SCREEN_HEIGHT - 70.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 0);
	m_current->SetAlign(CProcedure::EAlign::RIGHT);
	m_max = CProcedure::Create(D3DXVECTOR3(210.0f + 50.0f, SCREEN_HEIGHT - 70.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 0);
	m_max->SetAlign(CProcedure::EAlign::LEFT);

	SetEndChildren(m_bar);
	SetEndChildren(m_ground);
	SetEndChildren(m_current);
	SetEndChildren(m_max);

	return S_OK;
}

//--------------------------------------------------w
// 更新
//--------------------------------------------------
void CHPUI::Update()
{
	float rate = (float)m_hp->GetCurrent() / (float)m_hp->GetMax();

	D3DXVECTOR3 size = m_size;
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

HRESULT CBossHPUI::Init()
{
	m_size = D3DXVECTOR3(300.0f, 10.0f, 0.0f);
	m_pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 70.0f, 0.0f);
	m_ground = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ground->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_ground->SetSize(m_size);
	m_ground->SetPos(D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, 0.0f));
	m_ground->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	SetEndChildren(m_ground);

	m_bar = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bar->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_bar->SetSize(m_size);
	m_bar->SetPos(D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, 0.0f));
	m_bar->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	SetEndChildren(m_bar);

	m_current = CProcedure::Create(D3DXVECTOR3(m_pos.x - 10.0f, 70.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 0);
	m_current->SetAlign(CProcedure::EAlign::RIGHT);
	SetEndChildren(m_current);
	m_max = CProcedure::Create(D3DXVECTOR3(m_pos.x + 10.0f, 70.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 0);
	m_max->SetAlign(CProcedure::EAlign::LEFT);
	SetEndChildren(m_max);

	return S_OK;
}
