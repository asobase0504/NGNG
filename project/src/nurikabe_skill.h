//**************************************************************
//
// �ʂ肩��
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _NURIKABE_SKILL_H_			// ���̃}�N����`������ĂȂ�������
#define _NURIKABE_SKILL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;

//==============================================================
// �X�L���N���X
//==============================================================
class CNurikabeSkill : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CNurikabeSkill();
	~CNurikabeSkill();

	// �ÓI�����o�֐�
	static CNurikabeSkill* Create(CCharacter* chara);		// �X�L���̐���

	void InitAbility() override;					// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;					// �X�L����
	void UninitAbility() override;					// �X�L���I����
	void HitAbility(CCharacter* Target) override;	// �X�L���������������̌���

private:	// �����o�ϐ�
	int m_time;
	CCharacter* m_aimCharacter;	// �_������
};
#endif