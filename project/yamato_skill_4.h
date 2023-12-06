//**************************************************************
//
// �X�L��()
// Author : ����]��
//
//**************************************************************
#ifndef _YAMATO_SKILL_4_H_			// ���̃}�N����`������ĂȂ�������
#define _YAMATO_SKILL_4_H_			// ��d�C���N���[�h�h�~�̃}�N����`

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
class CYamatoSkill_4 : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CYamatoSkill_4(int nPriority = 3);
	~CYamatoSkill_4();

	// �ÓI�����o�֐�
	static CYamatoSkill_4	*Create(CCharacter* chara);					// �X�L���̐���

	void InitAbility() override;										// �X�L�����n�܂�Ƃ�
	void HitAbility(CCharacter* Target) override;						// �X�L���������������̌���

private:		// �����o�ϐ�

};
#endif