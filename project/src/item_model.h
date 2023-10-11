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
#include "item_data.h"

//==============================================================
// クラス
//==============================================================
class CItemModel : public CObjectX
{
public:
	CItemModel(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemModel();

	HRESULT Init() override;
	HRESULT Init(int inId);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CItemModel* Create(const D3DXVECTOR3& inPos, int inId);

private:
	// アイテムのモデルデータ
	std::string m_modelData[ITEM_MAX];
};
#endif	// _ITEM_MODEL_H_