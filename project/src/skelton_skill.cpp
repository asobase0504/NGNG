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
#include "skelton_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkeltonSkill::CSkeltonSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkeltonSkill::~CSkeltonSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CSkeltonSkill::InitAbility()
{
	m_Duration = 30;

	// �����蔻����擾
	D3DXVECTOR3 posDiff = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	CCollision* collision = CCollisionBox::Create(posDiff, m_apChara->GetRot(), D3DXVECTOR3(20.0f, 20.0f, 50.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	m_apChara->SetInertiaMoveLock(true);
	m_apChara->SetMoveLock(true);
	m_apChara->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CSkeltonSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CSkeltonSkill::UninitAbility()
{
	m_apChara->SetInertiaMoveLock(false);
	m_apChara->SetMoveLock(false);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CSkeltonSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CSkeltonSkill *CSkeltonSkill::Create(CCharacter* chara)
{
	CSkeltonSkill* pSkill = new CSkeltonSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}