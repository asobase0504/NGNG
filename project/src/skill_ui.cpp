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
#include "skill_data_base.h"
#include "text_object.h"

//**************************************************
// 静的メンバ変数
//**************************************************
const float CSkillUI::UI_SIZE = 25.0f;


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CSkillUI::CSkillUI(CTaskGroup::EPriority list)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CSkillUI::~CSkillUI()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CSkillUI::Init()
{
	D3DXVECTOR3 pos(550.f, 250.f, 0.f);
	D3DXVECTOR3 size(UI_SIZE, UI_SIZE,0.f);
	m_bg = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bg->SetSize(D3DXVECTOR3(UI_SIZE + 1.5f, UI_SIZE + 1.5f, 0.0f));

	m_ground = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ground->SetAnchor(CObject2d::EAnchor::ANCHOR_TOP);
	m_ground->SetSize(D3DXVECTOR3(UI_SIZE, UI_SIZE, 0.0f));

	m_display = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_display->SetAnchor(CObject2d::EAnchor::ANCHOR_TOP);
	m_display->SetSize(D3DXVECTOR3(UI_SIZE, 0.0f, 0.0f));
	m_display->SetColor(D3DXCOLOR(0.15f, 0.15f, 0.15f, 0.75f));

	m_procedure = CProcedure::Create(D3DXVECTOR3(m_ground->GetPos().x + (m_ground->GetSize().x),m_ground->GetPos().y + (m_ground->GetSize().y),0.0f), D3DXVECTOR3(25.0f, 25.0f, 25.0f), 1);
	m_ct = 0;

	return S_OK;
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CSkillUI::Update()
{
	if (m_skill->GetStock() == m_skill->GetMaxStock())
	{
		m_display->SetDisplay(false);
		m_procedure->SetDisplay(false);
		m_bg->SetDisplay(true);
		m_ground->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		// クールダウンの数字を描画するか否か
		if (m_skill->GetStock() == 0)
		{ // stockが切れた
			m_ct = (int)ceil((float)m_skill->GetCT() / 60.0f);
			m_procedure->SetNumber(m_ct);
			m_procedure->SetDisplay(true);
			m_bg->SetDisplay(false);

			m_ground->SetColor(D3DXCOLOR(0.65f,0.65f,0.65f,1.0f));
		}
		else
		{ // まだstockがある
			m_procedure->SetDisplay(false);
			m_bg->SetDisplay(true);
			m_ground->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// ゲージの作成
		m_display->SetDisplay(true);
		int maxCT = CSkillDataBase::GetInstance()->GetCT(m_skill->GetName());
		float rate = ((float)m_skill->GetCT()) / maxCT;
		D3DXVECTOR3 size = D3DXVECTOR3(UI_SIZE, UI_SIZE, 0.0f);
		size.y *= rate;
		m_display->SetSize(size);
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CSkillUI *CSkillUI::Create(const D3DXVECTOR3& inPos, CSkill* inSkill)
{
	CSkillUI* ui = new CSkillUI;

	assert(ui != nullptr);

	ui->Init();
	ui->m_skill = inSkill;
	ui->m_ground->SetPos(inPos);
	ui->m_ground->SetTexture(CSkillDataBase::GetInstance()->GetInfo(ui->m_skill->GetName()).texKey);
	ui->m_display->SetPos(inPos);
	D3DXVECTOR3 pos = inPos;
	pos.y += UI_SIZE;
	ui->m_bg->SetPos(pos);
	ui->m_procedure->SetPos(pos);
	return ui;
}
