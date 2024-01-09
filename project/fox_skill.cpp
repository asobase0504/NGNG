//**************************************************************
//
// �X�L��(�ʏ�U��)
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "fox_skill.h"

#include "skill.h"
#include "skill_data_base.h"
#include "skill_entity.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "collision_sphere.h"
#include "utility.h"

#include "object_polygon3d.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CFoxSkill::CFoxSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CFoxSkill::~CFoxSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CFoxSkill::InitAbility()
{
	m_effectCnt = 0;
	m_apChara->SetToFaceRot(false);

	m_effectRot = m_apChara->GetRot().y - D3DX_PI * 0.45f;
	m_effectPos = m_apChara->GetPos();
	m_effectPos.y += 25.0f;

	m_Duration = 30;
	// �����蔻����擾
	m_collision = CCollisionSphere::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f)), 30);
	m_collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(m_collision);
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CFoxSkill::AllWayAbility()
{
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	m_effectRot += (D3DX_PI * 0.45f * 2.0f) / (30 - 5);
	m_effectCnt++;
	if (m_effectCnt >= 1 && m_Duration >= 5)
	{
		m_effectCnt = 0;

		float randomY = m_effectPos.y + FloatRandom(10.0f, -10.0f);

		D3DXVECTOR3 targetPos = CalculatePerimeterPos(D3DXVECTOR3(m_effectPos.x, randomY, m_effectPos.z), D3DXVECTOR3(0.0f, m_effectRot, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 55.0f));

		CObjectPolygon3D* effect = CObjectPolygon3D::Create();
		effect->SetPos(targetPos);
		effect->SetRot(D3DXVECTOR3(0.0f, m_effectRot, 0.0f));
		effect->SetSize(D3DXVECTOR3(20.0f, 1.0f, 0.0f));
		effect->SetIsCulling(true);
		effect->SetTexture("LINE");
		SetEndChildren(effect);
	}
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CFoxSkill::UninitAbility()
{
	m_apChara->SetToFaceRot(true);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CFoxSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 1.5f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CFoxSkill *CFoxSkill::Create(CCharacter* chara)
{
	CFoxSkill* pSkill = new CFoxSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "FOX_SKILL";
	pSkill->Init();

	return pSkill;
}