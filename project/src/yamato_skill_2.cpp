//**************************************************************
//
// スキル(ブリンク)
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
#include "yamato_skill_2.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CYamatoSkill_2::CYamatoSkill_2()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CYamatoSkill_2::~CYamatoSkill_2()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CYamatoSkill_2::InitAbility()
{
	// データベースから情報を取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Time = 0;
		m_Duration = 30;
		// 当たり判定を取得
		m_collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f);
		m_collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_collision);

		// カメラの方向に合わせる
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		D3DXVec3Normalize(&vecNor, &vecNor);
		vecNor *= 30.0f;			//移動させたい値を入れる
		m_apChara->SetMove(vecNor);
		// プレイヤーの操作を無効化
		m_apChara->SetControlLock(true);
		// 重力・慣性を切る
		m_apChara->SetInertiaMoveLock(true);
	}
}

//--------------------------------------------------------------
// 持続する効果
//--------------------------------------------------------------
void CYamatoSkill_2::AllWayAbility()
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
void CYamatoSkill_2::UninitAbility()
{
	//	プレイヤーの操作が無効化されていたら有効化
	m_apChara->SetControlLock(false);
	//	プレイヤーの移動が無効化されていたら有効化
	m_apChara->SetMoveLock(false);
	//	慣性・重力が無効化されていたら有効化
	m_apChara->SetInertiaMoveLock(false);
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CYamatoSkill_2::HitAbility(CCharacter * Target)
{
	
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CYamatoSkill_2 *CYamatoSkill_2::Create(CCharacter* chara)
{
	// 生成処理
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CYamatoSkill_2* pSkill = new CYamatoSkill_2;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_2";
	pSkill->Init();

	return pSkill;
}