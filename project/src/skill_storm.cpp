//**************************************************************
//
// �䕗
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
// skill
#include "skill_storm.h"
#include "utility.h"

#include "collision_cylinder.h"
#include "object_polygon3d.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkillStorm::CSkillStorm()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkillStorm::~CSkillStorm()
{

}

//--------------------------------------------------------------
// �X�L�����n�܂�Ƃ�
//--------------------------------------------------------------
void CSkillStorm::InitAbility()
{
	D3DXVECTOR3 move = CalculatePerimeterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apChara->GetRot(), D3DXVECTOR3(0.0f, 0.0f, 3.5f));
	m_bullet = new CObject;
	m_bullet->SetPos(m_apChara->GetPos());
	m_bullet->SetMove(move);
	SetEndChildren(m_bullet);

	//m_effectBG = CObjectPolygon3D::Create();
	//m_effectBG->SetSize(D3DXVECTOR3(120.0f, 60.0f, 0.0f));
	//m_effectBG->SetBillboard(true);
	//m_effectBG->SetColor(D3DXCOLOR(0.8f,0.8f,1.0f,0.5f));
	//SetEndChildren(m_effectBG);

	m_Duration = 180;
}

//--------------------------------------------------------------
// ���
//--------------------------------------------------------------
void CSkillStorm::AllWayAbility()
{
	if (m_collision.empty())
	{
		m_timer++;
		if (m_timer % 5 == 0)
		{
			// �����蔻��
			CCollision* collision = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 120.0f, 120.0f);
			m_collision.push_back(collision);
			collision->SetParent(&m_bullet->GetPos());

			m_bullet->SetEndChildren(collision);
		}
	}

	//{
	//	D3DXVECTOR3 pos = m_bullet->GetPos();
	//	pos.y += (60 - m_Duration);
	//	m_effectBG->SetSize(D3DXVECTOR3(120.0f, (60 - m_Duration), 0.0f));
	//	m_effectBG->SetPos(pos);
	//}

	for (int i = 0; i < 2; i++)
	{
		float rotY = FloatRandom(D3DX_PI, -D3DX_PI);
		float diff = FloatRandom(120.0f, 0.0f);
		D3DXVECTOR3 targetPos = CalculatePerimeterPos(m_bullet->GetPos(), D3DXVECTOR3(0.0f, rotY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, diff));
		targetPos.y += 60.0f + FloatRandom(4.0f,-4.0f);

		CObjectPolygon3D* effect = CObjectPolygon3D::Create();
		effect->SetPos(targetPos);
		effect->SetRot(D3DXVECTOR3(0.0f, rotY, 0.0f));
		effect->SetSize(D3DXVECTOR3(20.0f, 1.0f, 0.0f));
		effect->SetIsCulling(true);
		effect->SetTexture("LINE");
		effect->SetLife(20);
		SetEndChildren(effect);
	}
}

//--------------------------------------------------------------
// �X�L�����I����
//--------------------------------------------------------------
void CSkillStorm::UninitAbility()
{
	m_apChara->SetInertiaMoveLock(false);
	m_apChara->SetMoveLock(false);
}

//--------------------------------------------------------------
// �X�L���������������̌���
//--------------------------------------------------------------
void CSkillStorm::HitAbility(CCharacter * Target)
{
	// todo �v���C���[�̍ŏI�I�ȍU���͂��擾����
	m_apChara->DealDamage(Target, 0.15f);
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CSkillStorm *CSkillStorm::Create(CCharacter* chara)
{
	CSkillStorm* pSkill = new CSkillStorm;
	pSkill->m_apChara = chara;
	pSkill->Init();
	return pSkill;
}