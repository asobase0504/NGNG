﻿//**************************************************************
//
// キャラクター
// Author : 梶田大夢
//
//**************************************************************

// include
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "application.h"
#include "objectX.h"
#include "PlayerController.h"
#include "collision_sphere.h"
#include "road.h"
#include "statue_manager.h"

#include "status.h"
#include "map.h"
#include "map_model.h"
#include "object_mesh.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CCharacter::CCharacter(int nPriority) : m_haveItem{}
{
	m_apModel.clear();
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CCharacter::~CCharacter()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CCharacter::Init()
{
	CObject::Init();
	m_isDied = false;

	m_apModel.resize(1);
	m_apModel[0] = CObjectX::Create(m_pos);
	m_apModel[0]->LoadModel("BOX");
	m_road = CRoad::Create(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	m_hp.Init(100);
	m_hp.SetCurrent(50);
	m_addHp.Init(100);
	m_addHp.SetCurrent(100);
	m_addHpSubTime.Init(100);
	m_addHpSubTime.SetCurrent(100);
	m_barrier.Init(100);
	m_barrier.SetCurrent(100);
	m_barrierRePopTime.Init(100);
	m_barrierRePopTime.SetCurrent(100);
	m_attack.Init(100);
	m_attack.SetCurrent(100);
	m_attackSpeed.Init(1.0f);
	m_attackSpeed.SetCurrent(1.0f);
	m_defense.Init(100);
	m_defense.SetCurrent(100);
	m_criticalRate.Init(0.0f);
	m_criticalRate.SetCurrent(0.0f);
	m_criticalDamage.Init(2.0f);
	m_criticalDamage.SetCurrent(2.0f);
	m_movePower.Init(2.0f);
	m_movePower.SetCurrent(2.0f);
	m_jumpPower.Init(FLT_MAX);
	m_jumpPower.SetCurrent(3.0f);
	m_jumpCount.Init(1);
	m_jumpCount.SetCurrent(0);
	m_money.Init(100);
	m_money.SetCurrent(100);

	m_state = GROUND;

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CCharacter::Uninit(void)
{
	// 破棄処理
	CObject::Release();

	m_apModel[0]->Uninit();
	m_collision->Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CCharacter::Update(void)
{
	// 更新処理
	CObject::Update();

	bool isGround = false;

	CStatueManager::GetInstance()->AllFuncStatue([this, &isGround](CStatue* inSattue)
	{
		if (m_collision->ToBox(inSattue->GetCollisionBox(), true))
		{
			D3DXVECTOR3 extrusion = m_collision->GetPosWorld();
			SetPos(extrusion);
			SetMoveXZ(0.0f,0.0f);

			if (m_collision->GetIsTop())
			{
				isGround = true;
			}
		}
	});

	CMap* map = CMap::GetMap();
	D3DXVECTOR3 pos = GetPos();

	for (int i = 0; i < map->GetNumModel(); i++)
	{
		if (m_collision->ToBox(map->GetMapModel(i)->GetCollisionBox(), true))
		{// 押し出した位置
			SetPos(m_collision->GetPosWorld());
			if (m_collision->GetIsTop())
			{
				isGround = true;
			}
		}
	}

	for (int i = 0; i < map->GetNumMesh(); i++)
	{
		if (m_collision->ToMesh(map->GetMapMesh(i)->GetCollisionMesh()))
		{// 押し出した位置
			SetPos(m_collision->GetPosWorld());
			isGround = true;
		}
	}

	static STATE state;
	state = m_state;

	if (isGround)
	{
		m_state = GROUND;
	}
	else
	{
		m_state = SKY;
	}

	if (state == GROUND && m_state == GROUND)
	{
		SetMoveY(0.0f);
		m_jumpCount.SetCurrent(0);
	}

	if (m_hp.GetCurrent() <= 0)
	{
		// 死亡処理
		m_isDied = true;
	}


	// 重力
	AddMoveY(-0.18f);
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CCharacter::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用

	//現在のマテリアルを維持
	pDevice->GetMaterial(&matDef);

	//パーツのワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//パーツのモデルの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//パーツのモデルの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int i = 0; i < (int)m_apModel.size(); i++)
	{
		if (m_apModel[i]->GetParent() == nullptr)
		{
			m_apModel[i]->SetMtxWorld(m_mtxWorld);
		}
	}
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CCharacter* CCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//キャラクター生成
	CCharacter* pCharacter = new CCharacter;

	if (pCharacter != nullptr)
	{//NULLチェック
	 //メンバ変数に代入
		//初期化
		pCharacter->Init();
	}

	return pCharacter;
}

//--------------------------------------------------------------
// 位置の設定
//--------------------------------------------------------------
void CCharacter::SetPos(const D3DXVECTOR3 & inPos)
{
	std::vector<CObjectX*> objectX = GetModel();
	if (objectX.size() > 0)
	{
		GetModel()[0]->SetPos(inPos);
	}

	CObject::SetPos(inPos);
}

//--------------------------------------------------------------
// 向きの設定
//--------------------------------------------------------------
void CCharacter::SetRot(const D3DXVECTOR3 & inRot)
{
	if (m_apModel.size() > 0)
	{
		GetModel()[0]->SetRot(inRot);
	}

	CObject::SetRot(inRot);
}

//--------------------------------------------------------------
// ダメージ
//--------------------------------------------------------------
void CCharacter::Damage(const int inDamage)
{
	int dmg = inDamage;


	CStatus<int>* hp = GetHp();
	hp->AddCurrent(-dmg);
}

//--------------------------------------------------------------
// 攻撃
//--------------------------------------------------------------
void CCharacter::Attack(CCharacter* pEnemy, float SkillMul)
{
	// プレイヤーのダメージを計算
	int Damage = CalDamage(SkillMul);
	// エネミーにダメージを与える。
	pEnemy->Damage(Damage);
}

void CCharacter::Move()
{
}

//--------------------------------------------------------------
// ダメージ計算関数
//--------------------------------------------------------------
int CCharacter::CalDamage(float SkillAtkMul)
{// 攻撃力 * 

	int CalDamage =
		((m_attack.GetBase() + m_attack.GetAddItem() + m_attack.GetBuffItem()) *
		(m_attack.GetMulBuff() + m_attack.GetMulItem() + SkillAtkMul));

	return CalDamage;
}

////--------------------------------------------------------------
//// 防御力計算関数
////--------------------------------------------------------------
//int CCharacter::DefDamage(float SkillDefMul)
//{// 防御力
//	int Def =
//		((m_def.GetBase() + m_attack.GetAddItem() + m_attack.GetBuffItem()) *
//		(m_attack.GetMulBuff() + m_attack.GetMulItem() + SkillDefMul));
//}