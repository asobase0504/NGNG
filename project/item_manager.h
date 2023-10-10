//**************************************************************
//
// item_manager
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

//==============================================================
// include
//==============================================================
#include "object2d.h"

//==============================================================
// ƒNƒ‰ƒX
//==============================================================
class CItemManager : public CTask
{
public:
	CItemManager(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemManager();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CItemManager* Create();

	std::string GetItemId(int inId) { return m_itemId[inId]; }

public:
	enum ITEM_ID
	{
		ITEM_1 = 0,
		ITEM_MAX
	};

private:
	std::string m_itemId[ITEM_MAX];
};
#endif	// _ITEM_MANAGER_H_