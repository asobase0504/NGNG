//**************************************************************
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
CSkillEntity::CSkillEntity(int nPriority)
{
	m_collision.clear();
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
	AllWayAbility();

	if (m_Duration > 0)
	{
		// スキル使用中にする
		m_isSkill = true;

		// 効果時間の減少
		m_Duration--;

		// 当たり判定
		Collision();
	}
	else if(m_Duration <= 0)
	{// 効果時間が0以下になったら

		UninitAbility();

		for (CCollision* collision : m_collision)
		{// 当たり判定が残っていたら
			collision->Uninit();
		}
		m_collision.clear();
		Uninit();
	}
}

//--------------------------------------------------------------
// 当たり判定
//--------------------------------------------------------------
void CSkillEntity::Collision()
{
	if (m_collision.size() <= 0)
	{
		return;
	}

	// 敵に当たっているか
	bool isHit = false;
	std::list<CCollision*> hitIndex;

	// 自分とは違う関係を持ってるキャラクターに当たり判定を行なう
	CMap::GetMap()->DoDifferentRelation(m_relation, [this, &isHit, &hitIndex](CCharacter* inChara)
	{
		// 攻撃を受ける状態か否か
		if (inChara->GetIsAtkCollision())
		{
			return;
		}

		// 当たり判定
		for (CCollision* collision : m_collision)
		{
			if (collision->ToCylinder(inChara->GetCollision()))
			{
				this->HitAbility(inChara);
				hitIndex.push_back(collision);
				isHit = true;
				break;
			}
		}
	});

	if (isHit && m_collision.size() > 0)
	{// 敵に当たっていたら
		hitIndex.unique();

		for (CCollision* index : hitIndex)
		{
			index->Uninit();
			m_collision.remove(index);
		}
	}
}
