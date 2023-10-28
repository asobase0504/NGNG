//**************************************************************
//
// �X�L���f�[�^�x�[�X
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "skill_data_base.h"
#include "collision_box.h"
#include "character.h"
#include "enemy_manager.h"
#include "collision_sphere.h"

//==============================================================
// �ÓI�����o�[�ϐ��̐錾
//==============================================================
CSkillDataBase* CSkillDataBase::m_instance = nullptr;

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkillDataBase::CSkillDataBase()
{
}

//--------------------------------------------------------------
// instance�̎擾
//--------------------------------------------------------------
CSkillDataBase * CSkillDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CSkillDataBase;
		
		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkillDataBase::~CSkillDataBase()
{
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CSkillDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;

}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
void CSkillDataBase::Init()
{
	m_dates["YAMATO_SKILL_1"] = { 0,1,1,0,60,0,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[this](CCharacter* inusedCharacter)
	{// �������̌���
		if (inusedCharacter != nullptr)
		{
			// �����蔻��
			m_Collision = CCollisionSphere::Create(inusedCharacter->GetPos(),GetSize("YAMATO_SKILL_1").x);
			std::vector<CEnemy*> Enemy = CEnemyManager::GetInstance()->GetEnemy();
			// �G�l�~�[�̐����擾
			int EnemyCount = Enemy.size();

			for (int nCnt = 0; nCnt < EnemyCount; nCnt++)
			{// �U���͈͂ɓG�����邩���肷��
				bool a = m_Collision->ToSphere((CCollisionSphere*)Enemy[nCnt]->GetCollision());
				if (a)
				{// �_���[�W�̔���
					GetHitAbility("YAMATO_SKILL_1")(inusedCharacter, inusedCharacter);
				}
			}
		}

		return false;
	},
		[this](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{// Hit���̌���
		//CStatus<unsigned int> atk = inusedCharacter->GetAtk();
		//int nAtk = atk.GetCurrent();

		inusedInTarget->Damage(50);

		return false;
	} };

	m_dates["YAMATO_SKILL_2"] = { 120,1,1,0,5,0,D3DXVECTOR3(30.0f,30.0f,30.0f),
		[this](CCharacter* inusedCharacter)
	{ // �������̌���
		return false;
	},
		[this](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{ // Hit���̌���
		return false;
	} };
	m_dates["YAMATO_SKILL_3"] = { 0,1,1,0,5,0,D3DXVECTOR3(0.0f,0.0f,0.0f),
		[](CCharacter* inusedCharacter)
	{ // �������̌���
		return false;
	},
		[](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{ // Hit���̌���
		return false;
	} };
	m_dates["YAMATO_SKILL_4"] = { 0,1,1,0,5,0,D3DXVECTOR3(0.0f,0.0f,0.0f),
		[](CCharacter* inusedCharacter)
	{ // �������̌���
		return false;
	},
		[](CCharacter* inusedCharacter,CCharacter* inusedInTarget)
	{ // Hit���̌���
		return false;
	} };
}