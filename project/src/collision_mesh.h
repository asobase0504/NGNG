//**************************************************************
//
// �����蔻��
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_MESH_H_			// ���̃}�N����`������ĂȂ�������
#define _COLLISION_MESH_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "collision_mesh.h"

class CCollisionBox;
class CCollisionCyinder;
class CCollisionSphere;

class CCollisionMesh : public CCollision
{
public:
	CCollisionMesh();
	~CCollisionMesh();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCyinder* inCyinder);
	bool ToMesh(CCollisionMesh* inMesh);
	bool ToBox(CCollisionBox* inBox);
	bool ToSphere(CCollisionSphere* inSphere);

private:

};

#endif