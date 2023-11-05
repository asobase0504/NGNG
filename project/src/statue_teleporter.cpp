//**************************************************************
//
// テレポーターの祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_teleporter.h"
#include "statue_manager.h"
#include "player_manager.h"
#include "input.h"
#include "map.h"
#include "collision_mesh.h"
#include "collision_box.h"
#include "object_mesh.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "utility.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueTeleporter::CStatueTeleporter(int nPriority)
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueTeleporter::~CStatueTeleporter()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CStatueTeleporter::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	m_time = 0;

	CStatue::Init(pos, rot);
	m_bOnce = false;
	m_btimeAdd = false;

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CStatueTeleporter::Uninit()
{
	// 終了処理
	CStatue::Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CStatueTeleporter::Update()
{
	// 情報取得
	CInput* input = CInput::GetKey();
	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetPlayer();

	// プレイヤーが触れている時
	if (Touch(pPlayer))
	{
		if (input->Trigger(KEY_BACK, -1))
		{// プレイヤーが特定のキーを押したとき
			if (!m_bOnce)
			{
				float randX = FloatRandom(1.5f, 0.5f);
				float randZ = FloatRandom(1.5f, 0.5f);

				m_pEnemy = CEnemyManager::GetInstance()->CreateEnemy(D3DXVECTOR3(randX, 0.0f, randZ), D3DXVECTOR3(50.0f, 50.0f, 50.0f), CEnemyManager::NONE);

				CStatus<int>* enemyHp = m_pEnemy->GetHp();
				enemyHp->SetCurrent(0);
				m_bOnce = true;
			}

			m_btimeAdd = true;
		}
	}

	if (m_bOnce)
	{
		if ((m_pEnemy->IsDied()) && (m_time >= MAX_TIME))
		{
			//-------------------------
			// マップ移動処理追加
			//-------------------------
		}
	}

	if (m_btimeAdd)
	{
		// 時間追加
		m_time++;
	}

	// 更新処理
	CStatue::Update();

#ifdef _DEBUG
	CDebugProc::Print("BloodPos(%f,%f,%f)\n", GetPos().x, GetPos().y, GetPos().z);
#endif // _DEBUG
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CStatueTeleporter::Draw(void)
{
	// 描画処理
	CStatue::Draw();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueTeleporter* CStatueTeleporter::Create(D3DXVECTOR3 pos)
{
	CStatueTeleporter* pStatueteleporter;
	pStatueteleporter = new CStatueTeleporter;
	pStatueteleporter->SetPos(pos);
	pStatueteleporter->Init();

	return pStatueteleporter;
}