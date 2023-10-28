//**************************************************************
//
// 戦いの祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_combat.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "input.h"
#include "utility.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueCombat::CStatueCombat(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueCombat::~CStatueCombat()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueCombat::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	CStatue::Init(pos, rot);

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CStatueCombat::Uninit()
{
	// 終了処理
	CStatue::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueCombat::Update()
{
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();
	D3DXVECTOR3 pos = GetPos();

	// プレイヤーが触れている時
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// プレイヤーが特定のキーを押したとき
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				// 敵の生成
				float randX = FloatRandom(1.5f, 0.5f);
				float randZ = FloatRandom(1.5f, 0.5f);

				CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(pos.x * randX,pos.y,pos.z * randZ),D3DXVECTOR3(50.0f,50.0f,50.0f), CEnemyManager::NONE);
			}
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
void CStatueCombat::Draw(void)
{
	// 描画処理
	CStatue::Draw();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueCombat* CStatueCombat::Create(D3DXVECTOR3 pos)
{
	CStatueCombat* pStatuecombat;
	pStatuecombat = new CStatueCombat;
	pStatuecombat->SetPos(pos);
	pStatuecombat->Init();

	return pStatuecombat;
}