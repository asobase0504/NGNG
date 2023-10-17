//**************************************************************
//
// �����蔻��
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_SPHERE_H_			// ���̃}�N����`������ĂȂ�������
#define _COLLISION_SPHERE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "collision.h"

class CCollisionBox;
class CCollisionCyinder;
class CCollisionMesh;

class CCollisionSphere : public CCollision
{
public:
	CCollisionSphere();
	~CCollisionSphere();

	HRESULT Init();
	void Uninit();

	//bool ToCylinder(CCollisionCyinder* inCyinder);
	bool ToMesh(CCollisionMesh* inMesh, bool isExtrusion);
	bool ToBox(CCollisionBox* inBox);
	bool ToSphere(CCollisionSphere* inSphere);

	static CCollisionSphere* Create(const D3DXVECTOR3& pos,const float length);

	float GetLength() { return m_length; }
	float GetExtrusionHeight() { return m_extrusionHeight; }

private:
	float m_length;
	float m_extrusionHeight;	// �����o������
};

#endif