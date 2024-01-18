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
#include "gyuuki_stamp_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CGyuukiStampSkill::CGyuukiStampSkill()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CGyuukiStampSkill::~CGyuukiStampSkill()
{

}

//--------------------------------------------------------------
// スキルが始まるとき
//--------------------------------------------------------------
void CGyuukiStampSkill::InitAbility()
{
	m_Duration = 20;
	m_time = 0;

	int random = IntRandom(2,2);
	D3DXVECTOR3 separate;
	switch (random)
	{
	case 0:
		separate = D3DXVECTOR3(195.0f, 0.0f, 195.0f);
		break;
	case 1:
		separate = D3DXVECTOR3(-195.0f, 0.0f, 195.0f);
		break;
	case 2:
		separate = D3DXVECTOR3(195.0f, 0.0f, -195.0f);
		break;
	case 3:
		separate = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		break;
	case 4:
		separate = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
		break;
	case 5:
		break;
		separate = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	default:
		break;
	}

	// 当たり判定を取得
	D3DXVECTOR3 pos = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), separate);
	CCollision* collision = CCollisionBox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	m_apChara->SetMoveLock(true);
	m_apChara->SetToFaceRot(true);
}

//--------------------------------------------------------------
// 常に
//--------------------------------------------------------------
void CGyuukiStampSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// スキルが終了時
//--------------------------------------------------------------
void CGyuukiStampSkill::UninitAbility()
{
	m_apChara->SetMoveLock(false);
	m_apChara->SetInertiaMoveLock(false);
}

//--------------------------------------------------------------
// スキルが当たった時の効果
//--------------------------------------------------------------
void CGyuukiStampSkill::HitAbility(CCharacter * Target)
{
	// todo プレイヤーの最終的な攻撃力を取得する
	m_apChara->DealDamage(Target, 1.5f);
}

//--------------------------------------------------------------
// スキル生成処理
//--------------------------------------------------------------
CGyuukiStampSkill *CGyuukiStampSkill::Create(CCharacter* chara)
{
	CGyuukiStampSkill* pSkill = new CGyuukiStampSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_1";
	pSkill->Init();

	return pSkill;
}