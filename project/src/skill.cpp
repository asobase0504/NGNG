//**************************************************************
//
// XL
// Author : ûüì]
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "skill.h"
#include "skill_data_base.h"
#include "player_manager.h"

//--------------------------------------------------------------
// RXgN^
//--------------------------------------------------------------
CSkill::CSkill(int nPriority)
{

}

//--------------------------------------------------------------
// fXgN^
//--------------------------------------------------------------
CSkill::~CSkill()
{

}

//--------------------------------------------------------------
// ú»
//--------------------------------------------------------------
HRESULT CSkill::Init()
{
	// ú»
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		m_CT[nCnt] = 0;
	}

	return S_OK;
}

//--------------------------------------------------------------
// I¹
//--------------------------------------------------------------
void CSkill::Uninit(void)
{
	
}

//--------------------------------------------------------------
// XV
//--------------------------------------------------------------
void CSkill::Update(void)
{
	// CTÌ¸­
	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		if (m_CT[nCnt] > 0)
		{
			m_CT[nCnt]--;
		}
	}
	
	// XL1ÌCX^Xðæ¾
	CSkillDataBase::GetInstance()->GetAbility(m_Name)(m_apChara);		// ­®É¶¬
}

//--------------------------------------------------------------
// XL¶¬
//--------------------------------------------------------------
CSkill *CSkill::YamatoSkill(std::string tag, CCharacter *chara)
{
	// ¶¬
	CSkill* pSkill = new CSkill;
	pSkill->Init();
	pSkill->m_Name = tag;
	pSkill->m_apChara = chara;

	return pSkill;
}
