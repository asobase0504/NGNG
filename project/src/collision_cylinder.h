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
class CLine;

class CCollisionCylinder : public CCollision
{
public:
	CCollisionCylinder();
	~CCollisionCylinder();

	HRESULT Init();
	void Uninit();
	void Update();

	bool ToCylinder(CCollisionCylinder* inCyinder) override;
	bool ToBox(CCollisionBox* inBox, bool isExtrusion) override;
	bool ToSphere(CCollisionSphere* inSphere) override;
	bool ToMesh(CCollisionMesh* inMesh) override;

	static CCollisionCylinder* Create(const D3DXVECTOR3& pos, const float length ,const float height);

	float GetLength() { return m_length; }
	float GetHeight() { return m_height; }

private:
	float m_length;
	float m_height;
	CLine* m_line[4];
};

#endif