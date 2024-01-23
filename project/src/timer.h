//==================================================
// moneyUI.h
// Author: 梶田大夢
//==================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//**************************************************
// インクルード
//**************************************************
#include "object2d.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CText;
class CProcedure;

//**************************************************
// クラス
//**************************************************
class CTimer : public CObject
{
public:
	CTimer();
	~CTimer();

	HRESULT Init() override;
	void Update() override;

	static CTimer* Create();

private:
	int m_time;

	CProcedure* m_second;	// 秒
	CProcedure* m_minutes;	// 分
	CText* m_koron;			// コロン
};

#endif // _TIMER_H_