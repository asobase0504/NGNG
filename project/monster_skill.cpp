//**************************************************************
//
// �X�L��(�ʏ�U��)
// Author : ����]��
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "monster_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CMonsterSkill::CMonsterSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CMonsterSkill::~CMonsterSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CMonsterSkill::InitAbility()
{
	m_Duration = 400;

	// �_����̌���
	CMap::GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});

	// �����蔻����擾
	//m_collision = CCollisionSphere::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f)), 30.0f);
	m_collision = CCollisionBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(),D3DXVECTOR3(20.0f,20.0f,50.0f));
	m_collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(m_collision);
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CMonsterSkill::AllWayAbility()
{
	// "2024/01/09" �z�[�~���O����������ɘa������

	if (m_collision != nullptr)
	{
		m_collision->SetRot(m_apChara->GetRot());
	}

	if (m_apChara->GetSpeed()->GetBuff() <= 5.0f)
	{
		m_apChara->GetSpeed()->AddBuffEffect(0.025f);
	}

	// �ǉ��I������
	if (m_collision == nullptr)
	{
		m_Duration = 0;
	}
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CMonsterSkill::UninitAbility()
{
	m_apChara->GetSpeed()->ResetBuffEffect();
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CMonsterSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CMonsterSkill *CMonsterSkill::Create(CCharacter* chara)
{
	CMonsterSkill* pSkill = new CMonsterSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_1";
	pSkill->Init();

	return pSkill;
}