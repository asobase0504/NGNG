//**************************************************************
//
// �^�̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_luck.h"
#include "character.h"
#include "collision_cylinder.h"
#include "item_manager.h"
#include "input.h"
#include "utility.h"
#include "procedure3D.h"

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
// ������
//--------------------------------------------------------------
HRESULT CStatueLuck::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	m_nUseMoney = 10;
	m_costUI = CProcedure3D::Create(pos, D3DXVECTOR3(4.0f, 4.0f, 0.0f), m_nUseMoney);
	SetEndChildren(m_costUI);
	m_costUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	CStatue::Init(pos,rot);
	LoadModel("STATUE_LUCK");

	m_nItemCount = 0;
	m_uiText = "�^������ [$" + std::to_string(m_nUseMoney) + "]";

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
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

	m_costUI->SetNumber(m_nUseMoney);

	m_uiText = "�^������ [$" + std::to_string(m_nUseMoney) + "]";

	if (m_nItemCount >= 2)
	{
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;
		m_costUI->Uninit();
		m_costUI = nullptr;
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

//--------------------------------------------------------------
// �ʒu
//--------------------------------------------------------------
void CStatueLuck::SetPos(const D3DXVECTOR3 & inPos)
{
	if (m_costUI != nullptr)
	{
		m_costUI->SetPos(inPos);

		D3DXVECTOR3 vector = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
		D3DXMATRIX mtxRot;
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXVec3TransformCoord(&vector, &vector, &mtxRot);
		m_costUI->AddPos(vector);
		m_costUI->AddPos(D3DXVECTOR3(0.0f,10.0f,0.0f));
	}
	CStatue::SetPos(inPos);
}
