//**************************************************************
//
// プレイヤー
// Author : 髙野馨將
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "player.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "Controller.h"
#include "application.h"
#include "objectX.h"
#include "collision_cylinder.h"
#include "utility.h"
//#include "skill.h"

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

	// 攻撃
	Attack();
	
	
	TakeItem();

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
// 生成
//--------------------------------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(pos);
	pPlayer->Init();

	return pPlayer;
}

//--------------------------------------------------------------
// 攻撃
//--------------------------------------------------------------
void CPlayer::Attack()
{
	// 通常攻撃(左クリック)
	if (m_controller->Skill_1())
	{
		// スキルの生成
	//	CSkill::YamatoSkill("YAMATO_SKILL_1",this);
	}

	// スキル1(右クリック)
	m_controller->Skill_2();
	
	// スキル2(シフト)
	m_controller->Skill_3();

	// スキル3(R)
	m_controller->Skill_4();
}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
void CPlayer::Move()
{
	// 移動量
	D3DXVECTOR3 move = m_controller->Move() * m_movePower.GetCurrent();

	if (D3DXVec3Length(&move) != 0.0f)
	{
		SetMoveXZ(move.x, move.z);
	}
	else
	{
		D3DXVECTOR3 nowMove = GetMove();
		AddMoveXZ(nowMove.x * -0.15f, nowMove.z * -0.15f);
	}
}

//--------------------------------------------------------------
// ジャンプ
//--------------------------------------------------------------
void CPlayer::Jump()
{
	// 移動量の取得
	D3DXVECTOR3 move(0.0f,0.0f,0.0f);

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
		move.y -= 0.18f;
	}
	else
	{
		SetMoveY(0.0f);
	}

	// 移動量の設定
	AddMove(move);
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
// アイテムの取得
//--------------------------------------------------------------
void CPlayer::TakeItem()
{
	int id = m_controller->TakeItem();

	if (id < 0)
	{
		return;
	}

	m_haveItem[id]++;
}

//--------------------------------------------------------------
// コントローラーの設定
//--------------------------------------------------------------
void CPlayer::SetController(CController * inOperate)
{
	m_controller = inOperate;
	m_controller->SetToOrder(this);
}

//--------------------------------------------------------------
// 位置の設定
//--------------------------------------------------------------
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
