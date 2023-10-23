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
#include "player_manager.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "collision_sphere.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkill::CSkill(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkill::~CSkill()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CSkill::Init()
{
	// 初期化
	m_CT = 0;

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CSkill::Uninit(void)
{
	// 破棄処理
	CTask::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CSkill::Update(void)
{
	// スキル1のインスタンスを取得
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();		// 発動時に生成

	if (m_apChara != nullptr && m_Name != "\0")
	{
		bool a = pSkillData->GetAbility(m_Name)(m_apChara);			// 当たったかどうか判定する

	}
	
	
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CSkill *CSkill::Create()
{
	// 生成処理
	CSkill* pSkill = new CSkill;
	pSkill->Init();

	return pSkill;
}

//--------------------------------------------------------------
// スキル当たり判定
//--------------------------------------------------------------
void CSkill::CollisionSkill()
{
	if (m_apChara != nullptr)
	{
		// 当たり判定
		m_Collision = CCollisionSphere::Create(m_apChara->GetPos(), CSkillDataBase::GetInstance()->GetSize("YAMATO_SKILL_1").x);
		std::vector<CEnemy*> Enemy = CEnemyManager::GetInstance()->GetEnemy();
		// エネミーの数を取得
		int EnemyCount = Enemy.size();

		for (int nCnt = 0; nCnt < EnemyCount; nCnt++)
		{// 攻撃範囲に敵がいるか判定する
			m_isCollision = false;
			m_isCollision = m_Collision->ToSphere((CCollisionSphere*)Enemy[nCnt]->GetCollision());
		}

		if (m_isCollision)
		{

		}
	}
}

//--------------------------------------------------------------
// スキルの設定
//--------------------------------------------------------------
void CSkill::SetSkill(std::string tag, CCharacter *chara)
{
	// 生成処理
	m_Name = tag;
	m_apChara = chara;
}