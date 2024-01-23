//**************************************************************
//
// �X�P���g���̍U��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "skill_back_step.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkillBackStep::CSkillBackStep()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkillBackStep::~CSkillBackStep()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CSkillBackStep::InitAbility()
{
	m_Duration = 5;

	m_apChara->SetToFaceRot(false);

	D3DXVECTOR3 move = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, -20.0f));

	m_apChara->SetInertiaMoveLock(true);
	m_apChara->SetMoveLock(true);
	m_apChara->SetMove(move);
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CSkillBackStep::AllWayAbility()
{
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CSkillBackStep::UninitAbility()
{
	m_apChara->SetInertiaMoveLock(false);
	m_apChara->SetMoveLock(false);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CSkillBackStep::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CSkillBackStep *CSkillBackStep::Create(CCharacter* chara)
{
	CSkillBackStep* pSkill = new CSkillBackStep;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}