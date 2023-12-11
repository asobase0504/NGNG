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
		if (/*(m_pEnemy->IsDied()) &&*/ (m_time >= MAX_TIME))
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
		float randX = FloatRandom(1.5f, 0.5f);
		float randZ = FloatRandom(1.5f, 0.5f);

		//m_pEnemy = CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(randX, 0.0f, randZ), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);

		//CStatus<int>* enemyHp = m_pEnemy->GetHp();
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