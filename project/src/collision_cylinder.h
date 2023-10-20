//**************************************************************
//
// �����蔻��
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _COLLISION_CYLINDER_H_			// ���̃}�N����`������ĂȂ�������
#define _COLLISION_CYLINDER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "collision.h"

class CCollisionMesh;
class CCollisionBox;
class CCollisionSphere;

class CCollisionCylinder : public CCollision
{
public:
	CCollisionCylinder();
	~CCollisionCylinder();

	HRESULT Init();
	void Uninit();

	bool ToCylinder(CCollisionCylinder* inCyinder) override;
	bool ToBox(CCollisionBox* inBox, bool isExtrusion) override;
	bool ToSphere(CCollisionSphere* inSphere) override;

	static CCollisionCylinder* Create(const D3DXVECTOR3& pos, const float length ,const float height);

	D3DXVECTOR3 GetExtrusion() { return m_extrusion; }
	float GetLength() { return m_length; }
	float GetHeight() { return m_height; }

private:
	float m_length;
	float m_height;

	D3DXVECTOR3 m_extrusion; //	�����o���l
};

#endif