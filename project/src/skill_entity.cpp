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

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkillEntity::CSkillEntity(int nPriority)
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
	InitAbility();

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CSkillEntity::Uninit(void)
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
void CSkillEntity::Update(void)
{
	// スキルデータのインスタンスを取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_Duration > 0)
	{
		bool collision = false;

		// 効果時間の減少
		m_Duration--;

		// 当たり判定
		std::vector<CEnemy*> Enemy = CEnemyManager::GetInstance()->GetEnemy();
		// エネミーの数を取得
		int EnemyCount = Enemy.size();

		for (int nCnt = 0; nCnt < EnemyCount; nCnt++)
		{// 攻撃範囲に敵がいるか判定する
			bool a = m_Collision->ToSphere((CCollisionSphere*)Enemy[nCnt]->GetCollision());
			if (a)
			{// ダメージの判定
				HitAbility(Enemy[nCnt]);
				collision = true;
			}
		}

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