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
#include "object2d.h"

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
};
#endif	// _ITEM_DATA_H_