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
	m_Duration = 200;
	// 初期化
	InitAbility();

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CSkillEntity::Uninit()
{
	// 当たり判定の削除
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}

	// 破棄処理
	CTask::Uninit();
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
		m_Duration--;

		if (m_Collision == nullptr)
		{
			return;
		}

		// 当たり判定
		std::list<CCharacter*> charaList = CMap::GetMap()->GetCharacterList();

		for (CCharacter* chara : charaList)
		{// 攻撃範囲に敵がいるか判定する

			// 同じ関係性だったら攻撃を当てない。
			switch (m_apChara->GetRelation())
			{
			case CCharacter::ERelation::FRIENDLY:
				if (chara->GetRelation() == CCharacter::ERelation::FRIENDLY)
				{
					continue;
				}
				break;
			case CCharacter::ERelation::HOSTILE:
				if (chara->GetRelation() == CCharacter::ERelation::HOSTILE)
				{
					continue;
				}
				break;
			default:
				assert(false);
				break;
			}

			bool hit = m_Collision->ToSphere((CCollisionSphere*)chara->GetCollision());
			if (hit)
			{// ダメージの判定
				HitAbility(chara);
			}
		}
	}
	else
	{
		Uninit();
	}
}