//**************************************************************
//
// ������(��)
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _MONSTER_SKY_H_			// ���̃}�N����`������ĂȂ�������
#define _MONSTER_SKY_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "enemy.h"

//==============================================================
// �G�N���X
//==============================================================
class CMonsterSky : public CEnemy
{
private:
	enum EActiveType
	{

	};
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CMonsterSky();
	~CMonsterSky();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Update() override;

private:
	void Move() override;		// �ړ�
};
#endif