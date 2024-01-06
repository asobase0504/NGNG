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
#include "status.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CProcedure;
class CObject2d;

//**************************************************
// クラス
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