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
CSkillEntity::CSkillEntity(int nPriority) : 
	m_Collision(nullptr)
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
	m_Duration = 200;
	// ������
	InitAbility();

	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CSkillEntity::Uninit()
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
void CSkillEntity::Update()
{
	// �X�L���f�[�^�̃C���X�^���X���擾����
	CSkillDataBase *pSkillData = CSkillDataBase::GetInstance();

	AllWayAbility();

	if (m_Duration > 0)
	{
		m_Duration--;

		if (m_Collision == nullptr)
		{
			return;
		}

		// �����蔻��
		std::list<CCharacter*> charaList = CMap::GetMap()->GetCharacterList();

		for (CCharacter* chara : charaList)
		{// �U���͈͂ɓG�����邩���肷��

			// �����֌W����������U���𓖂ĂȂ��B
			switch (m_apChara->GetRelation())
			{
			case CCharacter::ERelation::FRIENDLY:
				if (chara->GetRelation() == CCharacter::ERelation::FRIENDLY)
				{
					continue;
				}
				break;
			case CCharacter::ERelation::HOSTILE:
				if (chara->GetRelation() == CCharacter::ERelation::HOSTILE)
				{
					continue;
				}
				break;
			default:
				assert(false);
				break;
			}

			bool hit = m_Collision->ToSphere((CCollisionSphere*)chara->GetCollision());
			if (hit)
			{// �_���[�W�̔���
				HitAbility(chara);
			}
		}
	}
	else
	{
		Uninit();
	}
}