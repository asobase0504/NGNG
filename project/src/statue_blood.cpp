//**************************************************************
//
// ���̍Ւd
// Author : ���c�喲
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "statue_blood.h"
#include "statue_manager.h"
#include "player_manager.h"
#include "select_ui.h"
#include "procedure3D.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueBlood::CStatueBlood():
	m_subRateUI(nullptr)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueBlood::~CStatueBlood()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueBlood::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos, rot);
	LoadModel("STATUE_BLOOD");

	m_hpSubRate = 0.1f;

	int percent = (int)(m_hpSubRate * 100);

	m_uiText = "���������B[" + std::to_string(percent) + "%]";

	m_subRateUI = CProcedure3D::Create(pos, D3DXVECTOR3(4.0f, 4.0f, 0.0f), percent);
	SetEndChildren(m_subRateUI);
	m_subRateUI->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));


	return S_OK;
}

//--------------------------------------------------------------
// �I�����ꂽ�Ƃ�
//--------------------------------------------------------------
bool CStatueBlood::Select(CCharacter* selectCharacter)
{
	CCharacter* character = selectCharacter;
	CStatus<int>* hp = character->GetHp();
	CStatus<int>* money = character->GetMoney();
	// �v���C���[��HP�Ƃ����𒲐����Đݒ�

	int max = hp->GetMax();
	int point = (int)(max * m_hpSubRate);
	hp->AddCurrent(-point);
	money->AddCurrent(point);

	m_hpSubRate *= 2.5f;
	int percent = (int)(m_hpSubRate * 100);
	m_uiText = "���������B[" + std::to_string(percent) + "%]";

	m_subRateUI->SetNumber(percent);

	if (m_hpSubRate >= 1.0f)
	{
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;
		m_subRateUI->Uninit();
		m_subRateUI = nullptr;
	}

	return true;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueBlood* CStatueBlood::Create(D3DXVECTOR3 pos)
{
	CStatueBlood* pStatueblood;
	pStatueblood = new CStatueBlood;
	pStatueblood->SetPos(pos);
	pStatueblood->Init();

	return pStatueblood;
}


//--------------------------------------------------------------
// �ʒu
//--------------------------------------------------------------
void CStatueBlood::SetPos(const D3DXVECTOR3 & inPos)
{
	if (m_subRateUI != nullptr)
	{
		m_subRateUI->SetPos(inPos);

		D3DXVECTOR3 vector = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
		D3DXMATRIX mtxRot;
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXVec3TransformCoord(&vector, &vector, &mtxRot);
		m_subRateUI->AddPos(vector);
		m_subRateUI->AddPos(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	}
	CStatue::SetPos(inPos);
}
