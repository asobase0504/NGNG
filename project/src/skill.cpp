//**************************************************************
//
// XL
// Author : ϋόμ]
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "skill.h"
#include "skill_data_base.h"
#include "skill_entity.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "collision_sphere.h"

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
// ϊ»
//--------------------------------------------------------------
HRESULT CSkill::Init()
{
	// ϊ»
	m_CT = 0;

	return S_OK;
}

//--------------------------------------------------------------
// IΉ
//--------------------------------------------------------------
void CSkill::Uninit(void)
{
	// jό
	CTask::Uninit();
}

//--------------------------------------------------------------
// XV
//--------------------------------------------------------------
void CSkill::Update(void)
{
	// XLf[^ΜCX^XπζΎ·ι
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_CT > 0)
	{// N[^Cͺ κΞΈ­³Ήι
		m_CT--;
	}
	
	m_atkSpd = m_apChara->GetAtkSpd()->GetCurrent();

	// EntityͺSρΎB
	if (GetEndChildrenSize() == 0)
	{

	}

#ifdef _DEBUG
	CDebugProc::Print("%sΜN[^C : %d\n", m_Name.c_str(),m_CT);
#endif // _DEBUG
}

//--------------------------------------------------------------
// XLΆ¬
//--------------------------------------------------------------
CSkill *CSkill::Create()
{
	// Ά¬
	CSkill* pSkill = new CSkill;
	pSkill->Init();

	return pSkill;
}

//--------------------------------------------------------------
// XL1
//--------------------------------------------------------------
void CSkill::Skill()
{
	if (m_CT == 0)
	{// N[^CͺΘ―κΞ½θ»θπΆ¬·ι
		// ½θ»θΜ±ΤΜΗ
		CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
		pSkillData->GetDuration(m_Name);
		CSkillEntity* entity = pSkillData->GetAbility(m_Name)(m_apChara);

		// eqΦWΜ\z
		SetEndChildren(entity);

		// N[^CΜέθ
		m_CT = pSkillData->GetCT(m_Name) * m_atkSpd;
	}
}

//--------------------------------------------------------------
// XLΜέθ
//--------------------------------------------------------------
void CSkill::SetSkill(std::string tag, CCharacter *chara)
{
	// Ά¬
	m_Name = tag;
	m_apChara = chara;
}