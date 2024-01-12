//**************************************************************
//
// �L�c�l�̃X�L��(�ʏ�U��)
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _FOX_SKILL_H_	// ���̃}�N����`������ĂȂ�������
#define _FOX_SKILL_H_	// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// �X�L���N���X
//==============================================================
class CFoxSkill : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CFoxSkill();
	~CFoxSkill();

	// �ÓI�����o�֐�
	static CFoxSkill* Create(CCharacter* chara);		// �X�L���̐���

	void InitAbility() override;		// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;		// �X�L����
	void UninitAbility() override;		// �X�L���I����
	void HitAbility(CCharacter* Target) override;	// �X�L���������������̌���

private:		// �����o�ϐ�

	D3DXVECTOR3 m_effectPos;
	float m_effectRot;
	int m_effectCnt;
};
#endif