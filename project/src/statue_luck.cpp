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
// 終了処理
//--------------------------------------------------------------
void CStatueLuck::Uninit()
{
	// 終了処理
	CStatue::Uninit();
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
	
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// プレイヤーが特定のキーを押したとき
			if (!m_bOnce)
			{
				if (m_nItemCount < 2)
				{
					// プレイヤーお金を調整して設定
					playerMoney->AddCurrent(-m_nUseMoney);

					// アイテム確率計算
					int randomCount = IntRandom(100, 1);

					if (randomCount <= 4)
					{// レア

					//--------------------------
					//  アイテムドロップ関数
					//--------------------------

						m_nItemCount++;
					}
					else if (randomCount >= 5 && randomCount <= 12)
					{// アンコモン

					 //--------------------------
					 //  アイテムドロップ関数
					 //--------------------------

						m_nItemCount++;
					}
					else if (randomCount >= 13 && randomCount <= 39)
					{// コモン

					 //--------------------------
					 //  アイテムドロップ関数
					 //--------------------------

						m_nItemCount++;
					}
					else
					{// ハズレ

					}

					// 次回ガチャする時用に必要お金数を増やして設定しておく
					int randomNumber = rand() % 10;
					m_nUseMoney += randomNumber;

					m_bOnce = true;
				}
			}
		}
		else
		{
			m_bOnce = false;
			m_bChance = false;
		}
	}

	// 更新処理
	CStatue::Update();

#ifdef _DEBUG
	CDebugProc::Print("LuckPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CStatueLuck::Draw(void)
{
	// 描画処理
	CStatue::Draw();
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