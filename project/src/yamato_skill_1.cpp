//**************************************************************
//
// �X�L��(�ʏ�U��)
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
#include "yamato_skill_1.h"
#include "utility.h"

#include "object_polygon3d.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_1::CYamatoSkill_1(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CYamatoSkill_1::~CYamatoSkill_1()
{
	
}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CYamatoSkill_1::InitAbility()
{
	m_effectCnt = 0;
	m_apChara->SetToFaceRot(false);

	m_effectRot = m_apChara->GetRot().y - D3DX_PI * 0.45f;
	m_effectPos = m_apChara->GetPos();
	m_effectPos.y += 25.0f;

	// �f�[�^�x�[�X��������擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	if (m_apChara != nullptr)
	{
		m_Duration = pSkillData->GetDuration("YAMATO_SKILL_1");
		// �����蔻����擾
		m_Collision = CCollisionSphere::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f,0.0f,0.0f), m_apChara->GetRot(),D3DXVECTOR3(0.0f,0.0f,50.0f)), pSkillData->GetSize("YAMATO_SKILL_1").x);
		m_Collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(m_Collision);
	}
}

void CYamatoSkill_1::AllWayAbility()
{
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	m_effectRot += (D3DX_PI * 0.45f * 2.0f) / (pSkillData->GetDuration("YAMATO_SKILL_1") - 5);
	m_effectCnt++;
	if (m_effectCnt >= 1 && m_Duration >= 5)
	{
		m_effectCnt = 0;

		float randomY = m_effectPos.y + FloatRandom(10.0f, -10.0f);

		D3DXVECTOR3 targetPos = CalculatePerimeterPos(D3DXVECTOR3(m_effectPos.x, randomY, m_effectPos.z), D3DXVECTOR3(0.0f, m_effectRot, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 55.0f));

		CObjectPolygon3D* effect = CObjectPolygon3D::Create();
		effect->SetPos(targetPos);
		effect->SetRot(D3DXVECTOR3(0.0f, m_effectRot,0.0f));
		effect->SetSize(D3DXVECTOR3(20.0f, 1.0f, 0.0f));
		effect->SetIsCulling(true);
		effect->SetTexture("LINE");
		SetEndChildren(effect);
	}
}

void CYamatoSkill_1::UninitAbility()
{
	m_apChara->SetToFaceRot(true);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CYamatoSkill_1::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 1.5f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CYamatoSkill_1 *CYamatoSkill_1::Create(CCharacter* chara)
{
	// ��������
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	CYamatoSkill_1* pSkill = new CYamatoSkill_1;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_1";
	pSkill->Init();

	return pSkill;
}