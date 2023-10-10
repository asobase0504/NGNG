//**************************************************************
//
// item_data
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ITEM_DATA_H_
#define _ITEM_DATA_H_

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// ƒNƒ‰ƒX
//==============================================================
class CItemData : public CTask
{
private:
	enum ITEM_DATA
	{
		ITEM_NONE = -1,
		ITEM_POWER_UP,
		ITEM_MAX
	};

public:
	CItemData(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemData();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	static CItemData* Create(int inId);

	void SetItemData(ITEM_DATA inItemData) { m_itemData = inItemData; }
	ITEM_DATA GetItemData(int inId) { return m_itemData; }

private:
	void ItemState_();

private:
	ITEM_DATA m_itemData;
};
#endif	// _ITEM_DATA_H_