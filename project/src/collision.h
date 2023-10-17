//**************************************************************
//
// 当たり判定
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_H_			// このマクロ定義がされてなかったら
#define _COLLISION_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "object.h"

class CCollision : public CObject
{
public:
	CCollision();
	~CCollision();

	void Draw() final {}

	bool ToCylinder() {}
	bool ToMesh() {}
	bool ToBox() {}
	bool ToSphere() {}
};

#endif