//==================================================
// moneyUI.h
// Author: 梶田大夢
//==================================================
#ifndef _MONEYUI_H_
#define _MONEYUI_H_

//**************************************************
// インクルード
//**************************************************
#include "object.h"
#include "abnormal_data_base.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2D;
class CProcedure;

//**************************************************
// クラス
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
	int* m_stackCnt;		// stack数のロゴ
	CObject2D* m_abnormalLogo;
	CProcedure* m_stack;
};

#endif // _TIMER_H_