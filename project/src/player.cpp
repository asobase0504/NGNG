//**************************************************************
//
// プレイヤー
// Author : 髙野馨將
//
//**************************************************************

// include
#include "player.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_cylinder.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// 初期化処理
	CCharacter::Init();

	// モデルの読み込み
	m_apModel[0]->LoadModel("PLAYER01");
	m_apModel[0]->CalculationVtx();

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	m_collisionCyinder = CCollisionCyinder::Create(pos, 10.0f, 50.0f);
	m_collision.push_back(m_collisionCyinder);

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CPlayer::Uninit()
{
	// コントローラーの破棄
	if (m_controller != nullptr)
	{
		delete m_controller;
		m_controller = nullptr;
	}

	m_collisionCyinder->Uninit();

	// 終了処理
	CCharacter::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CPlayer::Update()
{
	// 移動量の取得
	D3DXVECTOR3 move = GetMove();
	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	if (m_controller == nullptr)
	{
		return;
	}

	// 移動
	Move();

	// ジャンプ
	Jump();

	// ダッシュ
	Dash();

	m_controller->TakeItem();
	
	bool a = m_collisionCyinder->ToBox(CEnemyManager::GetInstance()->GetEnemyBox(),true);
	m_collisionCyinder->SetPos(pos);

	if (a)
	{
		//D3DXVECTOR3 pos = GetPos();
		//SetPos(D3DXVECTOR3(m_collisionCyinder->GetExtrusion().x, pos.y, pos.z));
		//m_collisionCyinder->SetPos(D3DXVECTOR3(m_collisionCyinder->GetExtrusion().x, pos.y, pos.z));
	}

	// 更新処理
	CCharacter::Update();

#ifdef _DEBUG
	CDebugProc::Print("Player：pos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	CDebugProc::Print("Player：move(%f,%f,%f)\n", move.x, move.y, move.z);
	CDebugProc::Print("PlayerCollision：pos(%f,%f,%f)\n", m_collisionCyinder->GetPos().x, m_collisionCyinder->GetPos().y, m_collisionCyinder->GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer;
	pPlayer = new CPlayer(CObject::PLAYER);
	pPlayer->SetPos(pos);
	pPlayer->Init();

	return pPlayer;
}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
void CPlayer::Move()
{
	// 移動量
	SetMove(m_controller->Move());
}

//--------------------------------------------------------------
// ジャンプ
//--------------------------------------------------------------
void CPlayer::Jump()
{
	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	// ジャンプ
	bool jump = m_controller->Jump();

	if (jump && !m_jumpCount.MaxCurrentSame())
	{
 		m_jumpCount.AddCurrent(1);

		// ジャンプ力
		move.y += m_jumpPower.GetCurrent();
	}
	else
	{
		if (!(GetPos().y > 0.0f))
		{
			m_jumpCount.SetCurrent(0);
		}
	}

	if (GetPos().y > 0.0f)
	{
		// 重力
		move.y -= 0.175f;
	}

	// 移動量の設定
	SetMove(move);
}

//--------------------------------------------------------------
// ダッシュ
//--------------------------------------------------------------
void CPlayer::Dash()
{
	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	// ダッシュ
	m_isdash = m_controller->Dash();

	if (m_isdash)
	{
		// ダッシュ速度
		move.x *= DASH_SPEED;
		move.z *= DASH_SPEED;
	}

	// 移動量の設定
	SetMove(move);
}

//--------------------------------------------------------------
// コントローラーの設定
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}