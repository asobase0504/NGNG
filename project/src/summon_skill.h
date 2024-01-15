//**************************************************************
//
// 召喚スキル
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SUMMON_SKILL_H_			// このマクロ定義がされてなかったら
#define _SUMMON_SKILL_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "skill_entity.h"
#include "enemy_data_base.h"

//==============================================================
// 召喚スキル(基礎)
//==============================================================
class CSummonSkill : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CSummonSkill();
	~CSummonSkill();

	void InitAbility() override;		// スキルが始まるとき

protected:
	virtual CEnemyDataBase::EEnemyType SummonType() = 0;
};

//==============================================================
// 召喚スキル(キツネ)
//==============================================================
class CFoxSummonSkill : public CSummonSkill
{
public:
	// コンストラクタとデストラクタ
	explicit CFoxSummonSkill() {};
	~CFoxSummonSkill() {};

	static CFoxSummonSkill* Create(CCharacter* chara);
private:
	virtual CEnemyDataBase::EEnemyType SummonType() { return CEnemyDataBase::EEnemyType::FOX; };
};

//==============================================================
// 召喚スキル(骸骨)
//==============================================================
class CSkeltonSummonSkill : public CSummonSkill
{
public:
	// コンストラクタとデストラクタ
	explicit CSkeltonSummonSkill() {};
	~CSkeltonSummonSkill() {};

	static CSkeltonSummonSkill* Create(CCharacter* chara);
private:
	virtual CEnemyDataBase::EEnemyType SummonType() { return CEnemyDataBase::EEnemyType::SKELTON; };
};
#endif