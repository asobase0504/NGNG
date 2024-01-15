//==================================================
// moneyUI.h
// Author: 梶田大夢
//==================================================
#ifndef _CARRYING_ITEM_UI_H_
#define _CARRYING_ITEM_UI_H_

//**************************************************
// インクルード
//**************************************************
#include "object.h"
#include "item_data_base.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2d;
class CProcedure;

//**************************************************
// クラス
//**************************************************
class CCarryingItemUI : public CObject
{
public:
	CCarryingItemUI();
	~CCarryingItemUI();

	HRESULT Init() override;
	void Update() override;

	static CCarryingItemUI* Create(CItemDataBase::EItemType inType, const int*);

	CItemDataBase::EItemType GetType() { return m_type; }

	void SetPos(const D3DXVECTOR3&) override;

private:
	// 描画物
	CObject2d* m_ItemLogo;	// 状態異常ロゴ
	CProcedure* m_stack;		// 数字

	CItemDataBase::EItemType m_type;
	const unsigned int* m_stackCnt;		// stack数
};

#endif // _TIMER_H_