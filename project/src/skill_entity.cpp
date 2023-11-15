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
	MapChangeRelese();
	m_Duration = 200;
	// ������
	InitAbility();

	m_relation = m_apChara->GetRelation();
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
		bool collision = false;

		// ���ʎ��Ԃ̌���
		m_Duration--;

		if (m_Collision == nullptr)
		{
			return;
		}

		// �����Ƃ͈Ⴄ�֌W�������Ă�L�����N�^�[�ɍs�Ȃ�
		CMap::GetMap()->DoDifferentRelation(m_relation, [this, &collision](CCharacter* inChara)
		{
			// �����蔻��
			bool hit = m_Collision->ToSphere((CCollisionSphere*)inChara->GetCollision());
			if (hit)
			{// �_���[�W�̔���
				HitAbility(inChara);
				collision = true;
			}
		});

		if (collision)
		{// �G�ɓ������Ă�����
			Uninit();
		}
	}
	else if(m_Duration <= 0)
	{// ���ʎ��Ԃ�0�ȉ��ɂȂ��������
		Uninit();
	}

#ifdef _DEBUG
	CDebugProc::Print("Duration : %\n", m_Duration);
#endif // _DEBUG
}