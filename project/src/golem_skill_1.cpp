//**************************************************************
//
// スキル
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "golem_skill_1.h"
#include "collision_sphere.h"

// プレイヤー
#include "player_manager.h"
#include "player.h"

#include "road.h"
#include "abnormal.h"
#include "bullet.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CGolemSkill_1::CGolemSkill_1() :
	m_bullet(nullptr)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CGolemSkill_1::~CGolemSkill_1()
{
}

//--------------------------------------------------------------
// 作成
//--------------------------------------------------------------
CGolemSkill_1 * CGolemSkill_1::Create(CCharacter * chara)
{
	CGolemSkill_1* pSkill = new CGolemSkill_1;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "GOLEM_SKILL_1";
	pSkill->Init();

	return pSkill;
}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CGolemSkill_1::InitAbility()
{
	m_Duration = 400;
	m_chargeTime = 0;
	m_isCharge = true;

	m_aimCharacter = nullptr;

	// 狙う先の決定
	CApplication::GetInstance()->GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});
}

//--------------------------------------------------------------
// 常に更新する
//--------------------------------------------------------------
void CGolemSkill_1::AllWayAbility()
{
	if (m_aimCharacter == nullptr)
	{
		return;
	}

	m_chargeTime++;
	if (m_isCharge && m_chargeTime >= 30)
	{
		m_isCharge = false;

		D3DXVECTOR3 pos = m_apChara->GetPos();
		D3DXVECTOR3 move = m_aimCharacter->GetPos() - pos;
		m_bullet = CBullet::Create(pos, move * 0.01f, 10.0f);
		SetEndChildren(m_bullet);

		// 当たり判定を取得
		CCollision* collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f);
		m_collision.push_back(collision);
		collision->SetParent(&m_bullet->GetPos());
		SetEndChildren(collision);
	}

	if (m_collision.size() <= 0 && !m_isCharge)
	{
		m_Duration = 0;
	}
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CGolemSkill_1::HitAbility(CCharacter * Target)
{
	m_apChara->DealDamage(Target, 0.25f);
	Uninit();
}
