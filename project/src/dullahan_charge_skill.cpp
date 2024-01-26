//**************************************************************
//
// デュラハン(突進)
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "dullahan_charge_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CDullahanChargeSkill::CDullahanChargeSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CDullahanChargeSkill::~CDullahanChargeSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CDullahanChargeSkill::InitAbility()
{
	m_Duration = 400;

	// 狙う先の決定
	CApplication::GetInstance()->GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});

	// 当たり判定を取得
	CCollision* collision = CCollisionBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(20.0f, 20.0f, 50.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);
}

//--------------------------------------------------------------
// 常に
//--------------------------------------------------------------
void CDullahanChargeSkill::AllWayAbility()
{
	// "2024/01/09" ホーミングが強いから緩和したい

	if (m_collision.size() > 0)
	{
		m_collision.front()->SetRot(m_apChara->GetRot());
	}

	if (m_apChara->GetSpeed()->GetBuff() <= 5.0f)
	{
		m_apChara->GetSpeed()->AddBuffEffect(0.025f);
	}

	// 追加終了条件
	if (m_collision.size() <= 0)
	{
		m_Duration = 0;
	}
}

//--------------------------------------------------------------
// スキルが終了時
//--------------------------------------------------------------
void CDullahanChargeSkill::UninitAbility()
{
	m_apChara->GetSpeed()->ResetBuffEffect();
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CDullahanChargeSkill::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 0.55f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CDullahanChargeSkill *CDullahanChargeSkill::Create(CCharacter* chara)
{
	CDullahanChargeSkill* pSkill = new CDullahanChargeSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}