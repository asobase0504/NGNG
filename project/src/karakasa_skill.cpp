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
#include "karakasa_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CKarakasaSkill::CKarakasaSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CKarakasaSkill::~CKarakasaSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CKarakasaSkill::InitAbility()
{
	m_Duration = 400;

	m_aimCharacter = nullptr;

	// �_����̌���
	CMap::GetMap()->DoDifferentRelation(m_apChara->GetRelation(), [this](CCharacter* inChara)
	{
		m_aimCharacter = inChara;
	});

	m_apChara->SetMoveY(15.0f);
	m_apChara->SetMoveLock(true);
	m_apChara->SetInertiaMoveLock(true);

	m_time = 0;
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CKarakasaSkill::AllWayAbility()
{
	if (m_aimCharacter == nullptr)
	{
		return;
	}

	m_time++;

	if (m_time == 10)
	{
		D3DXVECTOR3 move = m_aimCharacter->GetPos() - m_apChara->GetPos();
		D3DXVec3Normalize(&move, &move);
		move *= 10.0f;
		m_apChara->SetMove(move);

		// �����蔻����擾
		CCollision* collision = CCollisionSphere::Create(CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 50.0f)), 30.0f);
		m_collision.push_back(collision);
		collision->SetParent(&m_apChara->GetPos());
		SetEndChildren(collision);

		m_apChara->SetToFaceRot(false);
	}

	// �I������
	if (m_apChara->GetState() == CCharacter::STATE::GROUND)
	{
		m_Duration = 0;
	}
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CKarakasaSkill::UninitAbility()
{
	m_apChara->SetMoveLock(false);
	m_apChara->SetInertiaMoveLock(false);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CKarakasaSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 1.5f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CKarakasaSkill *CKarakasaSkill::Create(CCharacter* chara)
{
	CKarakasaSkill* pSkill = new CKarakasaSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_1";
	pSkill->Init();

	return pSkill;
}