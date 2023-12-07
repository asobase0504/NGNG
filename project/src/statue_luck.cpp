//**************************************************************
//
// 運の祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_luck.h"
#include "player_manager.h"
#include "item_manager.h"
#include "input.h"
#include "utility.h"

namespace
{
std::array<float, CItemDataBase::RARITY_MAX> rate = { 0.05f,0.1f,0.2f,0.65f };
};

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueLuck::CStatueLuck()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueLuck::~CStatueLuck()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueLuck::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos,rot);
	LoadModel("STATUE_LUCK");

	m_nUseMoney = 10;
	m_nItemCount = 0;
	m_uiText = "運を試す [$" + std::to_string(m_nUseMoney) + "]";

	return S_OK;
}

bool CStatueLuck::Select(CCharacter * selectCharacter)
{
	CStatus<int>* money = selectCharacter->GetMoney();

	if (money->GetCurrent() < m_nUseMoney)
	{
		return false;
	}

	// プレイヤーお金を調整して設定
	money->AddCurrent(-m_nUseMoney);

	D3DXVECTOR3 pos(m_pos.x, m_pos.y + 30.0f, m_pos.z);
	int answer = CItemManager::GetInstance()->CreateRandomItemRarityRate(pos, GetMtxRot(), rate);

	switch (answer)
	{
	case 0:	// レア
	case 1:	// アンコモン
	case 2:	// コモン
		m_nItemCount++;
		break;
	case 3:	// ハズレ
		break;
	default:
		assert(false);
		break;
	}

	// 次回ガチャする時用に必要お金数を増やして設定しておく
	int randomNumber = rand() % 10;
	m_nUseMoney += randomNumber;

	m_uiText = "運を試す [$" + std::to_string(m_nUseMoney) + "]";

	if (m_nItemCount >= 2)
	{
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;
	}

	return true;
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueLuck* CStatueLuck::Create(D3DXVECTOR3 pos)
{
	CStatueLuck* pStatuechest;
	pStatuechest = new CStatueLuck;
	pStatuechest->SetPos(pos);
	pStatuechest->Init();

	return pStatuechest;
}