//**************************************************************
//
// キャラクター選択画面
// Author : 梶田大夢
//
//**************************************************************
#ifndef _CHARACTER_SELECT_H_
#define _CHARACTER_SELECT_H_

//==============================================================
// include
//==============================================================
#include "mode.h"

//==============================================================
// 前方宣言
//==============================================================
class CSelect;
class CObject2d;

//==============================================================
// キャラクター選択クラス
//==============================================================
class CCharacterSelect :public CMode
{
	// 遷移先
	enum ESelectMode
	{
		MODE_GAME = 0,		// ゲーム画面	
		MODE_TUTORIAL,		// チュートリアル画面
		MODE_RANKING,		// ランキング画面
		MODE_END,			// 終了
		MODE_MAX
	};

public:
	CCharacterSelect();
	~CCharacterSelect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	CSelect* m_start;
	CObject2d* m_startShadow;
};
#endif
