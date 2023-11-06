//**************************************************************
//
// ポリゴンバレット
// Author : 冨所知生
//
//**************************************************************
#ifndef _BULLET_POLYGON_H_	// このマクロ定義がされてなかったら
#define _BULLET_POLYGON_H_	// 二重インクルード防止のマクロ定義

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
class CCollision;

//==============================================================
// 道ポリゴンの設定
//==============================================================
class  CBullet : public CObjectPolygon3D
{
public:
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float speed);

	CBullet();
	~CBullet() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetSpeed(float speed) { m_speed = speed; }
private:
	int m_life;
	bool m_ispenetration;
	float m_speed;
	CCollision*		m_collision;
};

#endif