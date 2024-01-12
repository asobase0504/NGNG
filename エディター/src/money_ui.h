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
#include "status.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CProcedure;
class CObject2d;

//**************************************************
// �N���X
//**************************************************
class CMONEYUI: public CObject
{
public:
	CMONEYUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CMONEYUI();

	HRESULT Init() override;
	void Update() override;

	static CMONEYUI* Create(CStatus<int>* inMoney);

private:
	CStatus<int>* m_money;
	CProcedure* m_procedure;
	CObject2d* m_bg;
	int max_difficult;
};

#endif // _TIMER_H_