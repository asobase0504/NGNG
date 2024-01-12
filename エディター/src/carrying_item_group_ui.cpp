#include "carrying_item_group_ui.h"
#include "object2d.h"
#include "application.h"

CCarryingItemGroupUI::CCarryingItemGroupUI()
{
}

CCarryingItemGroupUI::~CCarryingItemGroupUI()
{
}

HRESULT CCarryingItemGroupUI::Init()
{
	m_bg = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bg->SetPos(D3DXVECTOR3(CApplication::CENTER_POS.x, 75.0f, 0.0f));
	m_bg->SetSize(D3DXVECTOR3(400.0f, 45.0f, 0.0f));
	m_bg->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.1f));

	return S_OK;
}

void CCarryingItemGroupUI::Update()
{
}

CCarryingItemUI* CCarryingItemGroupUI::CreateCarryingItemUI(CItemDataBase::EItemType inType, const unsigned int* m_stack)
{
	for (CCarryingItemUI* ui : m_uiList)
	{
		if (ui->GetType() == inType)
		{
			// stack”‚Ìã¸
			return nullptr;
		}
	}

	m_uiList.push_back(CCarryingItemUI::Create(inType, (const int*)m_stack));
	Alignment();
	return nullptr;
}

void CCarryingItemGroupUI::Alignment()
{
	int cnt = 0;

	D3DXVECTOR3 bgPos = m_bg->GetPos();
	D3DXVECTOR3 bgSize = m_bg->GetSize();
	for (CCarryingItemUI* ui : m_uiList)
	{
		float x = (bgPos.x - bgSize.x) + (cnt % 20) * 50.0f + 25.0f;
		float y = (bgPos.y - bgSize.y) + (cnt / 20) * 50.0f + 25.0f;
		ui->SetPos(D3DXVECTOR3(x,y,0.0f));
		cnt++;
	}
}
