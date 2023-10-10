//**************************************************************
//
// 当たり判定
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_SPHERE_H_			// このマクロ定義がされてなかったら
#define _COLLISION_SPHERE_H_			// 二重インクルード防止のマクロ定義

#include "collision.h"

class CCollisionBox;
class CCollisionCyinder;
class CCollisionMesh;

class CCollisionSphere : public CCollision
{
public:
	CCollisionSphere();
	~CCollisionSphere();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCyinder* inCyinder);
	bool ToMesh(CCollisionMesh* inMesh);
	bool ToBox(CCollisionBox* inBox);
	bool ToSphere(CCollisionSphere* inSphere);

private:
	float m_length;
};

#endif