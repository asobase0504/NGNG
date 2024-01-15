//**************************************************************
//
// �X�P���g��
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKELTON_SKILL_H_			// ���̃}�N����`������ĂȂ�������
#define _SKELTON_SKILL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// �X�L���N���X
//==============================================================
class CSkeltonSkill : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSkeltonSkill();
	~CSkeltonSkill();

	// �ÓI�����o�֐�
	static CSkeltonSkill* Create(CCharacter* chara);		// �X�L���̐���

	void InitAbility() override;					// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;					// �X�L����
	void UninitAbility() override;					// �X�L���I����
	void HitAbility(CCharacter* Target) override;	// �X�L���������������̌���

private:	// �����o�ϐ�
	int m_time;
};
#endif