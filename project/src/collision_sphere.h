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
class CCollisionCylinder;
class CCollisionMesh;
class CLine;

class CCollisionSphere : public CCollision
{
public:
	CCollisionSphere();
	~CCollisionSphere();

	HRESULT Init();

	//bool ToCylinder(CCollisionCylinder* inCyinder);
	bool ToMesh(CCollisionMesh* inMesh);
	bool ToBox(CCollisionBox* inBox, bool isExtrusion) override;
	bool ToSphere(CCollisionSphere* inSphere);
	bool ToCylinder(CCollisionCylinder* inCylinder);

	static CCollisionSphere* Create(const D3DXVECTOR3& pos, const float length);

	float GetLength() { return m_length; }
	float GetExtrusionHeight() { return m_extrusionHeight; }

private:
	void SetLine() override;
private:
	float m_length;
	float m_extrusionHeight;	// 押し出す高さ
	CLine* m_line[8];
};

#endif