//**************************************************************
//
// 敵
// Author : 梶田大夢
//
//**************************************************************

#ifdef _DEBUG
#if 0
#define ENEMY_DEBUG
#endif
#endif

// include
#include "enemy.h"
#include "player.h"
#include "player_manager.h"
#include "status.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_box.h"
#include "enemy_hp_ui.h"
#include "model_skin.h"

#include "enemy_data_base.h"
#include "skill.h"
#include "game.h"
#include "difficult.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CEnemy::CEnemy()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CEnemy::~CEnemy()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CEnemy::Init()
{
	// 初期化処理
	CCharacter::Init();

	// 敵対状態
	m_relation = ERelation::HOSTILE;

	m_AttackCnt = 0;
	// モデルの読み込み
	m_skinModel->Load("TENGU");
	SetEndChildren(m_skinModel);

	// HPUIの作成
	m_pEHPUI = CEnemy_HPUI::Create(this);
	SetEndChildren(m_pEHPUI);

	// 当たり判定の作成
	m_collision = CCollisionCylinder::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10.0f, 10.0f);
	m_collision->SetParent(&m_pos);
	SetEndChildren(m_collision);

	m_dropMoney = 5;

	m_diedCount = 0;
	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CEnemy::Update()
{
	if (m_isDied)
	{
		m_diedCount++;

		if (m_diedCount > 30)
		{
			Uninit();
		}
		return;
	}

	if (m_isStun)
	{
		SetMove(D3DXVECTOR3(0.0f,0.0f,0.0f));
		return;
	}

	if (!m_isMoveLock)
	{
		Move();
	}

	// 更新処理
	CCharacter::Update();

#ifdef ENEMY_DEBUG
	CDebugProc::Print("Enemy：move3(%f,%f,%f)\n", m_move.x, m_move.y, m_move.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// 死亡判定
//--------------------------------------------------------------
void CEnemy::Died()
{
	CPlayerManager::GetInstance()->GetPlayer()->GetMoney()->AddCurrent(m_dropMoney);
	CCharacter::Died();
}
