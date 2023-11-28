//**************************************************************
//
// エネミーHPUI
// Author : 冨所知生
//
//**************************************************************
#ifndef _ENEMY_HP_UI_H_	// このマクロ定義がされてなかったら
#define _ENEMY_HP_UI_H_	// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "object_polygon3d.h"

//==============================================================
// マクロ宣言
//==============================================================

//==============================================================
// 前方宣言
//==============================================================
class CCharacter;

//==============================================================
// 道ポリゴンの設定
//==============================================================
class  CEnemy_HPUI : public CObject
{
public:
	static CEnemy_HPUI *Create(CCharacter* pEnemy);

	CEnemy_HPUI();
	~CEnemy_HPUI() override;

	HRESULT Init() override;
	void Update() override;

	void SetEnemy(CCharacter* enemy) { m_pEnemy = enemy; }
private:
	bool m_isShow;
	CCharacter* m_pEnemy;
	CObjectPolygon3D* m_background;
	CObjectPolygon3D* m_gage;
};

#endif