//**************************************************************
//
// ぬりかべ
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "nurikabe_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CNurikabeSkill::CNurikabeSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CNurikabeSkill::~CNurikabeSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CNurikabeSkill::InitAbility()
{
	m_Duration = 30;

	// 狙う先の決定
	CMap::GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});

	// 当たり判定を取得
	CCollision* collision = CCollisionBox::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f)), m_apChara->GetRot(), D3DXVECTOR3(20.0f, 20.0f, 50.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	m_apChara->SetInertiaMoveLock(true);
	m_apChara->SetMoveLock(true);
	m_apChara->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//--------------------------------------------------------------
// 常に
//--------------------------------------------------------------
void CNurikabeSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// スキルが終了時
//--------------------------------------------------------------
void CNurikabeSkill::UninitAbility()
{
	m_apChara->SetInertiaMoveLock(false);
	m_apChara->SetMoveLock(false);
	m_apChara->GetSpeed()->ResetBuffEffect();
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CNurikabeSkill::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CNurikabeSkill *CNurikabeSkill::Create(CCharacter* chara)
{
	CNurikabeSkill* pSkill = new CNurikabeSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}