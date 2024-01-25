//**************************************************************
//
// �e���|�[�^�[�̍Ւd
// Author : ���c�喲
//
//**************************************************************

// include
#include "statue_teleporter.h"
#include "statue_manager.h"
#include "player_manager.h"
#include "input.h"
#include "map.h"
#include "collision_mesh.h"
#include "collision_box.h"
#include "object_mesh.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "utility.h"
#include "application.h"
#include "game.h"
#include "teleporter_event_ui.h"

#include "hp_ui.h"
#include "map_fade.h"

const int CStatueTeleporter::CHARGE_TIME	(360);

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CStatueTeleporter::CStatueTeleporter(int nPriority)
{

}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CStatueTeleporter::~CStatueTeleporter()
{

}

//--------------------------------------------------------------
// ����������
//--------------------------------------------------------------
HRESULT CStatueTeleporter::Init()
{
	// ����������
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	m_time = 0;

	CStatue::Init(pos, rot);

	m_collisionBox->SetSize(D3DXVECTOR3(50.0f, 40.0f, 40.0f));
	m_collisionCylinder->SetLength(50.0f);
	m_collisionCylinder->SetHeight(50.0f);

	LoadModel("STATUE_SHRINE");
	m_uiText = "�e���|�[�g�N��";
	m_bOnce = false;
	m_btimeAdd = false;
	m_isBossDead = false;

	m_pEnemy = nullptr;

	SetMark("GATE");
	return S_OK;
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void CStatueTeleporter::Update()
{
	if (m_pEnemy != nullptr)
	{
		if (m_pEnemy->IsDied())
		{
			m_isBossDead = true;
			m_pEnemy = nullptr;
		}
	}

	if (m_bOnce)
	{
		if (m_isBossDead && (m_time >= CHARGE_TIME))
		{
			//-------------------------
			// �}�b�v�ړ������ǉ�
			//-------------------------
			CApplication::GetInstance()->GetModeClass()->GetMapFade()->Start();
		}
	}

	if (m_btimeAdd)
	{
		// ���Ԓǉ�
		m_time++;
	}

	// �X�V����
	CStatue::Update();
}

//--------------------------------------------------------------
// �I�񂾎�
//--------------------------------------------------------------
bool CStatueTeleporter::Select(CCharacter* selectCharacter)
{
	if (!m_bOnce)
	{
		D3DXVECTOR3 popPos = m_pos;
		popPos.x += FloatRandom(100.0f, -100.0f);
		popPos.z += FloatRandom(100.0f, -100.0f);

		m_pEnemy = CEnemyManager::GetInstance()->CreateEnemy(popPos, CEnemyDataBase::GASYADOKURO,5);
		CBossHPUI* ui = new CBossHPUI;
		ui->Init();
		ui->SetHP(m_pEnemy->GetHp());
		ui->SetNameUI("��������");
		m_pEnemy->SetEndChildren(ui);

		DeleteMark();
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;

		selectCharacter->SetIsTeleporter(true);
		m_bOnce = true;
	}

	CTeleporterEventUI* eventUI = new CTeleporterEventUI;
	eventUI->Init();
	eventUI->SetReferenceTime(&m_time);
	eventUI->SetReferenceIsBossKill(&m_isBossDead);
	SetEndChildren(eventUI);

	m_btimeAdd = true;

	return true;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CStatueTeleporter* CStatueTeleporter::Create(D3DXVECTOR3 pos)
{
	CStatueTeleporter* pStatueteleporter;
	pStatueteleporter = new CStatueTeleporter;
	pStatueteleporter->SetPos(pos);
	pStatueteleporter->Init();

	return pStatueteleporter;
}