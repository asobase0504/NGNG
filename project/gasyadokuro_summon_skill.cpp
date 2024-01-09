//**************************************************************
//
// スキル(通常攻撃)
// Author : 髙野馨將
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "gasyadokuro_summon_skill.h"
#include "utility.h"
#include "map.h"

#include "enemy_manager.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CGasyadokuroSummonSkill::CGasyadokuroSummonSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CGasyadokuroSummonSkill::~CGasyadokuroSummonSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CGasyadokuroSummonSkill::InitAbility()
{
	m_Duration = 20;

	int summonCount = IntRandom(5, 1);
	D3DXVECTOR3 posChara = m_apChara->GetPos();
	D3DXVECTOR3 posSummon = m_apChara->GetPos();
	for (int i = 0; i < summonCount; i++)
	{
		posSummon = posChara;
		posSummon.x += FloatRandom(400.0f, -400.0f);
		posSummon.z += FloatRandom(400.0f, -400.0f);
		CMap::GetMap()->CreateEnemy(posSummon, CEnemyDataBase::EEnemyType::SKELTON);
	}
}

//--------------------------------------------------------------
// 常に
//--------------------------------------------------------------
void CGasyadokuroSummonSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CGasyadokuroSummonSkill *CGasyadokuroSummonSkill::Create(CCharacter* chara)
{
	CGasyadokuroSummonSkill* pSkill = new CGasyadokuroSummonSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "GASYADOKURO_SUMMON_SKILL";
	pSkill->Init();

	return pSkill;
}