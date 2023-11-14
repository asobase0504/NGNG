//**************************************************************
//
// 宝箱の祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_chest.h"
#include "player_manager.h"
#include "item_manager.h"
#include "collision_box.h"
#include "input.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueChest::CStatueChest(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueChest::~CStatueChest()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueChest::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos, rot);
	m_collisionBox->SetPos(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	m_collisionBox->SetSize(D3DXVECTOR3(2.5f, 5.0f, 2.5f));
	LoadModel("STATUE_CHEST");
	m_bOnce = false;

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CStatueChest::Uninit()
{
	// 終了処理
	CStatue::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueChest::Update()
{
	// プレイヤー情報取得
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerMoney = pPlayer->GetMoney();

	// プレイヤーが触れている時
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// プレイヤーが特定のキーを押したとき
			if (!m_bOnce)
			{
				// プレイヤーお金を調整して設定
				playerMoney->AddCurrent(-10);

				//-------------------------------------------------------------------------------
				// アイテムランダムドロップ関数追加
				//---------------------------------------------------------------------------------
				D3DXVECTOR3 pos = GetPos();
				CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), GetMtxRot(), CItemDataBase::ITEM_KIBORI);

				m_bOnce = true;
			}
		}
		else
		{
			m_bOnce = false;
		}
	}

	// 更新処理
	CStatue::Update();

#ifdef _DEBUG
#if 0
	CDebugProc::Print("ChestPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // 0
#endif // _DEBUG
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CStatueChest::Draw(void)
{
	// 描画処理
	CStatue::Draw();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueChest* CStatueChest::Create(D3DXVECTOR3 pos)
{
	CStatueChest* pStatuechest;
	pStatuechest = new CStatueChest;
	pStatuechest->SetPos(pos);
	pStatuechest->Init();

	return pStatuechest;
}