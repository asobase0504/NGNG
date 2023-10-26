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
	// スキルデータのインスタンスを取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_CT > 0)
	{// クールタイムがあれば減少させる
		m_CT--;
	}

#ifdef _DEBUG
	CDebugProc::Print("スキルのクールタイム : %d\n", m_CT);
#endif // _DEBUG
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
void CSkill::CollisionSkill(std::string tag)
{
	// スキルデータのインスタンスを取得する
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_apChara != nullptr)
	{
		// 当たり判定
		m_Collision = CCollisionSphere::Create(m_apChara->GetPos(), pSkillData->GetSize(tag).x);
		std::vector<CEnemy*> Enemy = CEnemyManager::GetInstance()->GetEnemy();
		// エネミーの数を取得
		int EnemyCount = Enemy.size();

		for (int nCnt = 0; nCnt < EnemyCount; nCnt++)
		{// 攻撃範囲に敵がいるか判定する
			m_isCollision = false;
			m_isCollision = m_Collision->ToSphere((CCollisionSphere*)Enemy[nCnt]->GetCollision());

			if (m_isCollision)
			{// hit時に生成
				pSkillData->GetHitAbility(tag);
			}
		}
	}
}

//--------------------------------------------------------------
// スキル1
//--------------------------------------------------------------
void CSkill::Skill1()
{
	if (m_CT == 0)
	{// クールタイムがなければ当たり判定を生成する
		CollisionSkill("YAMATO_SKILL_1");
	}

	// クールタイムの設定
	m_CT = CSkillDataBase::GetInstance()->GetCT("YAMATO_SKILL_2");
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