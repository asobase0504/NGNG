#include "player_abnormal_ui.h"
#include "object2d.h"
#include "procedure.h"

CPlayerAbnormalUI::CPlayerAbnormalUI(CTaskGroup::EPriority list):
	CObject(list)
{
}

CPlayerAbnormalUI::~CPlayerAbnormalUI()
{
}

HRESULT CPlayerAbnormalUI::Init()
{
	m_abnormalLogo = new CObject2d;
	SetEndChildren(m_abnormalLogo);
	m_abnormalLogo->Init();
	m_abnormalLogo->SetSize(D3DXVECTOR3(50.0f,50.0f,0.0f));

	m_stack = CProcedure::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), *m_stackCnt);

	return E_NOTIMPL;
}

void CPlayerAbnormalUI::Update()
{
	if (*m_stackCnt == 0)
	{
		Uninit();
	}
}

CPlayerAbnormalUI * CPlayerAbnormalUI::Create(const int* inStock, CAbnormalDataBase::EAbnormalType inType)
{
	CPlayerAbnormalUI* ui = new CPlayerAbnormalUI;
	ui->Init();
	ui->m_stackCnt = inStock;
	ui->m_inType = inType;

	return ui;
}

void CPlayerAbnormalUI::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);

	m_abnormalLogo->SetPos(inPos);
	m_stack->SetPos(inPos);
}
