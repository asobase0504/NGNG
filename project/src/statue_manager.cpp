//**************************************************************
//
// ���Ǘ�
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_manager.h"
#include "statue_blood.h"
#include "statue_chest.h"
#include "statue_luck.h"
#include "statue_combat.h"
#include "statue_teleporter.h"
#include "statue.h"
#include "collision_box.h"
#include "application.h"
#include "utility.h"

#include "map.h"
#include "object_mesh.h"
#include "collision_mesh.h"

//--------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------------------------
CStatueManager* CStatueManager::m_statueManager = nullptr;

//--------------------------------------------------------------
// �V���O���g���ł̃C���X�^���X�̎擾
//--------------------------------------------------------------
CStatueManager* CStatueManager::GetInstance()
{
	if (m_statueManager == nullptr)
	{
		m_statueManager = new CStatueManager;
	}
	return m_statueManager;
}

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueManager::CStatueManager()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueManager::~CStatueManager()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueManager::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// �I������
//--------------------------------------------------------------
void CStatueManager::Uninit(void)
{
	if (m_statueManager != nullptr)
	{
		m_statueManager = nullptr;
	}
	CTask::Uninit();
}

//--------------------------------------------------------------
// ��������
//--------------------------------------------------------------
CStatue* CStatueManager::CreateStatue(D3DXVECTOR3 pos, int type)
{
	CStatue* statue = nullptr;
	switch (type)
	{
	case CStatueManager::BLOOD:
		statue = CStatueBlood::Create(pos);
		break;
	case CStatueManager::CHEST:
		statue = CStatueChest::Create(pos);
		break;
	case CStatueManager::LUCK:
		statue = CStatueLuck::Create(pos);
		break;
	case CStatueManager::COMBAT:
		statue = CStatueCombat::Create(pos);
		break;
	case CStatueManager::TELEPORTER:
		statue = CStatueTeleporter::Create(pos);
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
	}

	return statue;
}

//--------------------------------------------------------------
// ��������
//--------------------------------------------------------------
CStatue * CStatueManager::CreateStatue(int type)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	D3DXVECTOR3 pos(randomPosX, -FLT_MAX, randomPosZ);

	return CreateStatue(pos, type);
}

//--------------------------------------------------------------
// �����_���ȑ���������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreate()
{
	// ����
	int randomCount = IntRandom(5, 1);
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue;

	if (randomCount != 2)
	{
		statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), randomCount);
	}
	else
	{
		int rand = IntRandom(4, 1);

		if (rand == 1)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), 1);
		}
		else if (rand == 2)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), 3);
		}
		else
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, -FLT_MIN, randomPosZ), 4);
		}
	}

	return statue;
}
