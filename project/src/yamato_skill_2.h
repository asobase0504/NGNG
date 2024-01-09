//**************************************************************
//
// �X�L��(�u�����N)
// Author : ����]��
//
//**************************************************************
#ifndef _YAMATO_SKILL_2_H_			// ���̃}�N����`������ĂȂ�������
#define _YAMATO_SKILL_2_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;
class CCollision;

//==============================================================
// �X�L���N���X
//==============================================================
class CYamatoSkill_2 : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CYamatoSkill_2();
	~CYamatoSkill_2();

	// �ÓI�����o�֐�
	static CYamatoSkill_2	*Create(CCharacter* chara);		// �X�L���̐���

	void InitAbility() override;							// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;							// ������
	void UninitAbility() override;							// �I��
	void HitAbility(CCharacter* Target) override;			// �X�L���������������̌���

private:		// �����o�ϐ�
	int m_Time;												// ����
};
#endif