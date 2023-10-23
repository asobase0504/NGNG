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

#ifdef _DEBUG
	CDebugProc::Print("XLΜN[^C : %d\n", m_CT);
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
// XL½θ»θ
//--------------------------------------------------------------
void CSkill::CollisionSkill(std::string tag)
{
	// XLf[^ΜCX^XπζΎ·ι
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_apChara != nullptr)
	{
		// ½θ»θ
		m_Collision = CCollisionSphere::Create(m_apChara->GetPos(), pSkillData->GetSize(tag).x);
		std::vector<CEnemy*> Enemy = CEnemyManager::GetInstance()->GetEnemy();
		// Gl~[ΜπζΎ
		int EnemyCount = Enemy.size();

		for (int nCnt = 0; nCnt < EnemyCount; nCnt++)
		{// UΝΝΙGͺ’ι©»θ·ι
			m_isCollision = false;
			m_isCollision = m_Collision->ToSphere((CCollisionSphere*)Enemy[nCnt]->GetCollision());

			if (m_isCollision)
			{// hitΙΆ¬
				pSkillData->GetHitAbility(tag);
			}
		}
	}
}

//--------------------------------------------------------------
// XL1
//--------------------------------------------------------------
void CSkill::Skill1()
{
	if (m_CT == 0)
	{// N[^CͺΘ―κΞ½θ»θπΆ¬·ι
		CollisionSkill("YAMATO_SKILL_1");
	}

	// N[^CΜέθ
	m_CT = CSkillDataBase::GetInstance()->GetCT("YAMATO_SKILL_2");
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