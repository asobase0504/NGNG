//**************************************************************
//
// item
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ITEM_DATA_H_
#define _ITEM_DATA_H_

//==============================================================
// include
//==============================================================
#include "task.h"
#include "item_data_base.h"

//==============================================================
// ƒNƒ‰ƒX
//==============================================================
class CItem : public CTask
{
public:
	CItem(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItem();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	static CItem* Create(ITEM_TYPE inId);

	void SetItemData(ITEM_TYPE inItemData) { m_itemData = inItemData; }
	ITEM_TYPE GetItemData(int inId) { return m_itemData; }

private:
	void ItemState_();

private:
	ITEM_TYPE m_itemData;
};
#endif	// _ITEM_DATA_H_