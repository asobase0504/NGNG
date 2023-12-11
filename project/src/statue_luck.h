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
class CProcedure3D;

//==============================================================
// �G�N���X
//==============================================================
class CStatueLuck : public CStatue
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CStatueLuck();
	~CStatueLuck();

	//�v���g�^�C�v�錾
	HRESULT	Init() override;

	bool Select(CCharacter* selectCharacter) override;

	// �ÓI�����o�֐�
	static CStatueLuck *Create(D3DXVECTOR3 pos);	// �^�̍Ւd�̐���

	void SetPos(const D3DXVECTOR3& inPos) override;

private:	// �����o�ϐ�
	int m_nUseMoney;		// �����K�v������
	int m_nItemCount;		// �A�C�e����
	CProcedure3D* m_useMoneyUI;	// �K�v���z��3D��ԏ�ɕ`��
};
#endif

