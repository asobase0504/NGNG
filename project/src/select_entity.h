//**************************************************************
//
// �I���ł������
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _SELECT_ENTITY_H_
#define _SELECT_ENTITY_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// �O���錾
//==============================================================
class CCollisionCylinder;
class CCollisionBox;
class CCharacter;
class CSelectUI;
class CProcedure3D;

//==============================================================
// �N���X
//==============================================================
class CSelectEntity : public CObjectX
{
public:
	CSelectEntity();
	~CSelectEntity();

	HRESULT Init() override;

	void Update() override;

	CCollisionCylinder* GetSelectCollision() { return m_collisionCylinder; }
	CCollisionBox* GetCollisionBox() { return m_collisionBox; }

	void DisplayUI();
	void NoDisplayUI() { m_isNearCharacter = false; }

	virtual bool Select(CCharacter* selectCharacter) = 0;	// �I�΂ꂽ���̏���

	CProcedure3D* GetCostUI() { return m_costUI; }

protected:
	CCollisionCylinder* m_collisionCylinder;	// �I���ł��铖���蔻��
	CCollisionBox* m_collisionBox;				// �����o�����s�Ȃ������蔻��
	CSelectUI* m_ui;
	CProcedure3D* m_costUI;	//�R�X�g��3D��ԏ�ɕ`��
	std::string m_uiText;
	bool m_isNearCharacter;		// �L�����N�^�[�Ɉ�ԋ߂��G���e�B�e�B�ł��邩�ۂ�
};
#endif	// _ITEM_MODEL_H_
