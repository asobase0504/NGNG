//**************************************************************
//
// スキル(リキャスト)
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
#include "Skill5.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkill5::CSkill5(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkill5::~CSkill5()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CSkill5::InitAbility()
{
	// データベースから情報を取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("YAMATO_SKILL_5");
		// 当たり判定を取得
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("YAMATO_SKILL_5").x);
		m_Collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_Collision);
	}
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CSkill5::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 1.5f);

	if (Target->GetHp()->GetCurrent() <= 0)
	{// CTを0にする
		m_apChara->GetSkill()[5]->SetCT(0);
	}

}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CSkill5 *CSkill5::Create(CCharacter* chara)
{
	// 生成処理
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CSkill5* pSkill = new CSkill5;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_5";
	pSkill->Init();

	return pSkill;
}