//**************************************************************
//
// 当たり判定
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_BOX_H_			// このマクロ定義がされてなかったら
#define _COLLISION_BOX_H_			// 二重インクルード防止のマクロ定義

#include "collision.h"

class CCollisionMesh;
class CCollisionCylinder;
class CCollisionSphere;
class CLine;

class CCollisionBox : public CCollision
{
public:
	CCollisionBox();
	~CCollisionBox();

	HRESULT Init();
	void Update();

	bool ToCylinder(CCollisionCylinder* inCyinder) override;
	//bool ToMesh(CCollisionMesh* inMesh);
	//bool ToBox(CCollisionBox* inBox);
	//bool ToSphere(CCollisionSphere* inSphere);

	static CCollisionBox* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXMATRIX& mtx);
private:
	void SetLine();
private:
	CLine* m_line[12];
};
#endif