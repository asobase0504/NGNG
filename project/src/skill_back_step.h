//**************************************************************
//
// �o�b�N�X�e�b�v
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKILL_BACK_STEP_H_			// ���̃}�N����`������ĂȂ�������
#define _SKILL_BACK_STEP_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// �X�L���N���X
//==============================================================
class CSkillBackStep : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSkillBackStep();
	~CSkillBackStep();

	// �ÓI�����o�֐�
	static CSkillBackStep* Create(CCharacter* chara);		// �X�L���̐���

	void InitAbility() override;					// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;					// �X�L����
	void UninitAbility() override;					// �X�L���I����
	void HitAbility(CCharacter* Target) override;	// �X�L���������������̌���

private:	// �����o�ϐ�
	int m_time;
};
#endif