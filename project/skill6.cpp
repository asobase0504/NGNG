//**************************************************************
//
// スキル(カウンター)
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
#include "skill6.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkill6::CSkill6(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkill6::~CSkill6()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CSkill6::InitAbility()
{
	// データベースから情報を取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("SKILL_6");
	}
}

//--------------------------------------------------------------
// 持続する効果
//--------------------------------------------------------------
void CSkill6::AllWayAbility()
{
	// データベースから情報を取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_Duration > 0)
	{// 効果中に攻撃されたらカウンターする
		// 当たり判定を取得
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("SKILL_6").x);
		m_Collision->SetParent(&m_apChara->GetPos());
	}
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CSkill6::UninitAbility()
{
	if (m_apChara->GetControlLock())
	{//	プレイヤーの操作が無効化されていたら有効化
		m_apChara->SetControlLock(false);
	}
	if (m_apChara->GetMoveLock())
	{//	プレイヤーの移動が無効化されていたら有効化
		m_apChara->SetMoveLock(false);
	}
	if (m_apChara->GetInertiaMoveLock())
	{//	慣性・重力が無効化されていたら有効化
		m_apChara->SetInertiaMoveLock(false);
	}
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CSkill6::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	Target->TakeDamage(50, Target);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CSkill6 *CSkill6::Create(CCharacter* chara)
{
	// 生成処理
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CSkill6* pSkill = new CSkill6;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "SKILL_6"; 
	pSkill->Init();

	return pSkill;
}