//**************************************************************
//
// スケルトンの攻撃
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "skill_back_step.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkillBackStep::CSkillBackStep()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkillBackStep::~CSkillBackStep()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CSkillBackStep::InitAbility()
{
	m_Duration = 5;

	m_apChara->SetToFaceRot(false);

	D3DXVECTOR3 move = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, -20.0f));

	m_apChara->SetInertiaMoveLock(true);
	m_apChara->SetMoveLock(true);
	m_apChara->SetMove(move);
}

//--------------------------------------------------------------
// 常に
//--------------------------------------------------------------
void CSkillBackStep::AllWayAbility()
{
}

//--------------------------------------------------------------
// スキルが終了時
//--------------------------------------------------------------
void CSkillBackStep::UninitAbility()
{
	m_apChara->SetInertiaMoveLock(false);
	m_apChara->SetMoveLock(false);
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CSkillBackStep::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CSkillBackStep *CSkillBackStep::Create(CCharacter* chara)
{
	CSkillBackStep* pSkill = new CSkillBackStep;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}