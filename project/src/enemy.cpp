//**************************************************************
//
// 敵
// Author : 梶田大夢
//
//**************************************************************

#ifdef _DEBUG
#if 1
#define ENEMY_DEBUG
#endif
#endif

// include
#include "enemy.h"
#include "player.h"
#include "player_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_box.h"

#include "enemy_data_base.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CEnemy::CEnemy(int nPriority)
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

	m_apModel[0]->LoadModel("SKELETON");
	m_apModel[0]->CalculationVtx();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSize();
	D3DXMATRIX mtx = GetMtxWorld();


	m_Activity = (CEnemyDataBase::GetInstance()->GetActivityFunc(CEnemyDataBase::EActivityPattern::PATTERN_GROUND_KEEP_DISTANCE));

	m_collision = CCollisionCylinder::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10.0f, 10.0f);
	m_collision->SetParent(&m_pos);
	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CEnemy::Uninit()
{
	// 終了処理
	CCharacter::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CEnemy::Update()
{
#ifdef ENEMY_DEBUG
	CDebugProc::Print("Enemy：move1(%f,%f,%f)\n", m_move.x, m_move.y, m_move.z);
#endif // _DEBUG

	// 現在のactivityに設定する。
	m_Activity(this);

#ifdef ENEMY_DEBUG
	CDebugProc::Print("Enemy：move2(%f,%f,%f)\n", m_move.x, m_move.y, m_move.z);
#endif // _DEBUG

	// 更新処理
	CCharacter::Update();

#ifdef ENEMY_DEBUG
	CDebugProc::Print("Enemy：move3(%f,%f,%f)\n", m_move.x, m_move.y, m_move.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CEnemy::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy* pEnemy;
	pEnemy = new CEnemy(CObject::ENEMY);
	pEnemy->SetPos(pos);
	pEnemy->SetSize(size);
	pEnemy->Init();

	return pEnemy;
}

//--------------------------------------------------------------
// 移動
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