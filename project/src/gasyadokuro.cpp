//**************************************************************
//
// 骸骨
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "gasyadokuro.h"
#include "collision_cylinder.h"
#include "collision_box.h"
#include "model_skin.h"
#include "skill.h"
#include "player_manager.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CGasyadokuro::CGasyadokuro()
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CGasyadokuro::~CGasyadokuro()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CGasyadokuro::Init()
{
	CEnemy::Init();

	// モデル
	m_skinModel->Load("GASYADOKURO");

	m_size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// 当たり判定
	m_collision->SetHeight(280.0f);
	m_collision->SetLength(100.0f);

	// 大きさ
	m_extrusion->SetSize(D3DXVECTOR3(40.0f, 90.0f, 40.0f));
	m_extrusion->SetPos(D3DXVECTOR3(0.0f, 70.0f, 0.0f));

	// ステータス
	m_attack.SetCurrent(1);
	m_hp.SetCurrent(100);
	m_hp.AddMax(100);
	m_movePower.Init(1.0f);
	m_movePower.SetCurrent(1.0f);

	// SKILLの作成
	m_skill.push_back(CSkill::Create());
	m_skill[0]->SetSkill("GASYADOKURO_ATTACK_SKILL", this);
	SetEndChildren(m_skill[0]);

	m_skill.push_back(CSkill::Create());
	m_skill[1]->SetSkill("SKELTON_SUMMON_SKILL", this);
	SetEndChildren(m_skill[1]);

	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CGasyadokuro::Update()
{
	CEnemy::Update();

	// プレイヤーの位置取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();
	D3DXVECTOR3 distancePos = (PlayerPos - pos);
	float distance = D3DXVec3Length(&distancePos);

	if (distance <= 170.0f)
	{
		// 叩きつけ(左)
		GetSkill()[0]->Use();
	}
	else
	{
		// どくろの召喚
		GetSkill()[1]->Use();
	}

}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
void CGasyadokuro::Move()
{
	// 移動量の取得
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	// プレイヤーの位置取得
	D3DXVECTOR3 PlayerPos = CPlayerManager::GetInstance()->GetPlayerPos();

	D3DXVECTOR3 distancePos = (PlayerPos - pos);

	distancePos.y = 0.0f;

	D3DXVec3Normalize(&distancePos, &distancePos);

	distancePos *= m_movePower.GetCurrent();

	SetMoveXZ(distancePos.x, distancePos.z);
}
