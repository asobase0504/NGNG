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
void CPlayer::Uninit(void)
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
void CPlayer::Update(void)
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
	m_collisionCyinder->SetPos(pos);
	//bool a = m_collisionCyinder->ToSphere(CEnemyManager::GetInstance()->GetEnemySphere());

	//if (a)
	{
		int b = 0;
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
// 描画処理
//--------------------------------------------------------------
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
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

	bool jump = false;

	// ジャンプ
	jump = m_controller->Jump();

	if (jump)
	{
		// ジャンプ力
		move.y += 25.0f;
		jump = false;
	}

	if (GetPos().y > 0.0f)
	{
		// 重力
		move.y -= 1.0f;
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