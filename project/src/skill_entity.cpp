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
#include "map.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSkillEntity::CSkillEntity(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSkillEntity::~CSkillEntity()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CSkillEntity::Init()
{
	// ������
	m_Duration = 1;
	m_Interval = 0;
	m_isSkill = false;
	InitAbility();

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CSkillEntity::Uninit(void)
{
	// �����蔻��̍폜
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}

	// �j������
	CTask::Uninit();
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CSkillEntity::Update(void)
{
	// �X�L���f�[�^�̃C���X�^���X���擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	if (m_Duration > 0)
	{
		// �X�L���g�p���ɂ���
		m_isSkill = true;

		// �G�ɓ������Ă��邩
		bool collision = false;

		// ���ʎ��Ԃ̌���
		m_Duration--;
		m_Interval--;

		// �C���^�[�o��0�ȉ��œ����蔻�肪�Ȃ������瓖���蔻��𐶐�����
		if (m_Interval <= 0 && m_Collision == nullptr)
		{
			m_Collision = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), pSkillData->GetSize(m_Name).x);
			m_Collision->SetParent(&m_apChara->GetPos());
		}

		// �����蔻��
		std::list<CEnemy*> enemyList = CMap::GetMap()->GetEnemyList();

		if (m_Collision != nullptr)
		{
			for (CEnemy* enemy : enemyList)
			{// �U���͈͂ɓG�����邩���肷��
				bool EnemyCollision = m_Collision->ToSphere((CCollisionSphere*)enemy->GetCollision());
				if (EnemyCollision && m_Interval <= 0.0f)
				{// �_���[�W�̔���
					HitAbility(enemy);
					m_Interval = pSkillData->GetInterval(m_Name);
					collision = true;
				}
			}
		}

		if (collision)
		{// �G�ɓ������Ă�����
			m_Collision->Uninit();
			m_Collision = nullptr;
		}
	}
	else if(m_Duration <= 0)
	{// ���ʎ��Ԃ�0�ȉ��ɂȂ��������
		Uninit();
	}

#ifdef _DEBUG
	CDebugProc::Print("Duration : %f\n", m_Duration);
#endif // _DEBUG
}