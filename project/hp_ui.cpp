#include "hp_ui.h"
#include "object2d.h"

CHPUI::CHPUI(CTaskGroup::EPriority list)
{
}

CHPUI::~CHPUI()
{
}

HRESULT CHPUI::Init()
{
	m_ground = CObject2d::Create();
	m_ground->SetSize(D3DXVECTOR3(220.0f, 17.0f, 0.0f));
	m_ground->SetPos(D3DXVECTOR3(512.0f, 50.0f, 0.0f));

	m_bar = CObject2d::Create();
	m_bar->SetSize(D3DXVECTOR3(200.0f,15.0f,0.0f));
	m_bar->SetPos(D3DXVECTOR3(512.0f,50.0f,0.0f));
	m_bar->SetColor(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f));
	return S_OK;
}

void CHPUI::Uninit()
{
}

void CHPUI::Update()
{
	float rate = (float)m_hp->GetCurrent() / (float)m_hp->GetMax();

	D3DXVECTOR3 size = D3DXVECTOR3(200.0f, 15.0f, 0.0f);
	size.x *= rate;
	m_bar->SetSize(size);
}

CHPUI* CHPUI::Create(CStatus<int>* inHp)
{
	CHPUI* ui = new CHPUI;

	assert(ui != nullptr);

	ui->Init();
	ui->m_hp = inHp;

	return ui;
}
