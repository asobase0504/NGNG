//**************************************************************
//
// スキル
// Author : 髙野馨將
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
// コンストラクタ
//--------------------------------------------------------------
CSkill::CSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkill::~CSkill()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CSkill::Init()
{
	// 初期化
	m_CT = 0;

	m_stockMax = CSkillDataBase::GetInstance()->GetStack(m_Name);
	m_stock = m_stockMax;

	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CSkill::Update()
{
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_CT > 0 && m_stock != m_stockMax)
	{// クールタイムがあれば減少させる
		m_CT--;
	}

	if (m_CT <= 0 && m_stock < m_stockMax)
	{
		m_stock++;
		m_CT = pSkillData->GetCT(m_Name);
	}

#ifdef _DEBUG
	CDebugProc::Print("%sのクールタイム : %d\n", m_Name.c_str(),m_CT);
#endif // _DEBUG
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CSkill *CSkill::Create()
{
	// 生成処理
	CSkill* pSkill = new CSkill;
	pSkill->Init();

	return pSkill;
}

//--------------------------------------------------------------
// スキル
//--------------------------------------------------------------
bool CSkill::Use()
{
	if (m_stock <= 0)
	{
		return false;
	}

	// クールタイムがなければ当たり判定を生成する

	m_stock--;

	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	CSkillEntity* entity = pSkillData->GetAbility(m_Name)(m_apChara);

	// 親子関係の構築
	SetEndChildren(entity);

	// クールタイムの設定
	m_atkSpd = m_apChara->GetAtkSpd()->GetCurrent();
	m_CT = pSkillData->GetCT(m_Name);

	return true;
}

//--------------------------------------------------------------
// スキルの設定
//--------------------------------------------------------------
void CSkill::SetSkill(std::string tag, CCharacter *chara)
{
	// 生成処理
	m_Name = tag;
	m_apChara = chara;
	m_stockMax = CSkillDataBase::GetInstance()->GetStack(m_Name);
	m_stock = m_stockMax;
}