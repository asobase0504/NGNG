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
#include "gasyadokuro_attack_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CGasyadokuroAttackSkill::CGasyadokuroAttackSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CGasyadokuroAttackSkill::~CGasyadokuroAttackSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::InitAbility()
{
	m_Duration = 10;

	m_apChara->SetMoveLock(true);
	m_apChara->SetInertiaMoveLock(true);

	// 当たり判定を取得
	CCollision* collision = CCollisionBox::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 150.0f)), m_apChara->GetRot(), D3DXVECTOR3(40.0f, 20.0f, 150.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	m_time = 0;
}

//--------------------------------------------------------------
// 常に
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// スキルが終了時
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::UninitAbility()
{
	m_apChara->SetMoveLock(false);
	m_apChara->SetInertiaMoveLock(false);
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 0.5f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CGasyadokuroAttackSkill *CGasyadokuroAttackSkill::Create(CCharacter* chara)
{
	CGasyadokuroAttackSkill* pSkill = new CGasyadokuroAttackSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();

	return pSkill;
}