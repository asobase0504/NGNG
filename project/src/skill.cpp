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
	// �X�L��1�̃C���X�^���X���擾
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();		// �������ɐ���

	if (m_apChara != nullptr && m_Name != "\0")
	{
		bool a = pSkillData->GetAbility(m_Name)(m_apChara);			// �����������ǂ������肷��

	}
	
	
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
// �X�L�������蔻��
//--------------------------------------------------------------
void CSkill::CollisionSkill()
{
	if (m_apChara != nullptr)
	{
		// �����蔻��
		m_Collision = CCollisionSphere::Create(m_apChara->GetPos(), CSkillDataBase::GetInstance()->GetSize("YAMATO_SKILL_1").x);
		std::vector<CEnemy*> Enemy = CEnemyManager::GetInstance()->GetEnemy();
		// �G�l�~�[�̐����擾
		int EnemyCount = Enemy.size();

		for (int nCnt = 0; nCnt < EnemyCount; nCnt++)
		{// �U���͈͂ɓG�����邩���肷��
			m_isCollision = false;
			m_isCollision = m_Collision->ToSphere((CCollisionSphere*)Enemy[nCnt]->GetCollision());
		}

		if (m_isCollision)
		{

		}
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