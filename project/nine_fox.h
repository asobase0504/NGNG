//**************************************************************
//
// ���
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _NINE_FOX_H_			// ���̃}�N����`������ĂȂ�������
#define _NINE_FOX_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "enemy.h"

//==============================================================
// �G�N���X
//==============================================================
class CNineFox : public CEnemy
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CNineFox();
	~CNineFox();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Update() override;

private:
	void Move() override;		// �ړ�
};
#endif