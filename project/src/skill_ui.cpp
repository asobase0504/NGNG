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
	m_ground = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ground->SetAnchor(CObject2d::EAnchor::ANCHOR_TOP);
	m_ground->SetSize(D3DXVECTOR3(UI_SIZE, UI_SIZE, 0.0f));

	m_display = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_display->SetAnchor(CObject2d::EAnchor::ANCHOR_TOP);
	m_display->SetSize(D3DXVECTOR3(UI_SIZE, 0.0f, 0.0f));
	m_display->SetColor(D3DXCOLOR(0.15f, 0.15f, 0.15f, 0.75f));

	m_procedure = CProcedure::Create(D3DXVECTOR3(m_ground->GetPos().x + (m_ground->GetSize().x),m_ground->GetPos().y,0.0f), D3DXVECTOR3(30.0f, 30.0f, 30.0f), 1);
	m_ct = 0;

	return S_OK;
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CSkillUI::Update()
{
	if (m_skill->GetCT() != 0)
	{
		m_ct = (int)ceil((float)m_skill->GetCT() / 60.0f);
		m_procedure->SetDisplay(true);
	}
	else
	{
		m_ct = 0;
		m_procedure->SetDisplay(false);
	}

	int maxCT = CSkillDataBase::GetInstance()->GetCT(m_skill->GetName());

	float rate = ((float)m_skill->GetCT()) / maxCT;

	D3DXVECTOR3 size = D3DXVECTOR3(UI_SIZE, UI_SIZE, 0.0f);
	size.y *= rate;
	m_display->SetSize(size);

	m_procedure->SetNumber(m_ct);
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
	ui->m_procedure->SetPos(inPos);
	//ui->m_ctText->SetPos(inPos);
	return ui;
}
