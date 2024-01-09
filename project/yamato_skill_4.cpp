//**************************************************************
//
// スキル(マーセナリーのR)
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
CYamatoSkill_4::CYamatoSkill_4()
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
		m_Duration = 120;
		m_Time = 0;
		// 当たり判定を取得
		m_collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40);
		m_collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_collision);

		// カメラの方向に合わせる
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		D3DXVec3Normalize(&vecNor, &vecNor);
		vecNor *= 25.0f;			//移動させたい値を入れる
		m_apChara->SetMove(vecNor);
		// プレイヤーの操作を無効化
		m_apChara->SetControlLock(true);
		// 重力・慣性を切る
		m_apChara->SetInertiaMoveLock(true);
		// 描画を切る
		m_apChara->SetDisplay(false);
	}
}

//--------------------------------------------------------------
// 持続する効果
//--------------------------------------------------------------
void CYamatoSkill_4::AllWayAbility()
{
	// 時間の加算
	m_Time++;
	if (m_Time > 20)
	{
		// プレイヤーの位置を固定
		m_apChara->SetMoveLock(true);
		m_apChara->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CYamatoSkill_4::UninitAbility()
{
	m_apChara->SetDisplay(true);

	// 操作の有効化
	m_apChara->SetControlLock(false);
	// 移動の有効化
	m_apChara->SetMoveLock(false);
	// 慣性・重力の有効化
	m_apChara->SetInertiaMoveLock(false);
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