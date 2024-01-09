//**************************************************************
//
// �X�L��(�ʏ�U��)
// Author : ����]��
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
// �R���X�g���N�^
//--------------------------------------------------------------
CGasyadokuroSummonSkill::CGasyadokuroSummonSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CGasyadokuroSummonSkill::~CGasyadokuroSummonSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
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
// ���
//--------------------------------------------------------------
void CGasyadokuroSummonSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CGasyadokuroSummonSkill *CGasyadokuroSummonSkill::Create(CCharacter* chara)
{
	CGasyadokuroSummonSkill* pSkill = new CGasyadokuroSummonSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "GASYADOKURO_SUMMON_SKILL";
	pSkill->Init();

	return pSkill;
}