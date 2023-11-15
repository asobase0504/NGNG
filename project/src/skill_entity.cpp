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
	MapChangeRelese();
	m_Duration = 200;
	// 初期化
	InitAbility();

	m_relation = m_apChara->GetRelation();
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
		bool collision = false;

		// 効果時間の減少
		m_Duration--;

		if (m_Collision == nullptr)
		{
			return;
		}

		// 自分とは違う関係を持ってるキャラクターに行なう
		CMap::GetMap()->DoDifferentRelation(m_relation, [this, &collision](CCharacter* inChara)
		{
			// 当たり判定
			bool hit = m_Collision->ToSphere((CCollisionSphere*)inChara->GetCollision());
			if (hit)
			{// ダメージの判定
				HitAbility(inChara);
				collision = true;
			}
		});

		if (collision)
		{// 敵に当たっていたら
			Uninit();
		}
	}
	else if(m_Duration <= 0)
	{// 効果時間が0以下になったら消す
		Uninit();
	}

#ifdef _DEBUG
	CDebugProc::Print("Duration : %\n", m_Duration);
#endif // _DEBUG
}