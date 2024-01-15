//**************************************************************
//
// �ʂ肩��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "nurikabe_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CNurikabeSkill::CNurikabeSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CNurikabeSkill::~CNurikabeSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CNurikabeSkill::InitAbility()
{
	m_Duration = 30;

	// �_����̌���
	CMap::GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});

	// �����蔻����擾
	CCollision* collision = CCollisionBox::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f)), m_apChara->GetRot(), D3DXVECTOR3(20.0f, 20.0f, 50.0f));
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
void CNurikabeSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CNurikabeSkill::UninitAbility()
{
	m_apChara->SetInertiaMoveLock(false);
	m_apChara->SetMoveLock(false);
	m_apChara->GetSpeed()->ResetBuffEffect();
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CNurikabeSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CNurikabeSkill *CNurikabeSkill::Create(CCharacter* chara)
{
	CNurikabeSkill* pSkill = new CNurikabeSkill;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}