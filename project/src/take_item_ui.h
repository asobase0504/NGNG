//**************************************************************
//
// 取得したアイテムの情報
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _TAKE_ITEM_UI_H_
#define _TAKE_ITEM_UI_H_

//==============================================================
// include
//==============================================================
#include "object.h"
#include "item_data_base.h"
#include <queue>

//==============================================================
// 前方宣言
//==============================================================
class CObject2d;
class CText;

//==============================================================
// クラス
//==============================================================
class CTakeItemUI : public CObject
{
private:
	static const D3DXVECTOR2 CENTER_POS;	// 中心座標
	static const D3DXVECTOR2 ICON_POS;	// アイコン位置
	static const D3DXVECTOR2 NAME_POS;	// 名前位置
	static const D3DXVECTOR2 TEXT_POS;	// テキスト位置
	static const int DISPLAY_TIME;	// 表示時間
public:
	CTakeItemUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CTakeItemUI();

	HRESULT Init() override;
	void Update() override;

	void SetTakeItem(CItemDataBase::EItemType inType);

private:

private:
	CObject2d* m_ground;	// 下地

	int m_displayCnt;		// 表示しているフレーム数

	// 描画するアイテム情報
	CObject2d* m_itemIcon;	// アイコン
	CText* m_text;			// 効果の説明
	CText* m_name;			// 名前
};
#endif	// _ITEM_DATA_H_