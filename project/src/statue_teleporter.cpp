//**************************************************************
//
// テレポーターの祭壇
// Author : 梶田大夢
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

#include "hp_ui.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueTeleporter::CStatueTeleporter(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueTeleporter::~CStatueTeleporter()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueTeleporter::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	m_time = 0;

	CStatue::Init(pos, rot);

	m_collisionBox->SetSize(D3DXVECTOR3(50.0f, 40.0f, 40.0f));
	m_collisionCylinder->SetLength(50.0f);
	m_collisionCylinder->SetHeight(50.0f);

	LoadModel("STATUE_SHRINE");
	m_uiText = "テレポート起動";
	m_bOnce = false;
	m_btimeAdd = false;

	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueTeleporter::Update()
{
	if (m_bOnce)
	{
		if ((m_pEnemy->IsDied()) && (m_time >= MAX_TIME))
		{
			//-------------------------
			// マップ移動処理追加
			//-------------------------
			CGame* game = (CGame*)(CApplication::GetInstance()->GetModeClass());
			game->SetChangeMap();
		}
	}

	if (m_btimeAdd)
	{
		// 時間追加
		m_time++;
	}

	// 更新処理
	CStatue::Update();
}

//--------------------------------------------------------------
// 選んだ時
//--------------------------------------------------------------
bool CStatueTeleporter::Select(CCharacter * selectCharacter)
{
	if (!m_bOnce)
	{
		D3DXVECTOR3 popPos = m_pos;
		popPos.x += FloatRandom(100.0f, -100.0f);
		popPos.z += FloatRandom(100.0f, -100.0f);

		m_pEnemy = CEnemyManager::GetInstance()->CreateEnemy(popPos, D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE,1);
		CBossHPUI* ui = new CBossHPUI;
		ui->Init();
		ui->SetHP(m_pEnemy->GetHp());
		m_pEnemy->SetEndChildren(ui);

		selectCharacter->SetIsTeleporter(true);
		m_bOnce = true;
	}

	m_btimeAdd = true;

	return true;
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueTeleporter* CStatueTeleporter::Create(D3DXVECTOR3 pos)
{
	CStatueTeleporter* pStatueteleporter;
	pStatueteleporter = new CStatueTeleporter;
	pStatueteleporter->SetPos(pos);
	pStatueteleporter->Init();

	return pStatueteleporter;
}