//**************************************************************
//
// 選択されてるObjectによって動作行動を教えるUI
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _SELECT_UI_H_
#define _SELECT_UI_H_

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// 前方宣言
//==============================================================
class CObject2d;
class CText;

//==============================================================
// クラス
//==============================================================
class CSelectUI : public CObject
{
private:
	static const D3DXVECTOR2 ICON_POS;	// アイコン位置
	static const D3DXVECTOR2 NAME_POS;	// 名前位置
	static const D3DXVECTOR2 TEXT_POS;	// テキスト位置
	static const int DISPLAY_TIME;	// 表示時間
public:
	CSelectUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CSelectUI();

	HRESULT Init() override;
	void Update() override;

	void SetText(std::string);

private:
	CObject2d* m_ground;	// 下地

	CText* m_keyIcon;	// 対応キーのテキスト
	CText* m_text;		// テキスト
};
#endif	// _ITEM_DATA_H_