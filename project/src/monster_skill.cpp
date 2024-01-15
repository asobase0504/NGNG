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
#include "monster_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CMonsterSkill::CMonsterSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CMonsterSkill::~CMonsterSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CMonsterSkill::InitAbility()
{
	m_Duration = 400;

	// 狙う先の決定
	CMap::GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
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
void CMonsterSkill::AllWayAbility()
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
void CMonsterSkill::UninitAbility()
{
	m_apChara->GetSpeed()->ResetBuffEffect();
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CMonsterSkill::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CMonsterSkill *CMonsterSkill::Create(CCharacter* chara)
{
	CMonsterSkill* pSkill = new CMonsterSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}