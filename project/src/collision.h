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

class CCollision : public CObject
{
public:
	CCollision();
	~CCollision();

	void Draw() final {}

	bool ToCylinder() {}
	bool ToMesh() {}
	bool ToBox() {}
	bool ToSphere() {}
};

#endif