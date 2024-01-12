//**************************************************************
//
// �X�L��(�ʏ�U��)
// Author : ����]��
//
//**************************************************************
#ifndef _YAMATO_SKILL_1_H_			// ���̃}�N����`������ĂȂ�������
#define _YAMATO_SKILL_1_H_			// ��d�C���N���[�h�h�~�̃}�N����`

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
class CYamatoSkill_1 : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CYamatoSkill_1();
	~CYamatoSkill_1();

	// �ÓI�����o�֐�
	static CYamatoSkill_1* Create(CCharacter* chara);		// �X�L���̐���

	void InitAbility() override;					// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;				// �X�L����
	void UninitAbility() override;				// �X�L����
	void HitAbility(CCharacter* Target) override;	// �X�L���������������̌���

private:		// �����o�ϐ�

	D3DXVECTOR3 m_effectPos;
	float m_effectRot;
	int m_effectCnt;
};
#endif