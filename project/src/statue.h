//**************************************************************
//
// ��
// Author: ���c �喲
//
//**************************************************************
#ifndef _STATUE_H_
#define _STATUE_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// �O���錾
//==============================================================
class CCollisionBox;
class CCollisionCylinder;
class CPlayer;

//==============================================================
// �N���X
//==============================================================
class CStatue : public CObjectX
{
public:
	CStatue(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CStatue();

	HRESULT Init() override;
	HRESULT Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot);
	void Uninit() override;
	void Update() override;
	void Draw() override; 

	static CStatue* Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3 & inRot);
	CCollisionBox* GetCollisionBox() { return m_collisionBox; }
	CCollisionCylinder* GetCollisionCylinder() { return m_collisionCylinder; }

	bool Touch(CPlayer* pPlayer);
protected:
	std::string m_modelData;
	CCollisionBox* m_collisionBox;
	CCollisionCylinder* m_collisionCylinder;

	CPlayer* m_player;
};
#endif	// _ITEM_MODEL_H_
