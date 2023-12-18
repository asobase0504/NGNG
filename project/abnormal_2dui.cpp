#include "abnormal_2dui.h"
#include "object2d.h"
#include "procedure.h"

CAbnormal2DUI::CAbnormal2DUI():
	CObject(CTaskGroup::EPriority::LEVEL_2D_UI)
{
}

CAbnormal2DUI::~CAbnormal2DUI()
{
}

HRESULT CAbnormal2DUI::Init()
{
	m_abnormalLogo = CObject2d::Create(CTaskGroup::LEVEL_2D_UI);
	SetEndChildren(m_abnormalLogo);
	m_abnormalLogo->SetSize(D3DXVECTOR3(25.0f,25.0f,0.0f));
	m_abnormalLogo->SetTexture("ABNORMAL_ICON_FIRE");

	m_stack = CProcedure::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), *m_stackCnt);
	SetEndChildren(m_stack);

	return E_NOTIMPL;
}

void CAbnormal2DUI::Update()
{
	m_stack->SetNumber(*m_stackCnt);
}

//--------------------------------------------------
// ¶¬
//--------------------------------------------------
CAbnormal2DUI * CAbnormal2DUI::Create(const int* inStock, CAbnormalDataBase::EAbnormalType inType)
{
	CAbnormal2DUI* ui = new CAbnormal2DUI;
	ui->m_stackCnt = inStock;
	ui->m_inType = inType;
	ui->Init();

	return ui;
}

//--------------------------------------------------
// ˆÊ’u‚Ì’²®
//--------------------------------------------------
void CAbnormal2DUI::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);

	m_abnormalLogo->SetPos(inPos);
	D3DXVECTOR3 pos = inPos;
	pos.x += 15.0f;
	pos.y -= 15.0f;
	m_stack->SetPos(pos);
}
