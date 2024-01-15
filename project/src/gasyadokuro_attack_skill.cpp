//**************************************************************
//
// �X�L��(�ʏ�U��)
// Author : ����]��
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "gasyadokuro_attack_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CGasyadokuroAttackSkill::CGasyadokuroAttackSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CGasyadokuroAttackSkill::~CGasyadokuroAttackSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::InitAbility()
{
	m_Duration = 10;

	m_apChara->SetMoveLock(true);
	m_apChara->SetInertiaMoveLock(true);

	// �����蔻����擾
	CCollision* collision = CCollisionBox::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 150.0f)), m_apChara->GetRot(), D3DXVECTOR3(40.0f, 20.0f, 150.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	m_time = 0;
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::UninitAbility()
{
	m_apChara->SetMoveLock(false);
	m_apChara->SetInertiaMoveLock(false);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CGasyadokuroAttackSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 0.5f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CGasyadokuroAttackSkill *CGasyadokuroAttackSkill::Create(CCharacter* chara)
{
	CGasyadokuroAttackSkill* pSkill = new CGasyadokuroAttackSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();

	return pSkill;
}