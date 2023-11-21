//=============================================================================
//
// 入力処理 [input_touch_panel.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUT_TOUCH_PANEL_H_		//このマクロ定義がされなかったら
#define _INPUT_TOUCH_PANEL_H_		//2重インクルード防止のマクロ定義

//----------------------------------------------------------------------------
//インクルードファイル
//----------------------------------------------------------------------------
#include "inputkeydata.h"
#include "DirectInput.h"

static const int MAX_TOUCH_PANEL = 5;		//タッチパネルの同時検知可能数

//----------------------------------------------------------------------------
//クラス定義
//----------------------------------------------------------------------------
class CInputTouchPanel
{
private:
	struct TouchPanel
	{
		TOUCHINPUT TouchData;
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 OldPos;
		D3DXVECTOR3 Vec;
		bool bTrigger;
		bool bFirstTrigger;
		bool bUse;
	};

public:
	CInputTouchPanel();
	~CInputTouchPanel();

	void Update();
	
	bool GetPress(int nNum = 0);					//プレス処理
	bool GetTrigger(int nNum = 0);					//トリガー処理
	D3DXVECTOR3 GetTouchPos(int nNum = 0);			//タッチPosのGet
	D3DXVECTOR3 GetTouchVec(int nNum = 0);			//タッチVecのGet
	void SetTouchData(TOUCHINPUT *pTouchData,int nCntData);		//データの設定
	float RateCalculation(float fMax,float fWnMax, int nbet);		//割合計算
	void SetScreenSize(D3DXVECTOR2 ScreenSize) { m_ScreenSize = ScreenSize; }

private:
	TouchPanel m_TouchPanel[MAX_TOUCH_PANEL];		//タッチパネルのひとつに必要な情報の構造体
	D3DXVECTOR2 m_ScreenSize;
};
#endif