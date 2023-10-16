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
	m_activityFunc[PATTERN_GO] = [](CEnemy* inEnemy)
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
}
