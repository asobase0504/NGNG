//**************************************************************
//
// �G
// Author : ���c�喲
//
//**************************************************************
#ifndef _ENEMY_H_			// ���̃}�N����`������ĂȂ�������
#define _ENEMY_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "character.h"

//==============================================================
// �O���錾
//==============================================================
class CObjectX;
class CController;

//==============================================================
// �v���C���[�N���X
//==============================================================
class CEnemy : public CCharacter
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CEnemy(int nPriority = 3);
	~CEnemy();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// �v���C���[�̐���

private:
	void Updatepos();			// ���W�̍X�V

private:		// �����o�ϐ�
	D3DXVECTOR3		m_posold;		// �O��̈ʒu
	D3DXVECTOR3		m_move;			// �ړ���
};
#endif