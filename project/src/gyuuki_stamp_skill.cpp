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
#include "gyuuki_stamp_skill.h"
#include "skill.h"
#include "skill_data_base.h"

#include "collision_sphere.h"
#include "collision_box.h"
#include "utility.h"

#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CGyuukiStampSkill::CGyuukiStampSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CGyuukiStampSkill::~CGyuukiStampSkill()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CGyuukiStampSkill::InitAbility()
{
	m_Duration = 20;
	m_time = 0;

	int random = IntRandom(2,2);
	D3DXVECTOR3 separate;
	switch (random)
	{
	case 0:
		separate = D3DXVECTOR3(195.0f, 0.0f, 195.0f);
		break;
	case 1:
		separate = D3DXVECTOR3(-195.0f, 0.0f, 195.0f);
		break;
	case 2:
		separate = D3DXVECTOR3(195.0f, 0.0f, -195.0f);
		break;
	case 3:
		separate = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
		break;
	case 4:
		separate = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
		break;
	case 5:
		break;
		separate = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	default:
		break;
	}

	// �����蔻����擾
	D3DXVECTOR3 pos = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), separate);
	CCollision* collision = CCollisionBox::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_collision.push_back(collision);
	collision->SetParent(&m_apChara->GetPos());
	SetEndChildren(collision);

	m_apChara->SetMoveLock(true);
	m_apChara->SetToFaceRot(true);
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CGyuukiStampSkill::AllWayAbility()
{
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CGyuukiStampSkill::UninitAbility()
{
	m_apChara->SetMoveLock(false);
	m_apChara->SetInertiaMoveLock(false);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CGyuukiStampSkill::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 1.5f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CGyuukiStampSkill *CGyuukiStampSkill::Create(CCharacter* chara)
{
	CGyuukiStampSkill* pSkill = new CGyuukiStampSkill;
	pSkill->m_apChara = chara;
	pSkill->m_Name = "YAMATO_SKILL_1";
	pSkill->Init();

	return pSkill;
}