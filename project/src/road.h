//**************************************************************
//
// 道ポリゴン
// Author : 冨所知生
//
//**************************************************************
#ifndef _ROAD_POLYGON_H_	// このマクロ定義がされてなかったら
#define _ROAD_POLYGON_H_	// 二重インクルード防止のマクロ定義

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
class  CRoad : public CObjectPolygon3D
{
public:
	static CRoad *Create(D3DXCOLOR col);

	CRoad();
	~CRoad() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetTarget(CCharacter* pTarget) { m_target = pTarget; }
	void SetShooter(CCharacter* pShooter) { m_shooter = pShooter; }
	void SetUse(bool use) { m_isuse = use; }

private:
	CCharacter* m_target;
	CCharacter* m_shooter;
	D3DXCOLOR m_col;

	bool m_isuse;
};

#endif