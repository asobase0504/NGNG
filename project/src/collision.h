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

class CCollisionMesh;
class CCollisionCyinder;
class CCollisionSphere;
class CCollisionBox;

class CCollision : public CObject
{
public:
	CCollision();
	~CCollision();

	void Draw() final {}

	virtual bool ToCylinder(CCollisionCyinder* inCyinder) { return false; }
	virtual bool ToMesh(CCollisionMesh* inMesh) { return false; }
	virtual bool ToBox(CCollisionBox* inBox, bool isExtrusion) { return false; }
	virtual bool ToSphere(CCollisionSphere* inSphere) { return false; }
};
#endif