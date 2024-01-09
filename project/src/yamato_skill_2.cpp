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
CYamatoSkill_2::CYamatoSkill_2()
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
		m_Time = 0;
		m_Duration = 30;
		// �����蔻����擾
		m_collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f);
		m_collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_collision);

		// �J�����̕����ɍ��킹��
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		D3DXVec3Normalize(&vecNor, &vecNor);
		vecNor *= 30.0f;			//�ړ����������l������
		m_apChara->SetMove(vecNor);
		// �v���C���[�̑���𖳌���
		m_apChara->SetControlLock(true);
		// �d�́E������؂�
		m_apChara->SetInertiaMoveLock(true);
	}
}

//--------------------------------------------------------------
// �����������
//--------------------------------------------------------------
void CYamatoSkill_2::AllWayAbility()
{
	// ���Ԃ̉��Z
	m_Time++;
	if (m_Time > 20)
	{
		// �v���C���[�̈ʒu���Œ�
		m_apChara->SetMoveLock(true);
		m_apChara->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CYamatoSkill_2::UninitAbility()
{
	//	�v���C���[�̑��삪����������Ă�����L����
	m_apChara->SetControlLock(false);
	//	�v���C���[�̈ړ�������������Ă�����L����
	m_apChara->SetMoveLock(false);
	//	�����E�d�͂�����������Ă�����L����
	m_apChara->SetInertiaMoveLock(false);
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