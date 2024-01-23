#include "carrying_item_ui.h"
#include "object2d.h"
#include "procedure.h"

CCarryingItemUI::CCarryingItemUI()
{
}

CCarryingItemUI::~CCarryingItemUI()
{
}

HRESULT CCarryingItemUI::Init()
{
	CObject::Init();
	m_ItemLogo = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_ItemLogo->SetSize(D3DXVECTOR3(25.0f,25.0f,0.0f));
	m_ItemLogo->SetTexture("ITEM_DANGO_O1");

	m_stack = CProcedure::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(10.0f,10.0f,0.0f),0);
	m_stack->SetDisplay(false);
	m_stack->SetAlign(CProcedure::EAlign::RIGHT);
	return S_OK;
}

void CCarryingItemUI::Update()
{
	CObject::Update();

	if (m_stack->GetNumber() >= 2)
	{
		m_stack->SetDisplay(true);
	}
}

CCarryingItemUI * CCarryingItemUI::Create(CItemDataBase::EItemType inType, const int* inStack)
{
	CCarryingItemUI* ui = new CCarryingItemUI;

	ui->Init();
	ui->m_type = inType;
	ui->m_ItemLogo->SetTexture(CItemDataBase::GetInstance()->GetItemIconTextureKey(inType));
	ui->m_stack->SetNumber(inStack);
	return ui;
}

void CCarryingItemUI::SetPos(const D3DXVECTOR3 & inPos)
{
	CObject::SetPos(inPos);
	m_ItemLogo->SetPos(inPos);
	D3DXVECTOR3 diff(30.0f, -15.0f, 0.0f);
	m_stack->SetPos(inPos + diff);
}
