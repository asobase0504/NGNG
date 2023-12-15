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
#include "player_manager.h"
#include "Controller.h"
#include "utility.h"

// 全体情報
#include "game.h"
#include "camera_game.h"
#include "application.h"
#include "result.h"
#include "map.h"

// 見た目
#include "objectX.h"

// スキル
#include "skill.h"
#include "skill_data_base.h"

// アイテム
#include "item.h"
#include "item_data_base.h"
#include "item_manager.h"

#include "select_entity.h"

#include "take_item_ui.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CPlayer::CPlayer(int nPriority) :
	m_isResult(false)
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
	m_skill.resize(MAX_SKILL);

	m_isdash = false;
	m_isUpdate = true;
	// 初期化処理
	CCharacter::Init();

	// 友好状態
	m_relation = ERelation::FRIENDLY;
	m_isUpdate = true;

	for (int nCnt = 0; nCnt < MAX_SKILL; nCnt++)
	{
		// スキルを生成
		m_skill[nCnt] = CSkill::Create();
		// intをstring型に変換する
		std::ostringstream  name;
		name << "YAMATO_SKILL_" << nCnt+1;
		// スキルの設定
		m_skill[nCnt]->SetSkill(name.str(), this);
		SetEndChildren(m_skill[nCnt]);
	}

	// モデルの読み込み
	m_apModel[0]->LoadModel("PLAYER01");
	m_apModel[0]->CalculationVtx();

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	// 当たり判定
	m_collision = CCollisionCylinder::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10.0f, 55.0f);
	m_collision->SetParent(&m_pos);

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
	if (!m_isUpdate)
	{
		return;
	}
	
	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	if (m_controller == nullptr)
	{
		return;
	}

	if (!m_isStun && !IsDied())
	{
		// 選択
		Select();
		// 移動
		Move();

		// ジャンプ
		Jump();

		// ダッシュ
		Dash();

		// 攻撃
		PAttack();
	}
	else
	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if (IsDied() && !m_isResult)
	{
		m_isResult = true;
		CResult::Create();
	}

	// 更新処理
	CCharacter::Update();

#ifdef _DEBUG
	CDebugProc::Print("Player : pos(%f, %f, %f)\n", GetPos().x, GetPos().y, GetPos().z);
	CDebugProc::Print("Player : move(%f, %f, %f)\n", move.x, move.y, move.z);
	CDebugProc::Print("PlayerCollision : pos(%f, %f, %f)\n", m_collision->GetPosWorld().x, m_collision->GetPosWorld().y, m_collision->GetPosWorld().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();
	pPlayer->SetPos(pos);
	return pPlayer;
}

//--------------------------------------------------------------
// 攻撃
//--------------------------------------------------------------
void CPlayer::PAttack()
{
	bool isSuccess = false;

	// 通常攻撃(左クリック)
	if (m_controller->Skill_1())
	{
		// 発動時に生成
		isSuccess = m_skill[0]->Skill();
	}

	// スキル1(右クリック)
	if(m_controller->Skill_2())
	{
		// 発動時に生成
		isSuccess = m_skill[2]->Skill();
	}

	// スキル2(シフト)
	if (m_controller->Skill_3())
	{
		// 発動時に生成
		isSuccess = m_skill[1]->Skill();
	}

	// スキル3(R)
	if (m_controller->Skill_4())
	{
		// 発動時に生成
		isSuccess = m_skill[3]->Skill();
	}

	if (isSuccess)
	{
		m_isdash = false;
	}
}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
void CPlayer::Move()
{
	// 移動量
	D3DXVECTOR3 move = m_controller->Move();

	m_isskill = false;

	if (m_isMoveLock)
	{
		SetMove(D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	if (m_isMoveLock)
	{
		return;
	}

	if (D3DXVec3Length(&move) != 0.0f)
	{
		if (!m_isControl)
		{
			SetMoveXZ(move.x, move.z);

			// カメラの方向に合わせる
			D3DXVECTOR3 cameraVec = GetMove();
			cameraVec.y = 0.0f;
			cameraVec = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera()->VectorCombinedRot(cameraVec);
			cameraVec *= m_movePower.GetCurrent();
			if (m_isdash)
			{
				cameraVec *= m_dashPower.GetCurrent();
			}
			CDebugProc::Print("Player : cameraVec(%f, %f, %f)\n", cameraVec.x, cameraVec.y, cameraVec.z);
			SetMoveXZ(cameraVec.x, cameraVec.z);
		}
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
	// ジャンプ
	bool jump = m_controller->Jump();

	if (jump && !m_jumpCount.MaxCurrentSame())
	{
 		m_jumpCount.AddCurrent(1);

		// ジャンプ力
		SetMoveY(m_jumpPower.GetCurrent());
		m_state = SKY;
	}
}

//--------------------------------------------------------------
// ダッシュ
//--------------------------------------------------------------
void CPlayer::Dash()
{
	// 移動量の取得
	D3DXVECTOR3 move = GetMove();

	// ダッシュ(ctrlを押すとダッシュと歩きを切り替える)
	m_isdash = m_controller->Dash(m_isdash);

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
void CPlayer::TakeItem(int id)
{
	m_haveItem[id]++;
	CItem::ITEM_FUNC itemFunc = CItemDataBase::GetInstance()->GetItemData((CItemDataBase::EItemType)id)->GetWhenPickFunc();

	CTakeItemUI* ui = new CTakeItemUI;
	ui->Init();
	ui->SetTakeItem((CItemDataBase::EItemType)id);

	if (itemFunc != nullptr)
	{
		itemFunc(this, m_haveItem[id]);
	}
}

//--------------------------------------------------------------
// 選ぶ
//--------------------------------------------------------------
void CPlayer::Select()
{
	CMap* map = CMap::GetMap();

	std::list<CSelectEntity*> list = map->GetSelectEntityList();

	CSelectEntity* nearEntity;
	float nearLength = FLT_MAX;

	for (CSelectEntity* entity : list)
	{
		entity->NoDisplayUI();

		if (entity->GetSelectCollision() == nullptr)
		{
			continue;
		}

		D3DXVECTOR3 diffPos = m_pos - entity->GetPos();
		float diff = D3DXVec3Length(&diffPos);
		if (nearLength > diff)
		{
			nearLength = diff;
			nearEntity = entity;
		}
	}

	if (nearEntity->GetSelectCollision()->ToCylinder(GetCollision()))
	{
		nearEntity->DisplayUI();

		if (m_controller->Select())
		{
			nearEntity->Select(this);
		}
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
	CCharacter::SetPos(inPos);
}
