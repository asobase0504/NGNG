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
#include "statue.h"
#include "collision_box.h"
#include "application.h"
#include "utility.h"

#include "map.h"
#include "object_mesh.h"

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
CStatue* CStatueManager::CreateStatue(D3DXVECTOR3 pos, EType type)
{
	CMap* pMap = CMap::GetMap();
	CMesh* pMesh = pMap->GetMapMesh(0);

	D3DXVECTOR3 Meshpos = pMesh->GetPos();

	switch (type)
	{
	case CStatueManager::NONE:
		m_pStatue = CStatue::Create(pos,D3DXVECTOR3(0.0f,0.0f,0.0f));
		break;
	case CStatueManager::BLOOD:
		RandomCreateBlood(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::CHEST:
		RandomCreateChest(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::LUCK:
		RandomCreateLuck(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::COMBAT:
		RandomCreateCombat(D3DXVECTOR3(pos.x, Meshpos.y, pos.z));
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
	}

	return m_pStatue;
}

//--------------------------------------------------------------
// ���̍Ւd�����_������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateBlood(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	m_pStatue = CStatueBlood::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));

	return m_pStatue;
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

	for (int nCnt = 0; nCnt < randomCount; nCnt++)
	{
		float randomPosX = FloatRandom(400.0f, -500.0f);
		float randomPosZ = FloatRandom(500.0f,-415.0f);
		m_pStatue = CStatueChest::Create(D3DXVECTOR3(randomPosX,pos.y, randomPosZ));
	}
	
	return m_pStatue;
}

//--------------------------------------------------------------
// �^�̍Ւd�����_������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateLuck(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	m_pStatue = CStatueLuck::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));

	return m_pStatue;
}

//--------------------------------------------------------------
// �킢�̍Ւd�����_������
//--------------------------------------------------------------
CStatue * CStatueManager::RandomCreateCombat(D3DXVECTOR3 pos)
{
	float randomPosX = FloatRandom(400.0f, -500.0f);
	float randomPosZ = FloatRandom(500.0f, -415.0f);

	m_pStatue = CStatueCombat::Create(D3DXVECTOR3(randomPosX, pos.y, randomPosZ));

	return m_pStatue;
}


