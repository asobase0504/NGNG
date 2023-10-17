//**************************************************************
//
// �����蔻��
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_H_			// ���̃}�N����`������ĂȂ�������
#define _COLLISION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "object.h"

class CCollisionMesh;
class CCollisionCyinder;
class CCollisionSphere;
class CCollisionBox;

class CCollision : public CObject
{
public:
	CCollision();
	~CCollision();

	void Draw() final {}

	virtual bool ToCylinder(CCollisionCyinder* inCyinder) { return false; }
	virtual bool ToMesh(CCollisionMesh* inMesh) { return false; }
	virtual bool ToBox(CCollisionBox* inBox, bool isExtrusion) { return false; }
	virtual bool ToSphere(CCollisionSphere* inSphere) { return false; }
};
#endif