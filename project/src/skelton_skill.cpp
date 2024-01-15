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
#include "skelton_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkeltonSkill::CSkeltonSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkeltonSkill::~CSkeltonSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CSkeltonSkill::InitAbility()
{
	m_Duration = 30;

	// 当たり判定を取得
	D3DXVECTOR3 posDiff = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	CCollision* collision = CCollisionBox::Create(posDiff, m_apChara->GetRot(), D3DXVECTOR3(20.0f, 20.0f, 50.0f));
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
void CSkeltonSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// スキルが終了時
//--------------------------------------------------------------
void CSkeltonSkill::UninitAbility()
{
	m_apChara->SetInertiaMoveLock(false);
	m_apChara->SetMoveLock(false);
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CSkeltonSkill::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CSkeltonSkill *CSkeltonSkill::Create(CCharacter* chara)
{
	CSkeltonSkill* pSkill = new CSkeltonSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}