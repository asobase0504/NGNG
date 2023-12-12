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
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	// 初期化
	m_Duration = pSkillData->GetDuration(m_Name);
	m_Interval = pSkillData->GetInterval(m_Name);
	m_Invincible = 0;
	m_isSkill = false;
	InitAbility();

	m_relation = m_apChara->GetRelation();
	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CSkillEntity::Uninit()
{
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

		if (m_Interval > 0)
		{// 無敵状態にする
		}

		// インターバル0以下で当たり判定がなかったら当たり判定を生成する
		if (m_Interval <= 0 && m_Collision == nullptr)
		{
			m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize(m_Name).x);
			m_Collision->SetParent(&m_apChara->GetPos());
			SetEndChildren(m_Collision);
		}

		if (m_Collision == nullptr)
		{
			return;
		}

		// 自分とは違う関係を持ってるキャラクターに行なう
		CMap::GetMap()->DoDifferentRelation(m_relation, [this, &collision, &pSkillData](CCharacter* inChara)
		{
			if (inChara->GetIsAtkCollision())
			{
				return;
			}

			// 当たり判定
			bool hit = m_Collision->ToSphere((CCollisionSphere*)inChara->GetCollision());
			if (hit && m_Interval <= 0)
			{// ダメージの判定
				HitAbility(inChara);
				collision = true;
			}
		});

		if (collision && m_Collision != nullptr)
		{// 敵に当たっていたら
			m_Interval = pSkillData->GetInterval(m_Name);
			m_Collision->Uninit();
			m_Collision = nullptr;
		}
	}
	else if (m_Duration <= 0)
	{// 効果時間が0以下になったら消す
		Uninit();
	}

#ifdef _DEBUG
	CDebugProc::Print("スキルの効果時間 : %f\n", m_Duration);
	CDebugProc::Print("当たり判定のインターバル: %f\n", m_Interval);
#endif // _DEBUG
}