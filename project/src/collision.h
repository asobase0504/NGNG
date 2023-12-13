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
#include "task.h"

class CCollisionMesh;
class CCollisionCylinder;
class CCollisionSphere;
class CCollisionBox;

class CCollision : public CTask
{
public:
	CCollision();
	~CCollision();

	void Update();
	void Draw() final {}

	virtual bool ToCylinder(CCollisionCylinder* inCyinder) { return false; }
	virtual bool ToMesh(CCollisionMesh* inMesh) { return false; }
	virtual bool ToBox(CCollisionBox* inBox, bool isExtrusion) { return false; }
	virtual bool ToSphere(CCollisionSphere* inSphere) { return false; }

	void SetParent(D3DXVECTOR3* inPos) { m_posParent = inPos; }
	void SetPosParent(D3DXVECTOR3 inPos) {
		if (m_posParent == nullptr)
		{
			return;
		}
		*m_posParent = inPos;
	}

	/* �ʒu�n */
	void SetPos(const D3DXVECTOR3& inPos) { m_posLocal = inPos; }
	const D3DXVECTOR3 &GetPosWorld();

	/* �ʒu�n */
	void SetPosOld(const D3DXVECTOR3& inPosOld) { m_posOld = inPosOld; }
	const D3DXVECTOR3 &GetPosOld() const { return m_posOld; }

	/* �����n */
	void SetRot(const D3DXVECTOR3& inRot) { m_rot = inRot; }
	const D3DXVECTOR3 &GetRot() const { return m_rot; }

	/* �傫���n */
	void SetSize(const D3DXVECTOR3& inSize) { m_size = inSize; SetLine(); }
	const D3DXVECTOR3 &GetSize() const { return m_size; }

	/* ���[���h�}�g���b�N�X */
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtx = mtxWorld; }
	const D3DXMATRIX& GetMtxWorld() { return m_mtx; }

	/* ��ɓ������� */
	void SetIsTop(bool isTop) { m_isTop = isTop; }
	bool GetIsTop() { return m_isTop; }

	/* ���ɓ������� */
	void SetIsUnder(bool isUnder) { m_isUnder = isUnder; }
	bool GetIsUnder() { return m_isUnder; }

private:
	virtual void SetLine() = 0;
private:
	D3DXVECTOR3* m_posParent;
	D3DXVECTOR3 m_posWorld;
	D3DXVECTOR3 m_posLocal;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtx;
	bool m_isTop;
	bool m_isUnder;

	int m_hitMeshIdx;
};
#endif