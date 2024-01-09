//**************************************************************
//
// �X�L��(�ʏ�U��)
// Author : ����]��
//
//**************************************************************
#ifndef _GASYADOKURO_SUMMON_SKILL_H_			// ���̃}�N����`������ĂȂ�������
#define _GASYADOKURO_SUMMON_SKILL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

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
class CGasyadokuroSummonSkill : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CGasyadokuroSummonSkill();
	~CGasyadokuroSummonSkill();

	// �ÓI�����o�֐�
	static CGasyadokuroSummonSkill* Create(CCharacter* chara);		// �X�L���̐���

	void InitAbility() override;					// �X�L�����n�܂�Ƃ�
	void AllWayAbility() override;					// �X�L����

private:		// �����o�ϐ�

	D3DXVECTOR3 m_effectPos;
	float m_effectRot;
	int m_effectCnt;
};
#endif