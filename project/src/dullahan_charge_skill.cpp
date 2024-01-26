//**************************************************************
//
// �f�����n��(�ːi)
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "dullahan_charge_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CDullahanChargeSkill::CDullahanChargeSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CDullahanChargeSkill::~CDullahanChargeSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CDullahanChargeSkill::InitAbility()
{
	m_Duration = 400;

	// �_����̌���
	CApplication::GetInstance()->GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});

	// �����蔻����擾
	CCollision* collision = CCollisionBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(20.0f, 20.0f, 50.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CDullahanChargeSkill::AllWayAbility()
{
	// "2024/01/09" �z�[�~���O����������ɘa������

	if (m_collision.size() > 0)
	{
		m_collision.front()->SetRot(m_apChara->GetRot());
	}

	if (m_apChara->GetSpeed()->GetBuff() <= 5.0f)
	{
		m_apChara->GetSpeed()->AddBuffEffect(0.025f);
	}

	// �ǉ��I������
	if (m_collision.size() <= 0)
	{
		m_Duration = 0;
	}
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CDullahanChargeSkill::UninitAbility()
{
	m_apChara->GetSpeed()->ResetBuffEffect();
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CDullahanChargeSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 0.55f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CDullahanChargeSkill *CDullahanChargeSkill::Create(CCharacter* chara)
{
	CDullahanChargeSkill* pSkill = new CDullahanChargeSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}