//**************************************************************
//
// item_model
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ITEM_MODEL_H_
#define _ITEM_MODEL_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// ƒNƒ‰ƒX
//==============================================================
class CItemModel : public CObjectX
{
public:
	CItemModel(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemModel();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CItemModel* Create();

private:
};
#endif	// _ITEM_MODEL_H_