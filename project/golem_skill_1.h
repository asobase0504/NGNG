//**************************************************************
//
// �X�L��
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _GOLEM_SKILL_1_H_		// ���̃}�N����`������ĂȂ�������
#define _GOLEM_SKILL_1_H_		// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// �O���錾
//==============================================================
class CObjectPolygon3D;
class CRoad;
class CBullet;
class CCollision;

//==============================================================
// �X�L���N���X
//==============================================================
class CGolemSkill_1 : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CGolemSkill_1();
	~CGolemSkill_1();

	void Uninit();

	// �ÓI�����o�֐�
	static CGolemSkill_1 *Create(CCharacter* chara);	// �X�L���̐���

	// �X�L��
	void InitAbility() override;					// �n�܂�Ƃ�
	void AllWayAbility() override;					// ������
	void HitAbility(CCharacter* Target) override;	// �����������̌���

private:		// �����o�ϐ�
	CRoad* m_road;

	CBullet* m_bullet;
	CObjectPolygon3D* m_bulletDesign;

	CCharacter* m_aimCharacter;

	bool m_isCharge;
	int m_chargeTime;
};
#endif