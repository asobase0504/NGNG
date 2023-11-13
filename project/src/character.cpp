//**************************************************************
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
#include "item.h"
#include "abnormal.h"
#include "abnormal_data_base.h"

#include "status.h"
#include "map.h"
#include "map_model.h"
#include "object_mesh.h"

#include "item_manager.h"

#include <thread>

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
	m_money.SetCurrent(50);
	m_isStun = false;

	for (int i = 0; i < CAbnormalDataBase::ABNORMAL_MAX; i++)
	{
		m_attackAbnormal[i] = false;
		m_haveAbnormal[i].s_stack = 0;
		m_haveAbnormal[i].s_effectTime = 0;
		m_haveAbnormal[i].s_target_interval = 0;
		m_haveAbnormal[i].s_interval = 0;

		for (int data :m_haveAbnormal[i].s_Time)
		{
			data = 0;
		}
	}

	m_state = GROUND;

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CCharacter::Uninit()
{
	// 破棄処理
	CObject::Release();

	m_apModel[0]->Uninit();
	m_collision->Uninit();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CCharacter::Update()
{
	// 更新処理
	CObject::Update();

	bool isGround = false;


	CMap* map = CMap::GetMap();
	D3DXVECTOR3 pos = GetPos();

	// 像との押し出し当たり判定
	std::list<CStatue*> list = map->GetStatueList();
	for (CStatue* inStatue : list)
	{
		if (!(m_collision->ToBox(inStatue->GetCollisionBox(), true)))
		{
			continue;
		}

		if (m_collision->GetIsTop())
		{
			isGround = true;
		}

		D3DXVECTOR3 extrusion = m_collision->GetPosWorld();
		SetPos(extrusion);
		SetMoveXZ(0.0f, 0.0f);
	}

	for (int i = 0; i < map->GetNumModel(); i++)
	{
		if (m_collision->ToBox(map->GetMapModel(i)->GetCollisionBox(), true))
		{// 押し出した位置
			D3DXVECTOR3 extrusion = m_collision->GetPosWorld();
			SetPos(extrusion);
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
			D3DXVECTOR3 extrusion = m_collision->GetPosWorld();
			SetPos(extrusion);
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

	// 付与されている状態異常を作動させる
	Abnormal();
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CCharacter::Draw()
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

	// ダメージ計算
	CStatus<int>* hp = GetHp();

	// 防御力算出
	int def = m_defense.CalStatus();

	dmg -= def;

	if (dmg <= 1)
	{// ダメージが1以下だった時1にする
		dmg = 1;
	}

	if (m_isBlock)
	{// ブロックがtrueの時にダメージを0にする
		dmg = 0;
		DamageBlock(false);
	}

	hp->AddCurrent(-dmg);
}

//--------------------------------------------------------------
// 攻撃
//--------------------------------------------------------------
void CCharacter::Attack(CCharacter* pEnemy, float SkillMul)
{
	// ダメージを与えた処理
	CItemManager::GetInstance()->AllWhenDamage(this, m_haveItem, pEnemy);
	// ダメージを受けた処理
	CItemManager::GetInstance()->AllWhenHit(pEnemy, pEnemy->m_haveItem, this);

	// プレイヤーのダメージを計算
	int Damage = CalDamage(SkillMul);
	// エネミーにダメージを与える。
	pEnemy->Damage(Damage);

	// 付与されている状態異常を作動させる
	for (int i = 0; i < m_attackAbnormal.size(); i++)
	{
		if (m_attackAbnormal[i] != false)
		{
			return;
		}

		CAbnormal::ABNORMAL_ACTION_FUNC abnormalFunc = CAbnormalDataBase::GetInstance()->GetItemData((CAbnormalDataBase::EAbnormalType)i)->GetWhenAttackFunc();

		if (abnormalFunc != nullptr)
		{
			abnormalFunc(this, i, pEnemy);
		}
	}
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
		(int)(((m_attack.GetBase() + m_attack.GetAddItem() + m_attack.GetBuffItem()) *
		(m_attack.GetMulBuff() + m_attack.GetMulItem() + SkillAtkMul)));


	return CalDamage;
}

//--------------------------------------------------------------
// 状態異常
//--------------------------------------------------------------
void CCharacter::Abnormal()
{
	// 付与されている状態異常を作動させる
	for (int i = 0; i < m_haveAbnormal.size(); i++)
	{
		if (m_haveAbnormal[i].s_stack <= 0)
		{
			continue;
		}

		CAbnormal::ABNORMAL_FUNC abnormalFunc = CAbnormalDataBase::GetInstance()->GetItemData((CAbnormalDataBase::EAbnormalType)i)->GetWhenAllWayFunc();

		if (abnormalFunc != nullptr)
		{

			for (int &data : m_haveAbnormal[i].s_Time)
			{
				data++;
			}

			m_haveAbnormal[i].s_interval++;

			for (int data : m_haveAbnormal[i].s_Time)
			{
				if (data >= m_haveAbnormal[i].s_effectTime)
				{// 状態異常を削除する
					CAbnormal::ABNORMAL_FUNC LostFunc = CAbnormalDataBase::GetInstance()->GetItemData((CAbnormalDataBase::EAbnormalType)i)->GetWhenClearFunc();

					//if (Los)
					{// 失った時の処理を呼び出す
					 // スタック数を減らす
						LostFunc(this, i);
						m_haveAbnormal[i].s_stack--;
					}
				}
			}

			// 付与されている状態異常の時間を減らす
			m_haveAbnormal[i].s_Time.remove_if([this, i](int data)
			{
				return data >= m_haveAbnormal[i].s_effectTime;
			});

			if (m_haveAbnormal[i].s_interval >= m_haveAbnormal[i].s_target_interval)
			{
				m_haveAbnormal[i].s_interval = 0;
				abnormalFunc(this, i);
			}
		}
	}
}