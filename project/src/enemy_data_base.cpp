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
#include "abnormal_data_base.h"
#include "abnormal.h"
#include "enemy.h"
#include "bullet.h"
#include "melee_attack.h"

#include "skill.h"

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
	//--------------------------------------------------------------
	// 空中から近寄る
	//--------------------------------------------------------------
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
	//--------------------------------------------------------------
	// 空中から一定の距離を稼ぐ
	//--------------------------------------------------------------
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
	//--------------------------------------------------------------
	// 地上から近寄る
	//--------------------------------------------------------------
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
	//--------------------------------------------------------------
	// 地上から一定の距離を稼ぐ
	//--------------------------------------------------------------
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
	//--------------------------------------------------------------
	// 地上から近寄って攻撃
	//--------------------------------------------------------------
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

		inEnemy->AddAttackCnt(1);

		// 近づいた時
		if (distance <= 50.0f)
		{
			if (inEnemy->GetAttackCnt() >= 120)
			{
				// 近接攻撃
				CMeleeAttack::Create(D3DXVECTOR3(inEnemy->GetPos().x, inEnemy->GetPos().y, inEnemy->GetPos().z));
				inEnemy->SetAttackCnt(0);
				move *= -0.5f;
			}
		}

		inEnemy->SetMoveXZ(move.x, move.z);
	};
	//--------------------------------------------------------------
	// ゴーレムの動き
	//--------------------------------------------------------------
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
				inEnemy->GetSkill()[0]->Skill();
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

	//--------------------------------------------------------------
	// 九尾の動き
	//--------------------------------------------------------------
	//* 弾を飛ばす */
	m_activityFunc[PATTERN_NINEFOX_BLAST] = [](CEnemy* inEnemy)
	{

	};

	EEnemyType type;

	//--------------------------------------------------------------
	// エネミーの職ステータスを設定
	//--------------------------------------------------------------
	{// 骸骨
		type = SKELTON;
		m_status[type].s_hp = 100;
		m_status[type].s_attack = 1;
		m_status[type].s_size = 50.0f;
		m_status[type].s_collisionLength = 10.0f;
		m_status[type].s_collisionHeight = 50.0f;
		m_status[type].s_modelKey = "SKE";
	}

	{// 九尾
		type = NINE_FOX;
		m_status[type].s_hp = 1000;
		m_status[type].s_attack = 1;
		m_status[type].s_size = 150.0f;
		m_status[type].s_collisionLength = 100.0f;
		m_status[type].s_collisionHeight = 150.0f;
		m_status[type].s_modelKey = "NINE_FOX";
	}
}
