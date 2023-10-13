#include "skill_data_base.h"

CSkillDataBase* CSkillDataBase::m_instance = nullptr;

CSkillDataBase::CSkillDataBase()
{
}

CSkillDataBase * CSkillDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CSkillDataBase;
		
		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

CSkillDataBase::~CSkillDataBase()
{
}

void CSkillDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}

void CSkillDataBase::Init()
{
	m_skillDataBase["YAMATO_SKILL_1"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // ”­“®Žž‚ÌŒø‰Ê

	},
		[](CCharacter* inusedCharacter)
	{ // HitŽž‚ÌŒø‰Ê

	} };
	m_skillDataBase["YAMATO_SKILL_2"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // ”­“®Žž‚ÌŒø‰Ê

	},
		[](CCharacter* inusedCharacter)
	{ // HitŽž‚ÌŒø‰Ê

	} };
	m_skillDataBase["YAMATO_SKILL_3"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // ”­“®Žž‚ÌŒø‰Ê

	},
		[](CCharacter* inusedCharacter)
	{ // HitŽž‚ÌŒø‰Ê

	} };
	m_skillDataBase["YAMATO_SKILL_4"] = { 20,1,
		[](CCharacter* inusedCharacter)
	{ // ”­“®Žž‚ÌŒø‰Ê

	},
		[](CCharacter* inusedCharacter)
	{ // HitŽž‚ÌŒø‰Ê

	} };
}
