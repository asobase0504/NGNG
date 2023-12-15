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
	m_skinModel = CSkinMesh::Create("SKE");
	SetEndChildren(m_skinModel);

	m_Activity = (CEnemyDataBase::GetInstance()->GetActivityFunc(CEnemyDataBase::EActivityPattern::PATTERN_GOLEM));

	m_pEHPUI = CEnemy_HPUI::Create(this);
	SetEndChildren(m_pEHPUI);

	// 当たり判定の作成
	m_collision = CCollisionCylinder::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10.0f, 10.0f);
	m_collision->SetParent(&m_pos);
	SetEndChildren(m_collision);

	// SKILLの作成
	m_skill.push_back(CSkill::Create());
	m_skill[0]->SetSkill("GOLEM_SKILL_1",this);
	SetEndChildren(m_skill[0]);

	m_dropMoney = 5;
	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CEnemy::Update()
{
	if (m_isDied)
	{
		Uninit();
		return;
	}

	if (m_isStun)
	{
		SetMove(D3DXVECTOR3(0.0f,0.0f,0.0f));
		return;
	}

	// 現在のactivityに設定する。
	m_Activity(this);

	CDifficult *pDiff = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetDifficult();
	int exp = pDiff->GetLevel();

	AddExp(exp);

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

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
void CEnemy::Move()
{
	// 移動量の取得
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	// プレイヤーの位置取得
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

	// 敵の追従
	if (pos.x <= PlayerPos.x)
	{
		move.x += MAX_SPEED;
	}
	else
	{
		move.x -= MAX_SPEED;
	}
	if (pos.z <= PlayerPos.z)
	{
		move.z += MAX_SPEED;
	}
	else
	{
		move.z -= MAX_SPEED;
	}

	SetMoveXZ(move.x,move.z);
}