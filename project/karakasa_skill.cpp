//**************************************************************
//
// スキル(通常攻撃)
// Author : 髙野馨將
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "karakasa_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CKarakasaSkill::CKarakasaSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CKarakasaSkill::~CKarakasaSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CKarakasaSkill::InitAbility()
{
	m_Duration = 400;

	// 狙う先の決定
	CMap::GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});

	m_apChara->SetMoveY(15.0f);
	m_apChara->SetMoveLock(true);
	m_apChara->SetInertiaMoveLock(true);

	m_time = 0;
}

//--------------------------------------------------------------
// 常に
//--------------------------------------------------------------
void CKarakasaSkill::AllWayAbility()
{
	m_time++;

	if (m_time == 10)
	{
		D3DXVECTOR3 move = m_aimCharacter->GetPos() - m_apChara->GetPos();
		D3DXVec3Normalize(&move, &move);
		move *= 10.0f;
		m_apChara->SetMove(move);

		// 当たり判定を取得
		m_collision = CCollisionSphere::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f)), 30.0f);
		m_collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_collision);

		m_apChara->SetToFaceRot(false);
	}

	// 終了条件
	if (m_apChara->GetState() == CCharacter::STATE::GROUND)
	{
		m_Duration = 0;
	}
}

//--------------------------------------------------------------
// スキルが終了時
//--------------------------------------------------------------
void CKarakasaSkill::UninitAbility()
{
	m_apChara->SetMoveLock(false);
	m_apChara->SetInertiaMoveLock(false);
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CKarakasaSkill::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 1.5f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CKarakasaSkill *CKarakasaSkill::Create(CCharacter* chara)
{
	CKarakasaSkill* pSkill = new CKarakasaSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_1";
	pSkill->Init();

	return pSkill;
}