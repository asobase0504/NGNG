//**************************************************************
//
// 血の祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_blood.h"
#include "statue_manager.h"
#include "player_manager.h"
#include "input.h"
#include "map.h"
#include "collision_mesh.h"
#include "collision_box.h"
#include "object_mesh.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueBlood::CStatueBlood(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueBlood::~CStatueBlood()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueBlood::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos, rot);
	LoadModel("STATUE_BLOOD");
	m_bOnce = false;

	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueBlood::Update()
{
	// プレイヤー情報取得
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	CStatus<int>* playerHp = pPlayer->GetHp();
	CStatus<int>* playerMoney = pPlayer->GetMoney();

	// プレイヤーが触れている時
	if (Touch())
	{
		if (!m_bOnce)
		{
			// プレイヤーのHPとお金を調整して設定
			playerHp->AddCurrent(-10);
			playerMoney->AddCurrent(10);

			m_bOnce = true;
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
	CDebugProc::Print("BloodPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // 0
#endif // _DEBUG
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueBlood* CStatueBlood::Create(D3DXVECTOR3 pos)
{
	CStatueBlood* pStatueblood;
	pStatueblood = new CStatueBlood;
	pStatueblood->SetPos(pos);
	pStatueblood->Init();

	return pStatueblood;
}