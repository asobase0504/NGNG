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
#include "collision_cylinder.h"
#include "collision_box.h"

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

	return S_OK;
}

//--------------------------------------------------------------
// 選択時
//--------------------------------------------------------------
bool CStatueChest::Select(CCharacter * selectCharacter)
{
	CStatus<int>* money = selectCharacter->GetMoney();

	// お金が足りないなら支払いができない
	if (money->GetCurrent() < 10)
	{
		return false;
	}

	// プレイヤーお金を調整して設定
	money->AddCurrent(-10);

	//-------------------------------------------------------------------------------
	// アイテムランダムドロップ関数追加
	//---------------------------------------------------------------------------------
	D3DXVECTOR3 pos = GetPos();
	CItemManager::GetInstance()->CreateRandomItemRarityRate(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), GetMtxRot(), { 0.7f,0.25,0.5f,0.0f });
	//CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), GetMtxRot(), CItemDataBase::EItemType::ITEM_DANGO);

	m_collisionCylinder->Uninit();
	m_collisionCylinder = nullptr;

	return true;
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