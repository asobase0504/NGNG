//==================================================
// moneyUI.h
// Author: ���c�喲
//==================================================
#ifndef _MONEYUI_H_
#define _MONEYUI_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"
#include "abnormal_data_base.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2D;
class CProcedure;

//**************************************************
// �N���X
//**************************************************
class CPlayerAbnormalUI : public CObject
{
public:
	CPlayerAbnormalUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CPlayerAbnormalUI();

	HRESULT Init() override;
	void Update() override;

	static CPlayerAbnormalUI* Create(const int& inStock,CAbnormalDataBase::EAbnormalType inType);

private:
	CAbnormalDataBase::EAbnormalType inType;
	bool m_isDisplayStack;
	int* m_stackCnt;		// stack���̃��S
	CObject2D* m_abnormalLogo;
	CProcedure* m_stack;
};

#endif // _TIMER_H_