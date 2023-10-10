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
#include "object.h"

//==============================================================
// �}�N���錾
//==============================================================
#define DASH_SPEED	(3.0f)

//==============================================================
// �O���錾
//==============================================================
class CObjectX;
class CController;

//==============================================================
// �v���C���[�N���X
//==============================================================
class CPlayer : public CObject
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
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// �v���C���[�̐���

	// Setter
	void SetController(CController* inOperate);

private:
	void Move();				// �ړ�
	void Jump();				// �W�����v
	void Dash();				// �_�b�V��
	void Updatepos();			// ���W�̍X�V

private:		// �����o�ϐ�
	D3DXVECTOR3		m_rot;			// �p�x
	D3DXVECTOR3		m_rotDest;		// �ړI�̊p�x�̕ۑ�
	D3DXVECTOR3		m_move;			// �ړ���

	bool			m_isjump;		// �W�����v���Ă��邩�ǂ���
	bool			m_isdash;		// �_�b�V�����Ă��邩�ǂ���

	D3DXMATRIX		m_mtxWorld;					// ���[���h�}�g���b�N�X
	CController*	m_controller;				// ���߂��o���l
	std::vector<CObjectX*>		m_apModel;		// ���f���̃C���X�^���X
};
#endif