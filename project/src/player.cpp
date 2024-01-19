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
#include "model_skin.h"

// スキル
#include "skill.h"
#include "skill_data_base.h"

// アイテム
#include "item.h"
#include "item_data_base.h"
#include "item_manager.h"

#include "select_entity.h"
#include "take_item_ui.h"

/* UI系統 */
#include "hp_ui.h"
#include "money_ui.h"
#include "skill_ui.h"
#include "abnormal_2dui.h"
#include "carrying_item_group_ui.h"

/**/
#include "procedure3D.h"

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
	m_direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	m_skinModel->Load("KENGOU");

	// 親子関係の構築
	SetEndChildren(m_skinModel);

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	// 当たり判定
	m_collision = CCollisionCylinder::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), 10.0f, 55.0f);
	m_collision->SetParent(&m_pos);

	// UI作成
	CHPUI::Create(GetHp());
	CMONEYUI::Create(GetMoney());

	for (int i = 0; i < 4; i++)
	{
		CSkillUI::Create(D3DXVECTOR3(1000.0f + 57.5f * i, SCREEN_HEIGHT - 90.0f, 0.0f), GetSkill(i));
	}

	m_carringitemGroupUI = new CCarryingItemGroupUI;
	m_carringitemGroupUI->Init();

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

	// 状態異常UI
	for (CAbnormal2DUI* ui : m_abnormalUI)
	{
		if (m_haveAbnormal[ui->GetType()].s_stack <= 0)
		{
			ui->Uninit();
		}
	}
	m_abnormalUI.remove_if([this](CAbnormal2DUI* ui) {return (m_haveAbnormal[ui->GetType()].s_stack <= 0); });
	int cnt = 0;
	for (CAbnormal2DUI* ui : m_abnormalUI)
	{
		ui->SetPos(D3DXVECTOR3(80.0f + cnt * 60.0f, SCREEN_HEIGHT - 120.0f, 0.0f));
		cnt++;
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

	if (m_isControl)
	{
		return;
	}

	// 通常攻撃(左クリック)
	if (m_controller->Skill_1())
	{
		// 発動時に生成
		isSuccess = m_skill[0]->Use();
		m_nonCombat = false;
	}

	// スキル1(右クリック)
	if(m_controller->Skill_2())
	{
		// 発動時に生成
		isSuccess = m_skill[2]->Use();
		m_nonCombat = false;
	}

	// スキル2(シフト)
	if (m_controller->Skill_3())
	{
		// 発動時に生成
		isSuccess = m_skill[1]->Use();
		m_nonCombat = false;
	}

	// スキル3(R)
	if (m_controller->Skill_4())
	{
		// 発動時に生成
		isSuccess = m_skill[3]->Use();
		m_nonCombat = false;
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

	if (m_isdash)
	{
		D3DXVECTOR3 charaMove = GetMove();
		charaMove.y = 0;

		if (D3DXVec3Length(&move) == 0.0f)
		{
			m_isdash = false;
		}
	}

	if (m_isMoveLock || m_isControl)
	{
		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (m_isMoveLock)
	{
		return;
	}

	if (D3DXVec3Length(&move) != 0.0f)
	{
		if (!m_isControl)
		{
			// ダッシュ(ctrlを押すとダッシュと歩きを切り替える)
			m_isdash = m_controller->Dash(m_isdash);

			SetMoveXZ(move.x, move.z);

			// カメラの方向に合わせる
			D3DXVECTOR3 cameraVec = GetMove();
			cameraVec.y = 0.0f;
			cameraVec = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera()->VectorCombinedRot(cameraVec);
			cameraVec *= m_movePower.GetCurrent();
			if (m_isdash)
			{
				cameraVec *= m_dashPower.GetCurrent();
				m_direction = cameraVec;
			}
			CDebugProc::Print("Player : cameraVec(%f, %f, %f)\n", cameraVec.x, cameraVec.y, cameraVec.z);
			SetMoveXZ(cameraVec.x, cameraVec.z);
		}
	}
	else
	{
		if (!m_isInertiaMoveLock)
		{
			D3DXVECTOR3 nowMove = GetMove();
			AddMoveXZ(nowMove.x * -0.15f, nowMove.z * -0.15f);
		}
	}

	if (m_isAccel)
	{// 敵を倒したときの加速
		D3DXVECTOR3 moveAccel = GetMove();
		D3DXVec3Normalize(&moveAccel, &moveAccel);
		SetItemMove(moveAccel * m_acceleration);
		m_isAccel = false;
	}

	if (m_nonCombat)
	{// 非戦闘時の加速
		D3DXVECTOR3 moveBase = GetMove();
		D3DXVec3Normalize(&moveBase, &moveBase);
		SetItemMove(moveBase * m_nonComAddSpeed);
	}
}

//--------------------------------------------------------------
// ジャンプ
//--------------------------------------------------------------
void CPlayer::Jump()
{
	if (m_isMoveLock || m_isControl)
	{
		return;
	}

	// ジャンプ
	bool jump = m_controller->Jump();

	if (jump && !m_jumpCount.MaxCurrentSame())
	{
		m_jumpCount.AddCurrent(1);

		if (m_isdash)
		{	
			// 効果時間の設定
			m_effectTime = 30;
			// 方向を正規化する
			D3DXVec3Normalize(&m_direction, &m_direction);
			// 前方に進む力の設定
			m_direction *= m_forwardJumpPoewer;
			// 値を渡す
			SetItemMove(D3DXVECTOR3(m_direction.x, 0.0f, m_direction.z));
		}

		// ジャンプ力
		SetMoveY(m_jumpPower.GetCurrent());
		m_state = SKY;
	}
}

//--------------------------------------------------------------
// アイテムの取得
//--------------------------------------------------------------
void CPlayer::TakeItem(int id)
{
	CCharacter::TakeItem(id);

	CTakeItemUI* ui = new CTakeItemUI;
	ui->Init();
	ui->SetTakeItem((CItemDataBase::EItemType)id);

	m_carringitemGroupUI->CreateCarryingItemUI((CItemDataBase::EItemType)id, &m_haveItem[id]);
}

//--------------------------------------------------------------
// 状態異常の加算
//--------------------------------------------------------------
void CPlayer::AddAbnormalStack(const int id, const int cnt)
{
	if (GetAbnormalCount()[id].s_stack == 0)
	{
		m_abnormalUI.push_back(CAbnormal2DUI::Create(&m_haveAbnormal[id].s_stack, (CAbnormalDataBase::EAbnormalType)id));
		int cnt = 0;
		for (CAbnormal2DUI* ui : m_abnormalUI)
		{
			ui->SetPos(D3DXVECTOR3(80.0f + cnt * 60.0f, SCREEN_HEIGHT - 120.0f,0.0f));
			cnt++;
		}
	}

	CCharacter::AddAbnormalStack(id, cnt);
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

		if (entity->GetCostUI() != nullptr)
		{
			entity->GetCostUI()->SetDisplay(600.0f > diff);
		}

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
// 向いている向きを回転させる
//--------------------------------------------------------------
void CPlayer::RotateToFace()
{
	if (m_isToFaceRot)
	{
		CCharacter::RotateToFace();
	}
	else
	{
		SetRot(D3DXVECTOR3(0.0f,((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera()->GetRot().y,0.0f));
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
