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
#include "application.h"
#include "sound.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_3::CYamatoSkill_3()
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
	m_Duration = 120;

	// �����蔻����擾
	CCollision* collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f);
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	// �v���C���[�̑���𖳌���
	m_apChara->SetControlLock(true);
	m_apChara->SetMoveXZ(0.0f, 0.0f);

	// �J�����̕����ɍ��킹�ēˌ�
	CCamera *camera = CApplication::GetInstance()->GetModeClass()->GetCamera();
	D3DXVECTOR3 vecNor = camera->GetPosR() - camera->GetPos();
	D3DXVec3Normalize(&vecNor, &vecNor);
	vecNor *= 15.0f;			//�ړ����������l������
	m_apChara->SetMoveXZ(vecNor.x, vecNor.z);

	m_time = 0;

	// sound
	CApplication::GetInstance()->GetSound()->Play(CSound::LEVEL_SE_SKILL_3);
}

//--------------------------------------------------------------
// �펞
//--------------------------------------------------------------
void CYamatoSkill_3::AllWayAbility()
{
	m_time++;

	/* "2024/01/09" �����U�����x�𔽉f�������� */
	if (m_time % 20 == 0 && m_collision.empty())
	{
		// �����蔻����擾
		CCollision* collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f);
		m_collision.push_back(collision);
		collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(collision);
	}
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CYamatoSkill_3::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target,1.0f);
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CYamatoSkill_3::UninitAbility()
{
	m_apChara->SetControlLock(false);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CYamatoSkill_3 *CYamatoSkill_3::Create(CCharacter* chara)
{
	CYamatoSkill_3* pSkill = new CYamatoSkill_3;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_3";
	pSkill->Init();

	return pSkill;
}