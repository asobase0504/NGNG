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
#include "yamato_skill_3.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_3::CYamatoSkill_3(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_3::~CYamatoSkill_3()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CYamatoSkill_3::InitAbility()
{
	// �f�[�^�x�[�X��������擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("YAMATO_SKILL_3");
		// �����蔻����擾
		m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize("YAMATO_SKILL_3").x);
		m_Collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_Collision);

		// �J�����̕����ɍ��킹��
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		D3DXVec3Normalize(&vecNor, &vecNor);
		vecNor *= 15.0f;			//�ړ����������l������
		m_apChara->SetMoveXZ(vecNor.x, vecNor.z);
	}
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CYamatoSkill_3::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	Target->Damage(50, Target);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CYamatoSkill_3 *CYamatoSkill_3::Create(CCharacter* chara)
{
	// ��������
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CYamatoSkill_3* pSkill = new CYamatoSkill_3;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_3";
	pSkill->Init();

	return pSkill;
}