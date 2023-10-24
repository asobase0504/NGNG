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
	// �X�L���f�[�^�̃C���X�^���X���擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_CT > 0)
	{// �N�[���^�C��������Ό���������
		m_CT--;
	}

#ifdef _DEBUG
	CDebugProc::Print("�X�L���̃N�[���^�C�� : %d\n", m_CT);
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
// �X�L�������蔻��
//--------------------------------------------------------------
void CSkill::CollisionSkill(std::string tag)
{
	// �X�L���f�[�^�̃C���X�^���X���擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_apChara != nullptr)
	{
		// �����蔻��
		m_Collision = CCollisionSphere::Create(m_apChara->GetPos(), pSkillData->GetSize(tag).x);
		std::vector<CEnemy*> Enemy = CEnemyManager::GetInstance()->GetEnemy();
		// �G�l�~�[�̐����擾
		int EnemyCount = Enemy.size();

		for (int nCnt = 0; nCnt < EnemyCount; nCnt++)
		{// �U���͈͂ɓG�����邩���肷��
			m_isCollision = false;
			m_isCollision = m_Collision->ToSphere((CCollisionSphere*)Enemy[nCnt]->GetCollision());

			if (m_isCollision)
			{// hit���ɐ���
				pSkillData->GetHitAbility(tag);
			}
		}
	}
}

//--------------------------------------------------------------
// �X�L��1
//--------------------------------------------------------------
void CSkill::Skill1()
{
	if (m_CT == 0)
	{// �N�[���^�C�����Ȃ���Γ����蔻��𐶐�����
		CollisionSkill("YAMATO_SKILL_1");
	}

	// �N�[���^�C���̐ݒ�
	m_CT = CSkillDataBase::GetInstance()->GetCT("YAMATO_SKILL_2");
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