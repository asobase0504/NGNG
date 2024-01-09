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
class CAbnormal2DUI : public CObject
{
public:
	CAbnormal2DUI();
	~CAbnormal2DUI();

	HRESULT Init() override;
	void Update() override;

	static CAbnormal2DUI* Create(const int* inStock,CAbnormalDataBase::EAbnormalType inType);

	CAbnormalDataBase::EAbnormalType GetType() { return m_inType; }

	void SetPos(const D3DXVECTOR3&) override;

private:
	// 描画物
	CObject2d* m_abnormalLogo;	// 状態異常ロゴ
	CProcedure* m_stack;		// 数字

	CAbnormalDataBase::EAbnormalType m_inType;
	bool m_isDisplayStack;
	const int* m_stackCnt;		// stack数
};

#endif // _TIMER_H_