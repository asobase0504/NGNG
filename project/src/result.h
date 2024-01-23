//**************************************************************
//
// result
// Author: Buriya Kota
//
//**************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// 前方宣言
//==============================================================
class CObject2d;
class CText;
class CUIBackGround;

//==============================================================
// クラス
//==============================================================
class CResult : public CTask
{
private:

public:
	CResult(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);
	~CResult();

	HRESULT Init() override;
	void Update() override;

	static CResult* Create();

private:
	CObject2d* m_bg;

	// 一番上
	CObject2d* m_loseBG;
	CText* m_loseText;

	// データ
	CUIBackGround* m_dataBG;
	CText* m_dataText;
	CObject2d* m_dataTextBG;
	CObject2d* m_dataTextBGOutLine;

	/* 情報 */
	CUIBackGround* m_infoBG;
	CText* m_infoText;
	CObject2d* m_infoTextBG;
	CObject2d* m_infoTextBGOutLine;

	// 収集アイテム
	CObject2d* m_takeItemTextBG;
	CText* m_takeItemText;

	// バック
	CObject2d* m_backBGOutLine;
	CObject2d* m_backBG;
	CText* m_backText;
};
#endif	// _GOLD_NUGGET_H_