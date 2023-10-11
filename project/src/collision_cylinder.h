//**************************************************************
//
// 当たり判定
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_CYLINDER_H_			// このマクロ定義がされてなかったら
#define _COLLISION_CYLINDER_H_			// 二重インクルード防止のマクロ定義

#include "collision.h"

class CCollisionMesh;
class CCollisionBox;
class CCollisionSphere;

class CCollisionCyinder : public CCollision
{
public:
	CCollisionCyinder();
	~CCollisionCyinder();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCyinder* inCyinder);
	bool ToMesh(CCollisionMesh* inMesh);
	bool ToBox(CCollisionBox* inBox);
	bool ToSphere(CCollisionSphere* inSphere);

	float GetLength() { return m_length; }
	float GetHeight() { return m_height; }
private:
	float m_length;
	float m_height;
};

#endif