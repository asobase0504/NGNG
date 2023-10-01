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
// ���b�V��
//==============================================================
class CMesh : public CObjectPolygon3D
{
public:
	virtual void OnHit() {}	// ���b�V���̓����������̔���

	CMesh(CTaskGroup::EPriority nPriority = CTaskGroup::EPriority::LEVEL_3D_1);
	~CMesh() override;

	HRESULT Init() override;		// ������
	void Uninit() override;			// �j��
	void Update() override;			// �X�V
	void Draw() override;			// �`��

	static CMesh* Create();

	bool CreateMesh(D3DXVECTOR3 *pPos);		// ���b�V���̓ʉ�����
	bool Collision(D3DXVECTOR3 *pPos);	// ���b�V���̓����蔻�����

	void Loadfile(const char * pFileName);	// ���b�V���̓ǂݍ���
	void Savefile(const char * pFileName);	// ���b�V���̏����o��
	
	void SetMesh(const int Size);

	void SetNumber(int IsNumber) { m_Number = IsNumber; }
	int GetNumber() { return m_Number; }

	void SetType(int IsType) { m_Type = IsType; }
	int GetMeshType() { return m_Type; }

	D3DXVECTOR3 GetMeshSize() { return D3DXVECTOR3(m_vtxCountX * m_MeshSize.x, 0.0f, m_vtxCountZ * m_MeshSize.z); }

	void SetOneMeshSize(D3DXVECTOR3 IsSize);
	D3DXVECTOR3 GetOneMeshSize() { return m_MeshSize; }
	int GetMeshSizeX() { return m_vtxCountX; }

	void SwitchCollision(bool onCollision) { IsCollision = onCollision; };

	std::string GetDataNeme() { return DataName; }

private:
	void SetVtxMesh(VERTEX_3D* pVtx, WORD* pIdx, int nCnt, bool isUp);
	void SetVtxMeshSize(int Size);
	void SetVtxMeshLight();

	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// �C���f�b�N�X�o�b�t�@

	int m_xsiz;				// �ʐ�
	int m_zsiz;				// �ʐ�
	int m_vtxCountX;		// �ӂ̒��_��
	int m_vtxCountZ;		// �ӂ̒��_��
	int m_vtx;				// ���_��
	int m_index;			// �C���f�b�N�X
	int m_polygonCount;		// �|���S����
	int m_NowMesh;
	int m_Number;
	int m_Type;
	D3DXVECTOR3 m_MeshSize;
	D3DXVECTOR3* m_nPosMesh;
	std::string  m_pFileName;
	std::string  DataName;
	bool IsCollision;
};
#endif

