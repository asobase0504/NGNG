//**************************************************************
//
// ���̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_blood.h"
#include "statue_manager.h"
#include "player_manager.h"
#include "input.h"
#include "map.h"
#include "collision_mesh.h"
#include "collision_box.h"
#include "object_mesh.h"
#include "select_ui.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueBlood::CStatueBlood(int nPriority)
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

	m_uiText = "���������B[" + std::to_string((int)(m_hpSubRate * 100)) + "%]";

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
	m_uiText = "���������B[" + std::to_string((int)(m_hpSubRate * 100)) + "%]";

	if (m_hpSubRate >= 1.0f)
	{
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;
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