//**************************************************************
//
// �^�̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_luck.h"
#include "player_manager.h"
#include "item_manager.h"
#include "input.h"
#include "utility.h"

namespace
{
std::array<float, CItemDataBase::RARITY_MAX> rate = { 0.05f,0.1f,0.2f,0.65f };
};

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueLuck::CStatueLuck()
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueLuck::~CStatueLuck()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueLuck::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos,rot);
	LoadModel("STATUE_LUCK");

	m_nUseMoney = 10;
	m_nItemCount = 0;
	m_uiText = "�^������ [$" + std::to_string(m_nUseMoney) + "]";

	return S_OK;
}

bool CStatueLuck::Select(CCharacter * selectCharacter)
{
	CStatus<int>* money = selectCharacter->GetMoney();

	if (money->GetCurrent() < m_nUseMoney)
	{
		return false;
	}

	// �v���C���[�����𒲐����Đݒ�
	money->AddCurrent(-m_nUseMoney);

	D3DXVECTOR3 pos(m_pos.x, m_pos.y + 30.0f, m_pos.z);
	int answer = CItemManager::GetInstance()->CreateRandomItemRarityRate(pos, GetMtxRot(), rate);

	switch (answer)
	{
	case 0:	// ���A
	case 1:	// �A���R����
	case 2:	// �R����
		m_nItemCount++;
		break;
	case 3:	// �n�Y��
		break;
	default:
		assert(false);
		break;
	}

	// ����K�`�����鎞�p�ɕK�v�������𑝂₵�Đݒ肵�Ă���
	int randomNumber = rand() % 10;
	m_nUseMoney += randomNumber;

	m_uiText = "�^������ [$" + std::to_string(m_nUseMoney) + "]";

	if (m_nItemCount >= 2)
	{
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;
	}

	return true;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueLuck* CStatueLuck::Create(D3DXVECTOR3 pos)
{
	CStatueLuck* pStatuechest;
	pStatuechest = new CStatueLuck;
	pStatuechest->SetPos(pos);
	pStatuechest->Init();

	return pStatuechest;
}