//==================================================
// moneyUI.h
// Author: 梶田大夢
//==================================================
#ifndef _PLAYER_ABNORMAL_UI_H_
#define _PLAYER_ABNORMAL_UI_H_

//**************************************************
// インクルード
//**************************************************
#include "object.h"
#include "abnormal_data_base.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2d;
class CProcedure;

//**************************************************
// クラス
//**************************************************
class CPlayerAbnormalUI : public CObject
{
public:
	CPlayerAbnormalUI();
	~CPlayerAbnormalUI();

	HRESULT Init() override;
	void Update() override;

	static CPlayerAbnormalUI* Create(const int* inStock,CAbnormalDataBase::EAbnormalType inType);

	CAbnormalDataBase::EAbnormalType GetType() { return m_inType; }

	void SetPos(const D3DXVECTOR3&) override;

private:
	CAbnormalDataBase::EAbnormalType m_inType;
	bool m_isDisplayStack;
	const int* m_stackCnt;		// stack数のロゴ
	CObject2d* m_abnormalLogo;
	CProcedure* m_stack;
};

#endif // _TIMER_H_