#include "teleporter_event_ui.h"
#include "object2d.h"
#include "procedure.h"
#include "text_object.h"
#include "statue_teleporter.h"

const D3DXVECTOR3 CTeleporterEventUI::GROUND_POS	(SCREEN_WIDTH * 0.9f, 120.0f, 0.0f);
const D3DXVECTOR3 CTeleporterEventUI::BAR_SIZE		(80.0f, 15.0f, 0.0f);
const D3DXVECTOR3 CTeleporterEventUI::BAR_POS		(SCREEN_WIDTH * 0.9f - BAR_SIZE.x, 170.0f, 0.0f);

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
	m_ground->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.5f));

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

	m_progress = CProcedure::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f + 50.0f, 170.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 0);
	m_progress->SetAlign(CProcedure::EAlign::CENTER);
	m_progress->SetNumber(0);

	m_text = CText::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.9f, 190.0f, 0.0f), D3DXVECTOR3(7.5f, 7.5f, 0.0f), 0, 0, "ƒ{ƒX‚ð“|‚¹");

	SetEndChildren(m_bar);
	SetEndChildren(m_ground);
	SetEndChildren(m_progress);

	return S_OK;
}

void CTeleporterEventUI::Update()
{
	float rate = (float)*m_referenceTime / (float)CStatueTeleporter::CHARGE_TIME;
	if (rate > 1.0f)
	{
		rate = 1.0f;
	}
	int number = (int)(rate * 100.0f);
	m_progress->SetNumber(number);

	D3DXVECTOR3 size = BAR_SIZE;
	size.x *= rate;
	m_bar->SetSize(size);
}
