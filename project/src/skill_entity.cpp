﻿//**************************************************************
//
// スキル
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
#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkillEntity::CSkillEntity(int nPriority) : 
	m_Collision(nullptr)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkillEntity::~CSkillEntity()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CSkillEntity::Init()
{
	// 初期化
	m_Duration = 0;
	m_Interval = 0;
	m_Invincible = 0;
	m_isSkill = false;

	InitAbility();

	m_relation = m_apChara->GetRelation();
	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CSkillEntity::Update()
{
	// スキルデータのインスタンスを取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	AllWayAbility();

	if (m_Duration > 0)
	{
		// スキル使用中にする
		m_isSkill = true;

		// 敵に当たっているか
		bool collision = false;

		// 効果時間の減少
		m_Duration--;
		// 次の当たり判定を出現させるまでの時間を減少
		m_Interval--;
		// 無敵時間の減少
		m_Invincible--;

		if (m_Invincible > 0)
		{// 無敵状態にする(プレイヤーが見えなくなり、ダメージを受けなくなる)
			m_apChara->SetDisplay(false);
		}
		else
		{// もとに戻す
			m_apChara->SetDisplay(true);
		}

		if (m_Collision == nullptr)
		{
			return;
		}

		// 自分とは違う関係を持ってるキャラクターに当たり判定を行なう
		CMap::GetMap()->DoDifferentRelation(m_relation, [this, &collision, &pSkillData](CCharacter* inChara)
		{
			// 攻撃を受ける状態か否か
			if (inChara->GetIsAtkCollision())
			{
				return;
			}

			// 当たり判定
			bool hit = m_Collision->ToCylinder(inChara->GetCollision());
			if (hit)
			{
				// 衝突処理
				this->HitAbility(inChara);
				collision = true;
			}
		});

		if (collision && m_Collision != nullptr)
		{// 敵に当たっていたら
			m_Collision->Uninit();
			m_Collision = nullptr;
		}
	}
	else if(m_Duration <= 0)
	{// 効果時間が0以下になったら

		UninitAbility();
		if (m_apChara->GetControlLock())
		{//	プレイヤーの操作が無効化されていたら有効化
			m_apChara->SetControlLock(false);
		}
		if (m_apChara->GetMoveLock())
		{//	プレイヤーの移動が無効化されていたら有効化
			m_apChara->SetMoveLock(false);
		}

		if (m_Collision != nullptr)
		{// 当たり判定が残っていたら
			m_Collision->Uninit();
			m_Collision = nullptr;
		}
		Uninit();
	}

#ifdef _DEBUG
	CDebugProc::Print("スキルの効果時間 : %f\n", m_Duration);
	CDebugProc::Print("当たり判定のインターバル: %f\n", m_Interval);
#endif // _DEBUG
}