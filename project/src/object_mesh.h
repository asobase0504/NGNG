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

public:
	virtual void OnHit() {}	// ���b�V���̓����������̔���

	CMesh(CTaskGroup::EPriority nPriority = CTaskGroup::EPriority::LEVEL_3D_1);
	~CMesh() override;

	HRESULT Init() override;		// ������
	void Uninit() override;			// �j��
	void Draw() override;			// �`��

	static CMesh* Create();

	bool CreateMesh(D3DXVECTOR3 *pPos);		// ���b�V���̓ʉ�����
	bool Collision(D3DXVECTOR3 *pPos);	// ���b�V���̓����蔻�����

	void Loadfile(const char * pFileName);	// ���b�V���̓ǂݍ���
	void Savefile(const char * pFileName);	// ���b�V���̏����o��
	
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

	LPDIRECT3DINDEXBUFFER9 m_idxBuff;	// �C���f�b�N�X�o�b�t�@

	int m_xsiz;				// �ʐ�
	int m_zsiz;				// �ʐ�
	int m_vtxCountX;		// �ӂ̒��_��
	int m_vtxCountZ;		// �ӂ̒��_��
	int m_vtx;				// ���_��
	int m_index;			// �C���f�b�N�X
	int m_polygonCount;		// �|���S����
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

