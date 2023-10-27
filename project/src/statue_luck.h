//**************************************************************
//
// �^�̍Ւd
// Author : ���c�喲
//
//**************************************************************
#ifndef _STATUE_LUCK_H_			// ���̃}�N����`������ĂȂ�������
#define _STATUE_LUCK_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "statue.h"

//==============================================================
// �}�N���錾
//==============================================================

//==============================================================
// �O���錾
//==============================================================
class CPlayer;
class CCollisionBox;
class CCollisionCylinder;

//==============================================================
// �G�N���X
//==============================================================
class CStatueLuck : public CStatue
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CStatueLuck(int nPriority = 3);
	~CStatueLuck();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// �ÓI�����o�֐�
	static CStatueLuck *Create(D3DXVECTOR3 pos);			// ���̍Ւd�̐���

private:	// �����o�ϐ�
	CPlayer* m_pPlayer;
	int m_nUseMoney;		// �����K�v������
	int m_nItemCount;		// �A�C�e����
	bool m_bChance;			// �����m��
	bool m_bOnce;			// ��񏈗��p
};
#endif
