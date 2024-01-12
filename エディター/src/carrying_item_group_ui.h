//==================================================
//
// 所持しているアイテムUI群
// Author: YudaKaito
//
//==================================================
#ifndef _CARRYING_ITEM_GROUP_UI_H_
#define _CARRYING_ITEM_GROUP_UI_H_

//**************************************************
// インクルード
//**************************************************
#include "object.h"
#include "item_data_base.h"
#include "carrying_item_ui.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2d;
class CProcedure;
class CCarryingItemUI;

//**************************************************
// クラス
//**************************************************
class CCarryingItemGroupUI : public CObject
{
public:
	CCarryingItemGroupUI();
	~CCarryingItemGroupUI();

	HRESULT Init() override;
	void Update() override;

	CCarryingItemUI* CreateCarryingItemUI(CItemDataBase::EItemType, const unsigned int* = nullptr);

private:
	void Alignment();	// 整列

private:
	// 描画物
	std::list<CCarryingItemUI*> m_uiList;
	CObject2d* m_bg;
};

#endif // _TIMER_H_