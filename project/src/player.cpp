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
#include "utility.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{
	m_collisionCyinder = nullptr;
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

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	m_collisionCyinder = CCollisionCyinder::Create(pos,5.0f, 50.0f);

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

	if (m_controller == nullptr)
	{
		return;
	}


	// 移動
	Move();

	// 更新処理
	CCharacter::Update();

	// ジャンプ
	Jump();

	// ダッシュ
	Dash();
	
	DEBUG_PRINT("pos1 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);

	if (m_collisionCyinder->ToBox(CEnemyManager::GetInstance()->GetEnemyBox(), true))
	{
		// 押し出した位置
		D3DXVECTOR3 extrusion = m_collisionCyinder->GetExtrusion();
		SetPos(D3DXVECTOR3(extrusion));
		m_collisionCyinder->SetPos(D3DXVECTOR3(extrusion));
		DEBUG_PRINT("pos2 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	DEBUG_PRINT("pos3 : %f, %f, %f\n", GetPos().x, GetPos().y, GetPos().z);

#ifdef _DEBUG
	CDebugProc::Print("Player：pos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
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

void CPlayer::SetPos(const D3DXVECTOR3 & inPos)
{
	if (m_collisionCyinder != nullptr)
	{
		m_collisionCyinder->SetPos(inPos);
	}

	std::vector<CObjectX*> objectX = GetModel();
	if (objectX.size() > 0)
	{
		GetModel()[0]->SetPos(inPos);
	}

	CCharacter::SetPos(inPos);
}
