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
// クラス
//==============================================================
class CItemModel : public CObjectX
{
private:
	enum MODEL_DATA
	{
		MODEL_NONE = -1,
		MODEL_POWER_UP,
		MODEL_MAX
	};

public:
	CItemModel(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemModel();

	HRESULT Init() override;
	HRESULT Init(int inId);
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}

	static CItemModel* Create(int inId);

	std::string GetItemId(int inId) { return m_modelData[inId]; }

private:
	// アイテムのモデルデータ
	std::string m_modelData[MODEL_MAX];
};
#endif	// _ITEM_MODEL_H_