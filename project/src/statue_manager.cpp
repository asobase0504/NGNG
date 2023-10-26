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
	switch (type)
	{
	case CStatueManager::NONE:
		m_pStatue = CStatue::Create(pos,D3DXVECTOR3(0.0f,0.0f,0.0f));
		break;
	case CStatueManager::BLOOD:
		m_pStatue = CStatueBlood::Create(pos);
		break;
	case CStatueManager::CHEST:
		m_pStatue = CStatueChest::Create(pos);
		break;
	case CStatueManager::LUCK:
		RabdomCreate(pos);
		break;
	case CStatueManager::COMBAT:
		m_pStatue = CStatueCombat::Create(pos);
		break;
	case CStatueManager::MAX:
		break;
	default:
		break;
	}

	return m_pStatue;
}

//--------------------------------------------------------------
// �����_����������
//--------------------------------------------------------------
CStatue * CStatueManager::RabdomCreate(D3DXVECTOR3 pos)
{
	int randomCount = IntRandom(15, 8);

	for (int nCnt = 0; nCnt < randomCount; nCnt++)
	{
		float randomPos = FloatRandom(420.0f, -420.0f);
		m_pStatue = CStatueLuck::Create(D3DXVECTOR3(randomPos,pos.y, randomPos));
	}
	
	return m_pStatue;
}
