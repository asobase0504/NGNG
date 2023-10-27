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
class CCollisionCylinder;
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

	static CCollisionMesh* Create(int inPrimitive, LPDIRECT3DVERTEXBUFFER9 inVtxBuff, LPDIRECT3DINDEXBUFFER9 inIdxBuff, D3DXMATRIX inMtxWorld);

	int GetPrimitive() { return m_primitive; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_vtxBuff; }
	LPDIRECT3DINDEXBUFFER9 GetIdxBuff() { return m_idxBuff; }
	float GetExtrusionHeight() { return m_extrusionHeight; }

private:
	int m_primitive;
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_idxBuff;
	float m_extrusionHeight;	// 押し出す高さ
};

#endif	// _COLLISION_MESH_H_