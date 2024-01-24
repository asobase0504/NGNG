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
#include "summon_skill.h"
#include "utility.h"
#include "map.h"

#include "enemy_manager.h"
#include "application.h"
#include "mode.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSummonSkill::CSummonSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSummonSkill::~CSummonSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CSummonSkill::InitAbility()
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
		CApplication::GetInstance()->GetModeClass()->GetMap()->CreateEnemy(posSummon, SummonType());
	}
}

//==============================================================
// �����X�L��(�L�c�l)
//==============================================================
CFoxSummonSkill * CFoxSummonSkill::Create(CCharacter * chara)
{
	CFoxSummonSkill* pSkill = new CFoxSummonSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}

//==============================================================
// �����X�L��(�[��)
//==============================================================
CSkeltonSummonSkill * CSkeltonSummonSkill::Create(CCharacter * chara)
{
	CSkeltonSummonSkill* pSkill = new CSkeltonSummonSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}
