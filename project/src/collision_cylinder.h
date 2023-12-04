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
	void Update();

	bool ToCylinder(CCollisionCylinder* inCyinder) override;
	bool ToBox(CCollisionBox* inBox, bool isExtrusion) override;
	bool ToSphere(CCollisionSphere* inSphere) override;
	bool ToMesh(CCollisionMesh* inMesh) override;

	// 第一: 座標 第二: 長さ 第三 : 高さ
	static CCollisionCylinder* Create(const D3DXVECTOR3& pos, const float length ,const float height);

	void SetLength(float inLength) { m_length = inLength; }
	float GetLength() { return m_length; }

	void SetHeight(float inHeight) { m_height = inHeight; }
	float GetHeight() { return m_height; }

private:
	float m_length;
	float m_height;
	CLine* m_line[4];
};

#endif