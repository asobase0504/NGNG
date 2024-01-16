//**************************************************************
//
// �ˌ��U��
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "skill_assault.h"
#include "skill.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkillAssault::CSkillAssault()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkillAssault::~CSkillAssault()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CSkillAssault::InitAbility()
{
	m_Duration = 15;

	m_apChara->SetToFaceRot(false);

	D3DXVECTOR3 move = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 20.0f));

	m_apChara->SetMoveLock(true);
	m_apChara->SetMove(move);

	// �ˌ��p�����蔻��
	CCollision* collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f);
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	m_hasAssault = true;
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CSkillAssault::AllWayAbility()
{
	if (m_hasAssault && m_Duration <= 5)
	{
		m_Duration = 0;
	}
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CSkillAssault::UninitAbility()
{
	m_apChara->SetMoveLock(false);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CSkillAssault::HitAbility(CCharacter * Target)
{
	if (m_hasAssault)
	{
		m_hasAssault = false;
		m_apChara->SetMove(D3DXVECTOR3(0.0f,0.0f,0.0f));

		// �U�艺�낵�p
		D3DXVECTOR3 pos = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 20.0f));
		CCollision* collision = CCollisionBox::Create(pos,m_apChara->GetRot(), D3DXVECTOR3(20.0f,20.0f,50.0f));
		m_collision.push_back(collision);
		collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(collision);
	}
	else
	{
		m_apChara->DealDamage(Target, 1.0f);
	}
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CSkillAssault *CSkillAssault::Create(CCharacter* chara)
{
	CSkillAssault* pSkill = new CSkillAssault;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}