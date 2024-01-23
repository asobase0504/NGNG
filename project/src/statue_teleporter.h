//**************************************************************
//
// �e���|�[�^�[�̍Ւd
// Author : ���c�喲
//
//**************************************************************
#ifndef _STATUE_TELEPORTER_H_			// ���̃}�N����`������ĂȂ�������
#define _STATUE_TELEPORTER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "statue.h"

//==============================================================
// �O���錾
//==============================================================
class CEnemy;
class CCollisionBox;
class CCollisionCylinder;

//==============================================================
// �e���|�[�^�[�N���X
//==============================================================
class CStatueTeleporter : public CStatue
{
public:
	static const int CHARGE_TIME;
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CStatueTeleporter(int nPriority = 3);
	~CStatueTeleporter();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;
	void	Update() override;

	bool Select(CCharacter* selectCharacter) override;

	// �ÓI�����o�֐�
	static CStatueTeleporter *Create(D3DXVECTOR3 pos);			// �e���|�[�^�[�̐���

private:	// �����o�ϐ�
	CEnemy* m_pEnemy;
	int m_time;
	bool m_bOnce;
	bool m_btimeAdd;
	bool m_isBossDead;
};
#endif


