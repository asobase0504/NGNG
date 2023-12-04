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
class CLine;

class CCollisionCylinder : public CCollision
{
public:
	CCollisionCylinder();
	~CCollisionCylinder();

	HRESULT Init();
	void Update();

	bool ToCylinder(CCollisionCylinder* inCyinder) override;
	bool ToBox(CCollisionBox* inBox, bool isExtrusion) override;
	bool ToSphere(CCollisionSphere* inSphere) override;
	bool ToMesh(CCollisionMesh* inMesh) override;

	// ���: ���W ���: ���� ��O : ����
	static CCollisionCylinder* Create(const D3DXVECTOR3& pos, const float length ,const float height);

	void SetLength(float inLength) { m_length = inLength; }
	float GetLength() { return m_length; }

	void SetHeight(float inHeight) { m_height = inHeight; }
	float GetHeight() { return m_height; }

private:
	float m_length;
	float m_height;
	CLine* m_line[4];
};

#endif