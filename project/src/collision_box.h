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
class CCollisionCylinder;
class CCollisionSphere;

class CCollisionBox : public CCollision
{
public:
	CCollisionBox();
	~CCollisionBox();

	HRESULT Init();
	void Uninit();

	//bool ToCylinder(CCollisionCylinder* inCyinder,bool isExtrusion);
	//bool ToMesh(CCollisionMesh* inMesh);
	//bool ToBox(CCollisionBox* inBox);
	//bool ToSphere(CCollisionSphere* inSphere);

	static CCollisionBox* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size);

	D3DXVECTOR3 GetSize() { return m_size; }

private:
	D3DXVECTOR3 m_size;
};

#endif