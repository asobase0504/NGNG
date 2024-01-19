#include "teleporter_event_ui.h"
#include "object2d.h"
#include "procedure.h"
#include "text_object.h"
#include "statue_teleporter.h"

const D3DXVECTOR3 CTeleporterEventUI::GROUND_POS	(SCREEN_WIDTH * 0.9f, 120.0f, 0.0f);
const D3DXVECTOR3 CTeleporterEventUI::BAR_SIZE		(80.0f, 8.0f, 0.0f);
const D3DXVECTOR3 CTeleporterEventUI::BAR_POS		(GROUND_POS.x - BAR_SIZE.x, 160.0f, 0.0f);

CTeleporterEventUI::CTeleporterEventUI(CTaskGroup::EPriority list)
{
}

CTeleporterEventUI::~CTeleporterEventUI()
{
}

HRESULT CTeleporterEventUI::Init()
{
	D3DXVECTOR3 size(100.0f, 90.0f, 0.0f);
	m_ground = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ground->SetSize(size);
	m_ground->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.9f, 120.0f, 0.0f));
	m_ground->SetColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.5f));

	size = D3DXVECTOR3(70.0f, 15.0f, 0.0f);
	m_barGround = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_barGround->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_barGround->SetSize(BAR_SIZE);
	m_barGround->SetPos(BAR_POS);
	m_barGround->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	m_barGround->SetTexture("HP_BAR");

	m_bar = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bar->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_bar->SetSize(BAR_SIZE);
	m_bar->SetPos(BAR_POS);
	m_bar->SetColor(D3DXCOLOR(0.85f, 0.85f, 0.3f, 1.0f));
	m_bar->SetTexture("HP_BAR");

	m_chargeText = CText::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f - BAR_SIZE.x, BAR_POS.y - BAR_SIZE.y - 7.5f - 2.0f, 0.0f), D3DXVECTOR3(7.5f, 7.5f, 0.0f), 0, 0, "‘Ï‚¦‚ë");
	m_bosskillText = CText::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f - BAR_SIZE.x, 210.0f, 0.0f), D3DXVECTOR3(7.5f, 7.5f, 0.0f), 0, 0, "ƒ{ƒX‚ð“|‚¹");

	SetEndChildren(m_ground);
	SetEndChildren(m_barGround);
	SetEndChildren(m_bar);
	SetEndChildren(m_chargeText);
	SetEndChildren(m_bosskillText);

	m_completeLine[0] = nullptr;
	m_completeLine[1] = nullptr;
	return S_OK;
}

void CTeleporterEventUI::Update()
{
	if (m_completeLine[0] == nullptr)
	{
		float rate = (float)*m_referenceTime / (float)CStatueTeleporter::CHARGE_TIME;
		if (rate > 1.0f)
		{
			rate = 1.0f;
			m_bar->SetColor(D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f));
			m_chargeText->SetColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));

			m_completeLine[0] = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
			m_completeLine[0]->SetPos(D3DXVECTOR3(GROUND_POS.x, m_chargeText->GetPos().y, 0.0f));
			m_completeLine[0]->SetSize(D3DXVECTOR3(80.0f, 1.0f, 0.0f));
			SetEndChildren(m_completeLine[0]);
		}

		D3DXVECTOR3 size = BAR_SIZE;
		size.x *= rate;
		m_bar->SetSize(size);
	}

	if (m_completeLine[1] == nullptr && *m_referenceIsBossKill == true)
	{
		m_bosskillText->SetColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));

		m_completeLine[1] = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
		m_completeLine[1]->SetPos(D3DXVECTOR3(GROUND_POS.x, m_bosskillText->GetPos().y,0.0f));
		m_completeLine[1]->SetSize(D3DXVECTOR3(80.0f,1.0f,0.0f));
		SetEndChildren(m_completeLine[1]);
	}
}
