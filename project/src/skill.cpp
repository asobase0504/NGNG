//**************************************************************
//
// �X�L��
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

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkill::CSkill()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkill::~CSkill()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CSkill::Init()
{
	// ������
	m_CT = 0;

	m_stockMax = CSkillDataBase::GetInstance()->GetStack(m_Name);
	m_stock = m_stockMax;

	return S_OK;
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CSkill::Update()
{
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_CT > 0 && m_stock != m_stockMax)
	{// �N�[���^�C��������Ό���������
		m_CT--;
	}

	if (m_CT <= 0 && m_stock < m_stockMax)
	{
		m_stock++;
		m_CT = pSkillData->GetCT(m_Name);
	}

#ifdef _DEBUG
	CDebugProc::Print("%s�̃N�[���^�C�� : %d\n", m_Name.c_str(),m_CT);
#endif // _DEBUG
}

//--------------------------------------------------------------
// �X�L����������
//--------------------------------------------------------------
CSkill *CSkill::Create()
{
	// ��������
	CSkill* pSkill = new CSkill;
	pSkill->Init();

	return pSkill;
}

//--------------------------------------------------------------
// �X�L��
//--------------------------------------------------------------
bool CSkill::Use()
{
	if (m_stock <= 0)
	{
		return false;
	}

	// �N�[���^�C�����Ȃ���Γ����蔻��𐶐�����

	m_stock--;

	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
	CSkillEntity* entity = pSkillData->GetAbility(m_Name)(m_apChara);

	// �e�q�֌W�̍\�z
	SetEndChildren(entity);

	// �N�[���^�C���̐ݒ�
	m_atkSpd = m_apChara->GetAtkSpd()->GetCurrent();
	m_CT = pSkillData->GetCT(m_Name);

	return true;
}

//--------------------------------------------------------------
// �X�L���̐ݒ�
//--------------------------------------------------------------
void CSkill::SetSkill(std::string tag, CCharacter *chara)
{
	// ��������
	m_Name = tag;
	m_apChara = chara;
	m_stockMax = CSkillDataBase::GetInstance()->GetStack(m_Name);
	m_stock = m_stockMax;
}