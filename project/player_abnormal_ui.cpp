#include "player_abnormal_ui.h"
#include "object2d.h"
#include "procedure.h"

CPlayerAbnormalUI::CPlayerAbnormalUI():
	CObject(CTaskGroup::EPriority::LEVEL_2D_UI)
{
}

CPlayerAbnormalUI::~CPlayerAbnormalUI()
{
}

HRESULT CPlayerAbnormalUI::Init()
{
	m_abnormalLogo = CObject2d::Create(CTaskGroup::LEVEL_2D_UI);
	SetEndChildren(m_abnormalLogo);
	m_abnormalLogo->SetSize(D3DXVECTOR3(25.0f,25.0f,0.0f));
	m_abnormalLogo->SetTexture("ABNORMAL_ICON_FIRE");

	m_stack = CProcedure::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), *m_stackCnt);
	SetEndChildren(m_stack);

	return E_NOTIMPL;
}

void CPlayerAbnormalUI::Update()
{
	m_stack->SetNumber(*m_stackCnt);
}

//--------------------------------------------------
// ¶¬
//--------------------------------------------------
CPlayerAbnormalUI * CPlayerAbnormalUI::Create(const int* inStock, CAbnormalDataBase::EAbnormalType inType)
{
	CPlayerAbnormalUI* ui = new CPlayerAbnormalUI;
	ui->m_stackCnt = inStock;
	ui->m_inType = inType;
	ui->Init();

	return ui;
}

//--------------------------------------------------
// ˆÊ’u‚Ì’²®
//--------------------------------------------------
void CPlayerAbnormalUI::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);

	m_abnormalLogo->SetPos(inPos);
	D3DXVECTOR3 pos = inPos;
	pos.x += 15.0f;
	pos.y -= 15.0f;
	m_stack->SetPos(pos);
}
