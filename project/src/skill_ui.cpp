//==================================================
// skillUI
// Author: 梶田大夢
//==================================================

//**************************************************
// include
//**************************************************
#include "application.h"

#include "skill_ui.h"
#include "procedure.h"
#include "debug_proc.h"

//**************************************************
// 静的メンバ変数
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CSKILLUI::CSKILLUI(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CSKILLUI::~CSKILLUI()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CSKILLUI::Init()
{
	m_ground = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ground->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_ground->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_ground->SetPos(D3DXVECTOR3(980.0f, SCREEN_HEIGHT - 70.0f, 0.0f));
	m_ground->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));

	m_display = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_display->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_display->SetSize(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	m_display->SetPos(D3DXVECTOR3(980.0f, SCREEN_HEIGHT - 70.0f, 0.0f));
	m_display->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.3f));

	m_procedure = CProcedure::Create(D3DXVECTOR3(m_ground->GetPos().x + (m_ground->GetSize().x),m_ground->GetPos().y,0.0f), D3DXVECTOR3(30.0f, 30.0f, 30.0f), 1);
	m_ct = 0;

	return S_OK;
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CSKILLUI::Update()
{
	if (m_skill->GetCT() > 60)
	{
		m_ct = m_skill->GetCT() / 60;
	}
	else
	{
		m_skill->SetCT(0);
		m_ct = 0;
		D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		m_display->SetSize(size);
	}

	float rate = ((float)m_skill->GetCT() - 60.0f) / 240.0f;

	D3DXVECTOR3 size = D3DXVECTOR3(65.0f, 50.0f, 0.0f);
	size.x *= rate;
	m_display->SetSize(size);

	m_procedure->SetNumber(m_ct);
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CSKILLUI *CSKILLUI::Create(CSkill* inSkill)
{
	CSKILLUI* ui = new CSKILLUI;

	assert(ui != nullptr);

	ui->Init();
	ui->m_skill = inSkill;

	return ui;
}
