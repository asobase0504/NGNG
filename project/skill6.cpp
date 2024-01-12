//**************************************************************
//
// �X�L��(�J�E���^�[)
// Author : ����]��
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
#include "skill6.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkill6::CSkill6(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkill6::~CSkill6()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CSkill6::InitAbility()
{
	// �f�[�^�x�[�X��������擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("SKILL_6");
	}
}

//--------------------------------------------------------------
// �����������
//--------------------------------------------------------------
void CSkill6::AllWayAbility()
{
	// �f�[�^�x�[�X��������擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_Duration > 0)
	{// ���ʒ��ɍU�����ꂽ��J�E���^�[����
		// �����蔻����擾
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("SKILL_6").x);
		m_Collision->SetParent(&m_apChara->GetPos());
	}
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CSkill6::UninitAbility()
{
	if (m_apChara->GetControlLock())
	{//	�v���C���[�̑��삪����������Ă�����L����
		m_apChara->SetControlLock(false);
	}
	if (m_apChara->GetMoveLock())
	{//	�v���C���[�̈ړ�������������Ă�����L����
		m_apChara->SetMoveLock(false);
	}
	if (m_apChara->GetInertiaMoveLock())
	{//	�����E�d�͂�����������Ă�����L����
		m_apChara->SetInertiaMoveLock(false);
	}
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CSkill6::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	Target->TakeDamage(50, Target);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CSkill6 *CSkill6::Create(CCharacter* chara)
{
	// ��������
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CSkill6* pSkill = new CSkill6;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "SKILL_6"; 
	pSkill->Init();

	return pSkill;
}