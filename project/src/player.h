//**************************************************************
//
// �v���C���[
// Author : ����]��
//
//**************************************************************
#ifndef _PLAYER_H_			// ���̃}�N����`������ĂȂ�������
#define _PLAYER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "character.h"

//==============================================================
// �}�N���錾
//==============================================================
#define DASH_SPEED	(1.5f)
#define JUMP		(15.0f)

//==============================================================
// �O���錾
//==============================================================
class CController;
class CCollisionCyinder;

//==============================================================
// �v���C���[�N���X
//==============================================================
class CPlayer : public CCharacter
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CPlayer(int nPriority = 3);
	~CPlayer();
	
	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos);			// �v���C���[�̐���

	// Setter
	void SetController(CController* inOperate);
	CCollisionCyinder* GetCylinder() { return m_collisionCyinder; }

private:
	void Attack();				// �U��
	void Move();				// �ړ�
	void Jump();				// �W�����v
	void Dash();				// �_�b�V��

private:		// �����o�ϐ�
	int				m_SkillStock;	// �X�L���X�g�b�N��

	bool			m_isjump;		// �W�����v���Ă��邩�ǂ���
	bool			m_isdash;		// �_�b�V�����Ă��邩�ǂ���

	CController*	m_controller;	// ���߂��o���l
	CCollisionCyinder* m_collisionCyinder;
};
#endif