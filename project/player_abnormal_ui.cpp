#include "player_abnormal_ui.h"

CPlayerAbnormalUI::CPlayerAbnormalUI(CTaskGroup::EPriority list):
	CObject(list)
{
}

CPlayerAbnormalUI::~CPlayerAbnormalUI()
{
}

HRESULT CPlayerAbnormalUI::Init()
{
	return E_NOTIMPL;
}

void CPlayerAbnormalUI::Update()
{
}

CPlayerAbnormalUI * CPlayerAbnormalUI::Create(const int & inStock, CAbnormalDataBase::EAbnormalType inType)
{
	return nullptr;
}
