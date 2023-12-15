//**************************************************************
//
// 通信されたプレイヤーを描画、管理する。
// Author : 梶田大夢
//
//**************************************************************
#ifndef _SERVER_PLAYER_H_			// このマクロ定義がされてなかったら
#define _SERVER_PLAYER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "character.h"

//==============================================================
// 前方宣言
//==============================================================

//==============================================================
// 敵クラス
//==============================================================
class CServerPlayer : public CCharacter
{
public:
	// コンストラクタとデストラクタ
	explicit CServerPlayer();
	~CServerPlayer();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Update() override;
};
#endif