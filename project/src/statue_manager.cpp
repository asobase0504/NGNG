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
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueManager::Update(void)
{
}

//--------------------------------------------------------------
// �`�揈��
//--------------------------------------------------------------
void CStatueManager::Draw(void)
{
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
		statue = RandomCreateBlood(pos);
		break;
	case CStatueManager::CHEST:
		statue = RandomCreateChest(pos);
		break;
	case CStatueManager::LUCK:
		statue = RandomCreateLuck(pos);
		break;
	case CStatueManager::COMBAT:
		statue = RandomCreateCombat(pos);
		break;
	case CStatueManager::TELEPORTER:
		statue = CStatueTeleporter::Create(pos);
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
	}
	m_pStatue.push_back(statue);

	return statue;
}

//--------------------------------------------------------------
// �����_���ȑ���������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreate(D3DXVECTOR3 pos)
{
	// ����
	int randomCount = IntRandom(5, 1);
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue;

	if (randomCount != 2)
	{
		statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), randomCount);
		m_pStatue.push_back(statue);
	}
	else
	{
		int rand = IntRandom(4, 1);

		if (rand == 1)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 1);
			m_pStatue.push_back(statue);
		}
		else if (rand == 2)
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 3);
			m_pStatue.push_back(statue);
		}
		else
		{
			statue = CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(randomPosX, pos.y, randomPosZ), 4);
			m_pStatue.push_back(statue);
		}
	}

	return statue;
}

//--------------------------------------------------------------
// ���̍Ւd�����_������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateBlood(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue = CStatueBlood::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
	m_pStatue.push_back(statue);

	return statue;
}

//--------------------------------------------------------------
// �󔠃����_������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateChest(D3DXVECTOR3 pos)
{
	// ������
	int randomCount = IntRandom(15, 8);

#ifdef _DEBUG
	randomCount = IntRandom(3, 1);
#endif // DEBUG

	CStatue* statue;
	for (int nCnt = 0; nCnt < randomCount; nCnt++)
	{
		float randomPosX = FloatRandom(400.0f, -500.0f);
		float randomPosZ = FloatRandom(500.0f,-415.0f);
		statue = CStatueChest::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
		m_pStatue.push_back(statue);
	}

	return statue;
}

//--------------------------------------------------------------
// �^�̍Ւd�����_������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateLuck(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue = CStatueLuck::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
	m_pStatue.push_back(statue);

	return statue;
}

//--------------------------------------------------------------
// �킢�̍Ւd�����_������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateCombat(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	CStatue* statue = CStatueCombat::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));
	m_pStatue.push_back(statue);

	return statue;
}

void CStatueManager::AllFuncStatue(std::function<void(CStatue*inStatue)> inFunc)
{
	std::for_each(m_pStatue.cbegin(), m_pStatue.cend(), inFunc);
}