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
CSkill::CSkill(int nPriority)
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

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CSkill::Uninit(void)
{
	// �j������
	CTask::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CSkill::Update(void)
{
	// �X�L���f�[�^�̃C���X�^���X���擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_CT > 0)
	{// �N�[���^�C��������Ό���������
		m_CT--;
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
// �X�L��1
//--------------------------------------------------------------
void CSkill::Skill1()
{
	if (m_CT == 0)
	{// �N�[���^�C�����Ȃ���Γ����蔻��𐶐�����
		// �����蔻��̎������Ԃ̊Ǘ�
		CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
		pSkillData->GetDuration(m_Name);
		CSkillEntity* entity = pSkillData->GetAbility(m_Name)(m_apChara);

		// �e�q�֌W�̍\�z
		SetEndChildren(entity);

		// �N�[���^�C���̐ݒ�
		m_CT = pSkillData->GetCT(m_Name);
	}
}

//--------------------------------------------------------------
// �X�L��1
//--------------------------------------------------------------
void CSkill::Skill2()
{
	if (m_CT == 0)
	{// �N�[���^�C�����Ȃ���Γ����蔻��𐶐�����
	 // �����蔻��̎������Ԃ̊Ǘ�
		CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();
		pSkillData->GetDuration(m_Name);
		pSkillData->GetAbility(m_Name)(m_apChara);

		// �N�[���^�C���̐ݒ�
		m_CT = pSkillData->GetCT(m_Name);
	}
}

//--------------------------------------------------------------
// �X�L���̐ݒ�
//--------------------------------------------------------------
void CSkill::SetSkill(std::string tag, CCharacter *chara)
{
	// ��������
	m_Name = tag;
	m_apChara = chara;
}