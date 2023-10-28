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

#include "application.h"
#include "objectX.h"
#include "object_mesh.h"

#include "collision_cylinder.h"
#include "collision_mesh.h"
#include "utility.h"

#include "enemy.h"
#include "Controller.h"
#include "skill.h"
#include "skill_data_base.h"
#include "item.h"
#include "item_data_base.h"
#include "map.h"
#include "map_model.h"
#include "statue.h"
#include "statue_manager.h"
#include "enemy_manager.h"
#include "player_manager.h"

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

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		// スキルを生成
		m_Skill[nCnt] = CSkill::Create();
		// intをstring型に変換する
		std::ostringstream  name;
		name << "YAMATO_SKILL_" << nCnt+1;
		// スキルの設定
		m_Skill[nCnt]->SetSkill(name.str(), this);
	}

	// モデルの読み込み
	m_apModel[0]->LoadModel("PLAYER01");
	m_apModel[0]->CalculationVtx();

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	m_collision.push_back(CCollisionCylinder::Create(pos, 10.0f, 10.0f));

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

	CMap* map = CMap::GetMap();
	D3DXVECTOR3 pos = GetPos();

	for (int i = 0; i < map->GetNumModel(); i++)
	{
		if (m_collision[0]->ToBox(map->GetMapModel(i)->GetCollisionBox(), true))
		{// 押し出した位置
			D3DXVECTOR3 extrusion = ((CCollisionCylinder*)m_collision[0])->GetExtrusion();
			SetPos(D3DXVECTOR3(extrusion));
			m_collision[0]->SetPos(D3DXVECTOR3(extrusion));
		//	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	for (int i = 0; i < map->GetNumMesh(); i++)
	{
		if (m_collision[0]->ToMesh(map->GetMapMesh(i)->GetCollisionMesh()))
		{// 押し出した位置
			float extrusion = ((CCollisionCylinder*)m_collision[0])->GetExtrusionHeight();
			SetPos(D3DXVECTOR3(pos.x, extrusion, pos.z));
			m_collision[0]->SetPos(D3DXVECTOR3(pos.x, extrusion, pos.z));
		//	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	DEBUG_PRINT("pos3 : %f, %f, %f\n", pos.x, pos.y, pos.z);

#ifdef _DEBUG
	CDebugProc::Print("Player : pos(%f, %f, %f)\n", GetPos().x, GetPos().y, GetPos().z);
	CDebugProc::Print("Player : move(%f, %f, %f)\n", move.x, move.y, move.z);
	CDebugProc::Print("PlayerCollision : pos(%f, %f, %f)\n", m_collision[0]->GetPos().x, m_collision[0]->GetPos().y, m_collision[0]->GetPos().z);
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
		// 発動時に生成
    m_Skill[0]->Skill1();
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
	CItem::ITEM_FUNC itemFunc = CItemDataBase::GetInstance()->GetItemData((CItemDataBase::EItemType)id)->GetWhenPickFunc();

	if (itemFunc != nullptr)
	{
		itemFunc(this, m_haveItem[id]);
	}
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
void CPlayer::SetPos(const D3DXVECTOR3& inPos)
{
	if (m_collision.size() > 0)
	{
		if (m_collision[0] != nullptr)
		{
			m_collision[0]->SetPos(inPos);
		}
	}
	CCharacter::SetPos(inPos);
}
