//**************************************************************
//
// 敵
// Author : 梶田大夢
//
//**************************************************************

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

	m_AttackCnt = 0;
	m_apModel[0]->LoadModel("SKELETON");
	m_apModel[0]->CalculationVtx();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 size = GetSize();
	D3DXMATRIX mtx = GetMtxWorld();

	m_Activity = (CEnemyDataBase::GetInstance()->GetActivityFunc(CEnemyDataBase::EActivityPattern::PATTERN_GOLEM_LASER));

	m_collision.push_back(CCollisionCylinder::Create(pos, 10.0f, 10.0f));

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
	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	//if (m_collisionSphere->ToMesh(CPlayerManager::GetInstance()->GetPlayerCylinder(), true))
	//{
	//	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//	D3DXVECTOR3 pos = player->GetPos();
	//	player->SetPos(D3DXVECTOR3(pos.x, m_collisionSphere->GetExtrusionHeight(), pos.z));
	//	m_collisionSphere->SetPos(D3DXVECTOR3(pos.x, m_collisionSphere->GetExtrusionHeight(), pos.z));
	//}

	// 移動処理
	//Move();

	// 更新処理
	CCharacter::Update();
	
	// 現在のactivityに設定する。
	m_Activity(this);

#ifdef _DEBUG
	//CDebugProc::Print("Enemy：pos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	//CDebugProc::Print("Enemy：move(%f,%f,%f)\n", move.x, move.y, move.z);
	//CDebugProc::Print("EnemyCollision：pos(%f,%f,%f)\n", m_collision->GetPos().x, m_collision->GetPos().y, m_collision->GetPos().z);
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

	if (pos.y <= PlayerPos.y)
	{
		move.y += MAX_SPEED;
	}
	else
	{
		move.y -= MAX_SPEED;
	}

	if (pos.z <= PlayerPos.z)
	{
		move.z += MAX_SPEED;
	}
	else
	{
		move.z -= MAX_SPEED;
	}

	SetMove(move);
}