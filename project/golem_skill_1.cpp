//**************************************************************
//
// �X�L��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "golem_skill_1.h"
#include "collision_sphere.h"

// �v���C���[
#include "player_manager.h"
#include "player.h"

#include "road.h"
#include "abnormal.h"
#include "bullet.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CGolemSkill_1::CGolemSkill_1() :
	m_road(nullptr),
	m_bullet(nullptr)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CGolemSkill_1::~CGolemSkill_1()
{
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CGolemSkill_1::Uninit()
{
	CSkillEntity::Uninit();

	if (m_road != nullptr)
	{
		m_road->Uninit();
		m_road = nullptr;
	}
}

//--------------------------------------------------------------
// �쐬
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
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CGolemSkill_1::InitAbility()
{
	m_aimCharacter = CPlayerManager::GetInstance()->GetPlayer();

	m_road = CRoad::Create(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	m_road->SetShooter(m_apChara);
	m_road->SetTarget(m_aimCharacter);
	m_road->SetUse(true);

	m_chargeTime = 0;
	m_isCharge = true;
}

//--------------------------------------------------------------
// ��ɍX�V����
//--------------------------------------------------------------
void CGolemSkill_1::AllWayAbility()
{
	m_chargeTime++;
	if (m_isCharge && m_chargeTime >= 180)
	{
		m_isCharge = false;

		D3DXVECTOR3 pos = m_apChara->GetPos();
		D3DXVECTOR3 move = m_aimCharacter->GetPos() - pos;
		m_bullet = CBullet::Create(pos, move * 0.01f, 10.0f, m_apChara->GetAbnormalAttack());

		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f);
		m_Collision->SetParent(&m_bullet->GetPos());
	}
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CGolemSkill_1::HitAbility(CCharacter * Target)
{
	if (m_bullet != nullptr)
	{
		m_bullet->Uninit();
		m_bullet = nullptr;
	}

	CAbnormal::ABNORMAL_FUNC abnormalFunc = CAbnormalDataBase::GetInstance()->GetItemData(CAbnormalDataBase::ABNORMAL_FIRE)->GetWhenAddFunc();
	abnormalFunc(Target, CAbnormalDataBase::ABNORMAL_FIRE);
	Uninit();
}