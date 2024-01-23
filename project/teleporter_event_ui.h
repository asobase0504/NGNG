//**************************************************************
//
// テレポーターイベント
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _TELEPORTER_EVENT_UI_H_
#define _TELEPORTER_EVENT_UI_H_

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// 前方宣言
//==============================================================
class CObject2d;
class CText;
class CProcedure;

//==============================================================
// クラス
//==============================================================
class CTeleporterEventUI : public CObject
{
private:
	static const D3DXVECTOR3 GROUND_POS;	// バー位置
	static const D3DXVECTOR3 BAR_POS;	// バー位置
	static const D3DXVECTOR3 BAR_SIZE;	// バー多きさ
	static const D3DXVECTOR3 TEXT_POS;	// テキスト位置
	static const int DISPLAY_TIME;	// 表示時間
public:
	CTeleporterEventUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CTeleporterEventUI();

	HRESULT Init() override;
	void Update() override;

	void SetReferenceTime(const int* inTime) { m_referenceTime = inTime; }
	void SetReferenceIsBossKill(const bool* inTime) { m_referenceIsBossKill = inTime; }

private:
	CObject2d* m_barGround;	// ゲージの下地
	CObject2d* m_bar;		// ゲージ
	CText* m_chargeText;		// "耐え忍べ"
	CText* m_bosskillText;		// "ボスを倒せ"
	CObject2d* m_completeLine[2];		// 完了ライン

	const int* m_referenceTime;	// 参照タイム
	const bool* m_referenceIsBossKill;	// 敵の排除
};
#endif	// _ITEM_DATA_H_