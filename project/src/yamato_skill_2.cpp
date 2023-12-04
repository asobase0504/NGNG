//**************************************************************
//
// �X�L��(�u�����N)
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
#include "yamato_skill_2.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_2::CYamatoSkill_2(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_2::~CYamatoSkill_2()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CYamatoSkill_2::InitAbility()
{
	// �f�[�^�x�[�X��������擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("YAMATO_SKILL_2");
		// �����蔻����擾
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("YAMATO_SKILL_2").x);
		m_Collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_Collision);

		// �J�����̕����ɍ��킹��
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		vecNor *= 2.0f;			//�ړ����������l������
		m_apChara->SetPos(m_apChara->GetPos() + vecNor);
	}
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CYamatoSkill_2::HitAbility(CCharacter * Target)
{
	
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CYamatoSkill_2 *CYamatoSkill_2::Create(CCharacter* chara)
{
	// ��������
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CYamatoSkill_2* pSkill = new CYamatoSkill_2;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_2";
	pSkill->Init();

	return pSkill;
}