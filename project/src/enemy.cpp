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
#include "collision_sphere.h"

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

	D3DXVECTOR3 pos = GetPos();

	m_collisionSphere = CCollisionSphere::Create(pos, 10.0f);

	m_activity.push_back(CEnemyDataBase::GetInstance()->GetActivityFunc(CEnemyDataBase::EActivityPattern::PATTERN_GROUND_KEEP_DISTANCE));

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CEnemy::Uninit()
{
	// 終了処理
	CCharacter::Uninit();

	m_collisionSphere->Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CEnemy::Update()
{
	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	m_collisionSphere->SetPos(pos);

	//if (m_collisionSphere->ToMesh(CPlayerManager::GetInstance()->GetPlayerCylinder(), true))
	//{
	//	CPlayer* player = CPlayerManager::GetInstance()->GetPlayer();
	//	D3DXVECTOR3 pos = player->GetPos();
	//	player->SetPos(D3DXVECTOR3(pos.x, m_collisionSphere->GetExtrusionHeight(), pos.z));
	//	m_collisionSphere->SetPos(D3DXVECTOR3(pos.x, m_collisionSphere->GetExtrusionHeight(), pos.z));
	//}


	// 移動処理
	Move();

	// 更新処理
	CCharacter::Update();
	
	for (int i = 0; i < m_activity.size(); i++)
	{
		m_activity[i](this);
	}

#ifdef _DEBUG
	CDebugProc::Print("Enemy：pos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("Enemy：move(%f,%f,%f)\n", move.x, move.y, move.z);
	CDebugProc::Print("EnemyCollision：pos(%f,%f,%f)\n", m_collisionSphere->GetPos().x, m_collisionSphere->GetPos().y, m_collisionSphere->GetPos().z);
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
CEnemy* CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy* pEnemy;
	pEnemy = new CEnemy(CObject::ENEMY);
	pEnemy->SetPos(pos);
	pEnemy->Init();

	return pEnemy;
}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
void CEnemy::Move()
{
}