//**************************************************************
//
// 当たり判定
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_MESH_H_			// このマクロ定義がされてなかったら
#define _COLLISION_MESH_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "collision.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionCyinder;
class CCollisionSphere;

//==============================================================
// コリジョンメッシュクラス
//==============================================================
class CCollisionMesh : public CCollision
{
public:
	CCollisionMesh();
	~CCollisionMesh();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCyinder* inCyinder, bool isExtrusion);	// TODO みっちのやつ終わったらこっちに当たり判定移行する
	bool ToSphere(CCollisionSphere* inSphere);

	static CCollisionMesh* Create(int inPrimitive, LPDIRECT3DVERTEXBUFFER9 inVtxBuff, LPDIRECT3DINDEXBUFFER9 inIdxBuff, D3DXMATRIX inMtxWorld);

	float GetExtrusionHeight() { return m_extrusionHeight; }

private:
	int m_primitive;
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_idxBuff;
	D3DXMATRIX m_mtxWorld;
	float m_extrusionHeight;	// 押し出す高さ
};

#endif	// _COLLISION_MESH_H_