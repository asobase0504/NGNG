//**************************************************************
//
// ���̍Ւd
// Author : ���c�喲
//
//**************************************************************
#ifndef _STATUE_BLOOD_H_			// ���̃}�N����`������ĂȂ�������
#define _STATUE_BLOOD_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "statue.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;

//==============================================================
// �G�N���X
//==============================================================
class CStatueBlood : public CStatue
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CStatueBlood(int nPriority = 3);
	~CStatueBlood();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;

	bool Select(CCharacter* selectCharacter) override;

	// �ÓI�����o�֐�
	static CStatueBlood *Create(D3DXVECTOR3 pos);			// ���̍Ւd�̐���

private:	// �����o�ϐ�
	float m_hpSubRate;	// HP����銄��
};
#endif
