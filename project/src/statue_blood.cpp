//**************************************************************
//
// 血の祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_blood.h"
#include "player_manager.h"
#include "input.h"

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
	CStatue::Init();

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CStatueBlood::Uninit()
{
	// 終了処理
	CStatue::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueBlood::Update()
{
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();

	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{
			int a = 0;
		}
	}

	// 更新処理
	CStatue::Update();

#ifdef _DEBUG
	//CDebugProc::Print("Enemy：pos(%f,%f,%f)\n", pos.x, pos.y, pos.z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CStatueBlood::Draw(void)
{
	// 描画処理
	CStatue::Draw();
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