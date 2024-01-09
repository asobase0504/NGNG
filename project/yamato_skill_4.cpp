//**************************************************************
//
// �X�L��(�}�[�Z�i���[��R)
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
CYamatoSkill_4::CYamatoSkill_4()
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
		m_Duration = 120;
		m_Time = 0;
		// �����蔻����擾
		m_collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 40);
		m_collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_collision);

		// �J�����̕����ɍ��킹��
		CCameraGame *camera = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera();
		D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
		D3DXVec3Normalize(&vecNor, &vecNor);
		vecNor *= 25.0f;			//�ړ����������l������
		m_apChara->SetMove(vecNor);
		// �v���C���[�̑���𖳌���
		m_apChara->SetControlLock(true);
		// �d�́E������؂�
		m_apChara->SetInertiaMoveLock(true);
		// �`���؂�
		m_apChara->SetDisplay(false);
	}
}

//--------------------------------------------------------------
// �����������
//--------------------------------------------------------------
void CYamatoSkill_4::AllWayAbility()
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
void CYamatoSkill_4::UninitAbility()
{
	m_apChara->SetDisplay(true);

	// ����̗L����
	m_apChara->SetControlLock(false);
	// �ړ��̗L����
	m_apChara->SetMoveLock(false);
	// �����E�d�̗͂L����
	m_apChara->SetInertiaMoveLock(false);
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