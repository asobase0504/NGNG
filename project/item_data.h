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
public:
	CItemData(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemData();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CItemData* Create();

private:
	enum ITEM_DATA
	{
		ITEM_POWER_UP = 0,
		ITEM_MAX
	};

private:
	ITEM_DATA m_itemData[ITEM_MAX];
};
#endif	// _ITEM_DATA_H_