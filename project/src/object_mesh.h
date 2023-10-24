//**************************************************************
//
// メッシュ設定ヘッター
// Author:hamada ryuuga
//
//**************************************************************
#ifndef _MESH_H_
#define _MESH_H_

//==============================================================
// include
//==============================================================
#include "object_polygon3d.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionMesh;

//==============================================================
// メッシュ
//==============================================================
class CMesh : public CObjectPolygon3D
{
public:
	static const float MOUNTAIN;

public:
	virtual void OnHit() {}	// メッシュの当たった時の判定

	CMesh(CTaskGroup::EPriority nPriority = CTaskGroup::EPriority::LEVEL_3D_1);
	~CMesh() override;

	HRESULT Init() override;		// 初期化
	void Uninit() override;			// 破棄
	void Draw() override;			// 描画

	static CMesh* Create();

	bool CreateMesh(D3DXVECTOR3 *pPos);		// メッシュの凸凹つける
	bool Collision(D3DXVECTOR3 *pPos);	// メッシュの当たり判定つける

	void Loadfile(const char * pFileName);	// メッシュの読み込み
	void Savefile(const char * pFileName);	// メッシュの書き出し
	
	void SetMesh(const int Size);

	void SetNumber(int IsNumber) { m_number = IsNumber; }
	int GetNumber() { return m_number; }

	void SetType(int IsType) { m_type = IsType; }
	int GetMeshType() { return m_type; }

	D3DXVECTOR3 GetMeshSize() { return D3DXVECTOR3(m_vtxCountX * m_meshSize.x, 0.0f, m_vtxCountZ * m_meshSize.z); }

	void SetOneMeshSize(D3DXVECTOR3 IsSize);
	D3DXVECTOR3 GetOneMeshSize() { return m_meshSize; }
	int GetMeshSizeX() { return m_vtxCountX; }

	LPDIRECT3DINDEXBUFFER9 GetIdxBuff() { return m_idxBuff; }

	void SwitchCollision(bool onCollision) { m_isCollision = onCollision; };

	std::string GetDataNeme() { return m_dataName; }
	CCollisionMesh* GetMesh() { return m_collisionMesh; }

private:
	void SetVtxMesh(VERTEX_3D* pVtx, WORD* pIdx, int nCnt, bool isUp);
	void SetVtxMeshSize(int Size);
	void SetVtxMeshLight();

	LPDIRECT3DINDEXBUFFER9 m_idxBuff;	// インデックスバッファ

	int m_xsiz;				// 面数
	int m_zsiz;				// 面数
	int m_vtxCountX;		// 辺の頂点数
	int m_vtxCountZ;		// 辺の頂点数
	int m_vtx;				// 頂点数
	int m_index;			// インデックス
	int m_polygonCount;		// ポリゴン数
	int m_nowMesh;
	int m_number;
	int m_type;
	D3DXVECTOR3 m_meshSize;
	D3DXVECTOR3* m_posMesh;
	std::string m_fileName;
	std::string m_dataName;
	bool m_isCollision;
	CCollisionMesh* m_collisionMesh;
};
#endif

