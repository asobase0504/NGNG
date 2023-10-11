//**************************************************************
//
// 当たり判定
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_MESH_H_			// このマクロ定義がされてなかったら
#define _COLLISION_MESH_H_			// 二重インクルード防止のマクロ定義

#include "collision_mesh.h"

class CCollisionBox;
class CCollisionCyinder;
class CCollisionSphere;

class CCollisionMesh : public CCollision
{
public:
	CCollisionMesh();
	~CCollisionMesh();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCyinder* inCyinder);
	bool ToMesh(CCollisionMesh* inMesh);
	bool ToBox(CCollisionBox* inBox);
	bool ToSphere(CCollisionSphere* inSphere);

private:

};

#endif