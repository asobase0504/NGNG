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
	// 初期化
	m_Duration = 1;
	m_Interval = 0;
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
		// スキル使用中にする
		m_isSkill = true;

		// 敵に当たっているか
		bool collision = false;

		// 効果時間の減少
		m_Duration--;
		m_Interval--;

		if (m_Collision == nullptr)
		{
			return;
		}
		// インターバル0以下で当たり判定がなかったら当たり判定を生成する
		if (m_Interval <= 0 && m_Collision == nullptr)
		{
			m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize(m_Name).x);
			m_Collision->SetParent(&m_apChara->GetPos());
		}

		// 自分とは違う関係を持ってるキャラクターに行なう
		CMap::GetMap()->DoDifferentRelation(m_relation, [this, &collision,&pSkillData](CCharacter* inChara)
		{
			// 当たり判定
			bool hit = m_Collision->ToSphere((CCollisionSphere*)inChara->GetCollision());
			if (hit && m_Interval <= 0.0f)
			{// ダメージの判定
				HitAbility(inChara);
				collision = true;
				m_Interval = pSkillData->GetInterval(m_Name);			
			}
		});

		if (collision)
		{// 敵に当たっていたら
			m_Collision->Uninit();
			m_Collision = nullptr;
		}
	}
	else if(m_Duration <= 0)
	{// 効果時間が0以下になったら消す
		Uninit();
	}

#ifdef _DEBUG
	CDebugProc::Print("Duration : %f\n", m_Duration);
#endif // _DEBUG
}