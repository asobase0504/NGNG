//**************************************************************
//
// 骸骨
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "skelton.h"
#include "collision_cylinder.h"
#include "model_skin.h"
#include "skill.h"
#include "player_manager.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CSkelton::CSkelton()
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CSkelton::~CSkelton()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CSkelton::Init()
{
	CEnemy::Init();

	// モデル
	m_skinModel->Load("SKE");

	m_size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// 当たり判定
	m_collision->SetHeight(50.0f);
	m_collision->SetLength(10.0f);

	// ステータス
	m_attack.SetCurrent(1);
	m_hp.SetCurrent(100);
	m_hp.AddMax(100);
	m_movePower.Init(1.0f);
	m_movePower.SetCurrent(1.0f);


	// SKILLの作成
	m_skill.push_back(CSkill::Create());
	m_skill[0]->SetSkill("GOLEM_SKILL_1", this);
	SetEndChildren(m_skill[0]);

	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CSkelton::Update()
{
	CEnemy::Update();

	// プレイヤーの位置取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
	D3DXVECTOR3 distancePos = (PlayerPos - pos);
	float distance = D3DXVec3Length(&distancePos);

	// カウント開始
	AddAttackCnt(1);

	// エネミーの距離が遠いとき
	if (distance >= 150.0f)
	{
		if (GetAttackCnt() >= 180)
		{
			// カウント開始
			SetAttackCnt(0);
			GetSkill()[0]->Skill();
		}
	}
}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
void CSkelton::Move()
{
	// 移動量の取得
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	// プレイヤーの位置取得
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

	D3DXVECTOR3 distancePos = (PlayerPos - pos);

	distancePos.y = 0.0f;

	D3DXVec3Normalize(&distancePos,&distancePos);

	distancePos *= m_movePower.GetCurrent();

	SetMoveXZ(distancePos.x, distancePos.z);
}
