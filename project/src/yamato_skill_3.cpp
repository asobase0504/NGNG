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
#include "yamato_skill_3.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"
#include "application.h"
#include "sound.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CYamatoSkill_3::CYamatoSkill_3()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CYamatoSkill_3::~CYamatoSkill_3()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CYamatoSkill_3::InitAbility()
{
	m_Duration = 120;

	// 当たり判定を取得
	CCollision* collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f);
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	// プレイヤーの操作を無効化
	m_apChara->SetControlLock(true);
	m_apChara->SetMoveXZ(0.0f, 0.0f);

	// カメラの方向に合わせて突撃
	CCamera *camera = CApplication::GetInstance()->GetModeClass()->GetCamera();
	D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
	D3DXVec3Normalize(&vecNor, &vecNor);
	vecNor *= 15.0f;			//移動させたい値を入れる
	m_apChara->SetMoveXZ(vecNor.x, vecNor.z);

	m_time = 0;

	// sound
	CApplication::GetInstance()->GetSound()->Play(CSound::LEVEL_SE_SKILL_3);
}

//--------------------------------------------------------------
// 常時
//--------------------------------------------------------------
void CYamatoSkill_3::AllWayAbility()
{
	m_time++;

	/* "2024/01/09" ここ攻撃速度を反映させたい */
	if (m_time % 20 == 0 && m_collision.empty())
	{
		// 当たり判定を取得
		CCollision* collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f);
		m_collision.push_back(collision);
		collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(collision);
	}
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CYamatoSkill_3::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target,1.0f);
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CYamatoSkill_3::UninitAbility()
{
	m_apChara->SetControlLock(false);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CYamatoSkill_3 *CYamatoSkill_3::Create(CCharacter* chara)
{
	CYamatoSkill_3* pSkill = new CYamatoSkill_3;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_3";
	pSkill->Init();

	return pSkill;
}