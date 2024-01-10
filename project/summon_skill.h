//**************************************************************
//
// �����X�L��
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SUMMON_SKILL_H_			// ���̃}�N����`������ĂȂ�������
#define _SUMMON_SKILL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "skill_entity.h"
#include "enemy_data_base.h"

//==============================================================
// �����X�L��(��b)
//==============================================================
class CSummonSkill : public CSkillEntity
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSummonSkill();
	~CSummonSkill();

	void InitAbility() override;		// �X�L�����n�܂�Ƃ�

protected:
	virtual CEnemyDataBase::EEnemyType SummonType() = 0;
};

//==============================================================
// �����X�L��(�L�c�l)
//==============================================================
class CFoxSummonSkill : public CSummonSkill
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CFoxSummonSkill() {};
	~CFoxSummonSkill() {};

	static CFoxSummonSkill* Create(CCharacter* chara);
private:
	virtual CEnemyDataBase::EEnemyType SummonType() { return CEnemyDataBase::EEnemyType::FOX; };
};

//==============================================================
// �����X�L��(�[��)
//==============================================================
class CSkeltonSummonSkill : public CSummonSkill
{
public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	explicit CSkeltonSummonSkill() {};
	~CSkeltonSummonSkill() {};

	static CSkeltonSummonSkill* Create(CCharacter* chara);
private:
	virtual CEnemyDataBase::EEnemyType SummonType() { return CEnemyDataBase::EEnemyType::SKELTON; };
};
#endif