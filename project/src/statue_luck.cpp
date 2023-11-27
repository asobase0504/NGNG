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

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueLuck::CStatueLuck(int nPriority)
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

	m_bOnce = false;
	m_bChance = false;
	m_nUseMoney = 10;
	m_nItemCount = 0;

	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueLuck::Update()
{
	// プレイヤー情報取得
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerMoney = pPlayer->GetMoney();

	// プレイヤーが触れている時
	
	if (Touch())
	{
		if (m_nItemCount < 2)
		{
			// プレイヤーお金を調整して設定
			playerMoney->AddCurrent(-m_nUseMoney);

			// アイテム確率計算
			int randomCount = IntRandom(100, 1);

			int answer = CItemManager::GetInstance()->CreateRandomItemRarityRate(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), GetMtxRot(),{ 0.05f,0.1f,0.2f,0.65f });

			switch (answer)
			{
			case 0:	// レア
				m_nItemCount++;
				break;
			case 1:	// アンコモン
				m_nItemCount++;
				break;
			case 2:	// コモン
				m_nItemCount++;
				break;
			case 3:	// ハズレ
				break;
			default:
				break;
			}

			// 次回ガチャする時用に必要お金数を増やして設定しておく
			int randomNumber = rand() % 10;
			m_nUseMoney += randomNumber;

			m_bOnce = true;
		}
	}

	// 更新処理
	CStatue::Update();

#ifdef _DEBUG
#if 0
	CDebugProc::Print("LuckPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // 0
#endif // _DEBUG
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