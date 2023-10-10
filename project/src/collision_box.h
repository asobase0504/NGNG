//**************************************************************
//
// �����蔻��
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_BOX_H_			// ���̃}�N����`������ĂȂ�������
#define _COLLISION_BOX_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "collision.h"

class CCollisionMesh;
class CCollisionCyinder;
class CCollisionSphere;

class CCollisionBox : public CCollision
{
public:
	CCollisionBox();
	~CCollisionBox();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCyinder* inCyinder);
	bool ToMesh(CCollisionMesh* inMesh);
	bool ToBox(CCollisionBox* inBox);
	bool ToSphere(CCollisionSphere* inSphere);

private:

};

#endif