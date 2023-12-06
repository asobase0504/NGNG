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
class CText;
class CObject2D;

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
	CText* m_stack;
	CObject2D* m_abnormalLogo;
};

#endif // _TIMER_H_