//**************************************************************
//
// �X�L��(���L���X�g)
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
#include "Skill5.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkill5::CSkill5(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkill5::~CSkill5()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CSkill5::InitAbility()
{
	// �f�[�^�x�[�X��������擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("YAMATO_SKILL_5");
		// �����蔻����擾
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("YAMATO_SKILL_5").x);
		m_Collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_Collision);
	}
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CSkill5::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 1.5f);

	if (Target->GetHp()->GetCurrent() <= 0)
	{// CT��0�ɂ���
		m_apChara->GetSkill()[5]->SetCT(0);
	}

}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CSkill5 *CSkill5::Create(CCharacter* chara)
{
	// ��������
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CSkill5* pSkill = new CSkill5;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_5";
	pSkill->Init();

	return pSkill;
}