//**************************************************************
//
// スキル(回転切り)
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
#include "yamato_skill_4.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CYamatoSkill_4::CYamatoSkill_4(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CYamatoSkill_4::~CYamatoSkill_4()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CYamatoSkill_4::InitAbility()
{
	// データベースから情報を取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("YAMATO_SKILL_4");
		m_Invincible = pSkillData->GetInvincible("YAMATO_SKILL_4");
		// 当たり判定を取得
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("YAMATO_SKILL_4").x);
		m_Collision->SetParent(&m_apChara->GetPos());

		// カメラの方向に合わせる
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		vecNor *= 1.5f;			// 移動させたい値を入れる
		m_apChara->SetPos(m_apChara->GetPos() + vecNor);
	}
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CYamatoSkill_4::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	Target->TakeDamage(50, Target);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CYamatoSkill_4 *CYamatoSkill_4::Create(CCharacter* chara)
{
	// 生成処理
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CYamatoSkill_4* pSkill = new CYamatoSkill_4;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_4";
	pSkill->Init();

	return pSkill;
}