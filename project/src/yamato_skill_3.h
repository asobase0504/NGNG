//**************************************************************
//
// �X�L��(��]�؂�)
// Author : ����]��
//
//**************************************************************
#ifndef _YAMATO_SKILL_3_H_			// ���̃}�N����`������ĂȂ�������
#define _YAMATO_SKILL_3_H_			// ��d�C���N���[�h�h�~�̃}�N����`

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
class CYamatoSkill_3 : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CYamatoSkill_3();
	~CYamatoSkill_3();

	// �ÓI�����o�֐�
	static CYamatoSkill_3	*Create(CCharacter* chara);					// �X�L���̐���

	void InitAbility() override;					// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;					// ������
	void HitAbility(CCharacter* Target) override;	// �X�L���������������̌���
	void UninitAbility() override;					// �I��

private:		// �����o�ϐ�
	int m_time;
};
#endif