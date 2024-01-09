//**************************************************************
//
// 化け物(空)
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _MONSTER_SKY_H_			// このマクロ定義がされてなかったら
#define _MONSTER_SKY_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "enemy.h"

//==============================================================
// 敵クラス
//==============================================================
class CMonsterSky : public CEnemy
{
public:
	// コンストラクタとデストラクタ
	explicit CMonsterSky();
	~CMonsterSky();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Update() override;

private:
	void Move() override;		// 移動
};
#endif