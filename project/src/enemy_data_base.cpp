//**************************************************************
//
// エネミーデータベース
// Author : YudaKaito
//
//**************************************************************
//==============================================================
// include
//==============================================================
#include "enemy_data_base.h"
#include "enemy.h"
#include "bullet.h"
#include "melee_attack.h"

//行動パターンに必要なinclude
#include "player_manager.h"

// マクロ定義
#define UPDATE_FUNC_CAST(func) (static_cast<void(CEnemyDataBase::*)()>(&(func)))

//==============================================================
// 静的メンバー変数の宣言
//==============================================================
CEnemyDataBase* CEnemyDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CEnemyDataBase::CEnemyDataBase()
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CEnemyDataBase::~CEnemyDataBase()
{
}

//--------------------------------------------------------------
// インスタンスの取得
//--------------------------------------------------------------
CEnemyDataBase* CEnemyDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CEnemyDataBase;

		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CEnemyDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
void CEnemyDataBase::Init()
{
	m_activityFunc.resize(MAX_PATTERN);

	// 空中から近寄る
	m_activityFunc[PATTERN_AIR_GO] = [](CEnemy* inEnemy)
	{
		// 移動量の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 座標の取得
		D3DXVECTOR3 pos = inEnemy->GetPos();

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

		inEnemy->SetMove(move);
	};

	// 空中から一定の距離を稼ぐ
	m_activityFunc[PATTERN_AIR_KEEP_DISTANCE] = [](CEnemy* inEnemy)
	{
		// 移動量の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 座標の取得
		D3DXVECTOR3 pos = inEnemy->GetPos();

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

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		if (distance <= 150.0f)
		{
			move *= -0.5f;
		}

		inEnemy->SetMove(move);
	};

	// 地上から近寄る
	m_activityFunc[PATTERN_GROUND_GO] = [](CEnemy* inEnemy)
	{
		// 移動量の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 座標の取得
		D3DXVECTOR3 pos = inEnemy->GetPos();

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

		inEnemy->SetMove(move);
	};

	// 地上から一定の距離を稼ぐ
	m_activityFunc[PATTERN_GROUND_KEEP_DISTANCE] = [](CEnemy* inEnemy)
	{
		// 移動量の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 座標の取得
		D3DXVECTOR3 pos = inEnemy->GetPos();

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

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		// 近づきたすぎた時
		if (distance <= 150.0f)
		{
			move *= -0.5f;
		}

		inEnemy->SetMoveXZ(move.x, move.z);
	};

	// 地上から近寄って攻撃
	m_activityFunc[PATTERN_GROUND_GO_ATTACK] = [](CEnemy* inEnemy)
	{
		// 移動量の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 座標の取得
		D3DXVECTOR3 pos = inEnemy->GetPos();

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

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		inEnemy->SetAttackCnt(1);

		// 近づいた時
		if (distance <= 150.0f)
		{
			if (inEnemy->GetAttackCnt() >= 120)
			{
				// 近接攻撃
				CMeleeAttack::Create(inEnemy->GetPos());
				inEnemy->SetAttackCnt(0);
				move *= -0.5f;
			}
		}

		inEnemy->SetMoveXZ(move.x, move.z);
	};

	// ゴーレムの動き
	// ゴーレムのレーザーを止める処理
	m_activityFunc[PATTERN_GOLEM] = [](CEnemy* inEnemy)
	{
		// 移動量の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 座標の取得
		D3DXVECTOR3 pos = inEnemy->GetPos();

		// プレイヤーの位置取得
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

		D3DXVECTOR3 distancePos = (PlayerPos - pos);
		float distance = D3DXVec3Length(&distancePos);

		// カウント開始
		inEnemy->AddAttackCnt(1);

		// エネミーの距離が遠いとき
		if (distance >= 150.0f )
		{
			if (inEnemy->GetAttackCnt() >= 180)
			{
				// カウント開始
				inEnemy->SetAttackCnt(0);
				inEnemy->SetActivity(GetInstance()->GetActivityFunc(PATTERN_GOLEM_LASER));
				move *= -0.5f;
			}
		}

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

		inEnemy->SetMoveXZ(move.x,move.z);
	};

	// ゴーレムのレーザーを打つ処理
	m_activityFunc[PATTERN_GOLEM_LASER] = [](CEnemy* inEnemy)
	{
		// プレイヤーの獲得
		CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();

		// 目標の設定
		inEnemy->GetRoad()->SetShooter(inEnemy);
		inEnemy->GetRoad()->SetTarget(pPlayer);
		inEnemy->GetRoad()->SetUse(true);

		// カウント開始
		inEnemy->AddAttackCnt(1);

		//--------------------------------------------------------------------
		// プレイヤーの位置取得
		D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
		// 座標の取得
		D3DXVECTOR3 pos = inEnemy->GetPos();

		D3DXVECTOR3 move = PlayerPos - pos;

		//--------------------------------------------------------------------

		if (inEnemy->GetAttackCnt() >= 180)
		{
			CBullet::Create(inEnemy->GetPos(), move * 0.01f, 10.0f);
			// 一定以上の時間が経過したらレーザー発射
			inEnemy->SetActivity(GetInstance()->GetActivityFunc(PATTERN_GOLEM));
			inEnemy->SetAttackCnt(0);

			inEnemy->GetRoad()->SetUse(false);
		}
		// 狙いを定めている状態
		//if (inEnemy->GetAttackCnt() >= inEnemy->GetAttackTime())
		//{
			// 一定以上の時間が経過したらレーザー発射
			// inEnemy->SetActivity(GetInstance()->GetActivityFunc(PATTERN_GOLEM));
		//}

	};
}
