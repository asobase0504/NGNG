//**************************************************************
//
// �X�L��(�J�E���^�[)
// Author : ����]��
//
//**************************************************************
#ifndef _SKILL6_H_			// ���̃}�N����`������ĂȂ�������
#define _SKILL6_H_			// ��d�C���N���[�h�h�~�̃}�N����`

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
class CSkill6 : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSkill6(int nPriority = 3);
	~CSkill6();

	// �ÓI�����o�֐�
	static CSkill6	*Create(CCharacter* chara);					// �X�L���̐���

	void InitAbility() override;										// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;										// ������
	void UninitAbility() override;										// �I��
	void HitAbility(CCharacter* Target) override;						// �X�L���������������̌���

private:		// �����o�ϐ�	
};
#endif