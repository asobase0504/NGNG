//**************************************************************
//
// �X�L��(��]�؂�)
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
#include "yamato_skill_4.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_4::CYamatoSkill_4(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_4::~CYamatoSkill_4()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CYamatoSkill_4::InitAbility()
{
	// �f�[�^�x�[�X��������擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("YAMATO_SKILL_4");
		m_Invincible = pSkillData->GetInvincible("YAMATO_SKILL_4");
		// �����蔻����擾
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("YAMATO_SKILL_4").x);
		m_Collision->SetParent(&m_apChara->GetPos());

		// �J�����̕����ɍ��킹��
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		vecNor *= 1.5f;			// �ړ����������l������
		m_apChara->SetPos(m_apChara->GetPos() + vecNor);
	}
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CYamatoSkill_4::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	Target->TakeDamage(50, Target);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CYamatoSkill_4 *CYamatoSkill_4::Create(CCharacter* chara)
{
	// ��������
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CYamatoSkill_4* pSkill = new CYamatoSkill_4;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_4";
	pSkill->Init();

	return pSkill;
}