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
// エネミーHPUI
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
	bool m_isShow;						// 自身を描画するか否か
	CCharacter* m_pEnemy;				// エネミー
	CObjectPolygon3D* m_outline;		// 背景(白)
	CObjectPolygon3D* m_background;		// 背景(黒)
	CObjectPolygon3D* m_gageHP;			// 現体力
	CObjectPolygon3D* m_gageDamage;		// 受けたダメージ
	std::list<CObjectPolygon3D*> m_abnormalIcons;		// 状態異常
};

#endif