//**************************************************************
//
// �����蔻��
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_MESH_H_			// ���̃}�N����`������ĂȂ�������
#define _COLLISION_MESH_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "collision.h"

//==============================================================
// �O���錾
//==============================================================
class CCollisionCyinder;
class CCollisionSphere;

//==============================================================
// �R���W�������b�V���N���X
//==============================================================
class CCollisionMesh : public CCollision
{
public:
	CCollisionMesh();
	~CCollisionMesh();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCyinder* inCyinder, bool isExtrusion);	// TODO �݂����̂�I������炱�����ɓ����蔻��ڍs����
	bool ToSphere(CCollisionSphere* inSphere);

	static CCollisionMesh* Create(int inPrimitive, LPDIRECT3DVERTEXBUFFER9 inVtxBuff, LPDIRECT3DINDEXBUFFER9 inIdxBuff, D3DXMATRIX inMtxWorld);

	float GetExtrusionHeight() { return m_extrusionHeight; }

private:
	int m_primitive;
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;
	LPDIRECT3DINDEXBUFFER9 m_idxBuff;
	D3DXMATRIX m_mtxWorld;
	float m_extrusionHeight;	// �����o������
};

#endif	// _COLLISION_MESH_H_