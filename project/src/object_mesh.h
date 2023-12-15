//**************************************************************
//
// ���b�V���ݒ�w�b�^�[
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
// �O���錾
//==============================================================
class CCollisionMesh;

//==============================================================
// ���b�V��
//==============================================================
class CMesh : public CObjectPolygon3D
{
public:
	static const float MOUNTAIN;
	static const float RADIUS;
	static const int START_HORIZONTAL;
	static const int START_VERTICAL;

public:
	virtual void OnHit() {}	// ���b�V���̓����������̔���

	CMesh(CTaskGroup::EPriority nPriority = CTaskGroup::EPriority::LEVEL_3D_2);
	~CMesh() override;

	HRESULT Init() override;		// ������
	void Uninit() override;			// �j��
	void Draw() override;			// �`��

	static CMesh* Create();

	bool CreateMesh(D3DXVECTOR3 *pPos);		// ���b�V���̓ʉ�����
	bool Collision(D3DXVECTOR3 *pPos);		// ���b�V���̓����蔻�����
	
	void SetMesh(const int Size);

	D3DXVECTOR3 GetMeshSize() { return D3DXVECTOR3(m_vtxCountX * m_meshSize.x, 0.0f, m_vtxCountZ * m_meshSize.z); }

	void SetOneMeshSize(D3DXVECTOR3 IsSize);
	D3DXVECTOR3 GetOneMeshSize() { return m_meshSize; }
	int GetMeshSizeX() { return m_vtxCountX; }

	LPDIRECT3DINDEXBUFFER9 GetIdxBuff() { return m_idxBuff; }

	void SwitchCollision(bool onCollision) { m_isCollision = onCollision; };

	CCollisionMesh* GetCollisionMesh() { return m_collisionMesh; }

	void SetY(std::vector<std::vector<float>> inY);
	void SetSkyMesh();

	void SetIsCulling(bool isCulling) { m_isCulling = isCulling; }

private:
	void SetVtxMesh(VERTEX_3D* pVtx, WORD* pIdx, int nCnt, bool isUp);
	void SetVtxMeshSize(int sizeX, int sizeZ);
	void SetVtxMeshLight();

	LPDIRECT3DINDEXBUFFER9 m_idxBuff;	// �C���f�b�N�X�o�b�t�@

	int m_xsiz;				// �ʐ�
	int m_zsiz;				// �ʐ�
	int m_vtxCountX;		// �ӂ̒��_��
	int m_vtxCountZ;		// �ӂ̒��_��
	int m_vtx;				// ���_��
	int m_index;			// �C���f�b�N�X
	int m_polygonCount;		// �|���S����

	D3DXVECTOR3 m_meshSize;
	bool m_isCollision;
	CCollisionMesh* m_collisionMesh;

	D3DXVECTOR2	m_sphereRange;		// ���̕`��͈�
	float m_fRadius;			// ���a

	bool m_isCulling;
};
#endif

