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
#include "utility.h"

#include "item_manager.h"

#include <thread>

#include "damege_ui.h"

//==============================================================
// 定数宣言
//==============================================================
const int CCharacter::MAX_SKILL(4);
const int CCharacter::MAX_NON_COMBAT_TIME(300);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CCharacter::CCharacter(int nPriority) : m_haveItem{}
{
	if (CMap::GetMap() != nullptr)
	{
		CMap::GetMap()->InCharacterList(this);
	}
	m_apModel.clear();
	m_skill.clear();
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
	m_isShield = false;
	m_isCritical = false;
	m_numCritical = 0;
	m_isBlock = false;
	m_isStun = false;
	m_nonCombat = false;
	m_nonCombatTime = 0;
	m_isRunning = false;
	m_isElite = false;
	m_isMoveLock = false;
	m_isControl = false;
	m_isTeleporter = false;

	m_apModel.resize(1);
	m_apModel[0] = CObjectX::Create(m_pos);
	m_apModel[0]->LoadModel("BOX");

	m_hp.Init(100);
	m_hp.SetCurrent(100);
	m_hp.AttachMax();
	m_addHp.Init(100);
	m_addHp.SetCurrent(100);
	m_addHp.AttachMax();
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
	m_defense.Init(0);
	m_defense.SetCurrent(0);
	m_criticalRate.Init(0.0f);
	m_criticalRate.SetCurrent(0.0f);
	m_criticalDamage.Init(2.0f);
	m_criticalDamage.SetCurrent(2.0f);
	m_movePower.Init(2.0f);
	m_movePower.SetCurrent(2.0f);
	m_dashPower.Init(1.25f);
	m_dashPower.SetCurrent(1.25f);
	m_jumpPower.Init();
	m_jumpPower.SetCurrent(5.0f);
	m_jumpCount.Init(1);
	m_jumpCount.SetCurrent(0);
	m_jumpCount.AttachMax();
	m_money.Init();
	m_money.SetCurrent(50);
	m_regenetionTime.Init(60);
	m_regenetion.Init(1);
	m_RegenetionCnt = 0;
	m_isStun = false;
	m_isBlock = false;
	m_isAtkCollision = false;
	m_addDamage = 0.0f;

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

	// 親子関係の構築
	SetEndChildren(m_apModel[0]);

	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CCharacter::Update()
{
	// 更新処理
	CObject::Update();

	// 常に起動するアイテム
	CItemManager::GetInstance()->AllWhenAllways(this, m_haveItem);

	Collision();

	if (!m_isMoveLock)
	{
		// 重力
		AddMoveY(-0.18f);
	}

	// 付与されている状態異常を作動させる
	Abnormal();

	// 自動回復
	Regenation();

	if (!m_nonCombat)
	{// 非戦闘時にする
		m_nonCombatTime++;

		if (m_nonCombatTime > MAX_NON_COMBAT_TIME)
		{
			m_nonCombat = true;
			m_nonCombatTime = 0;
		}
	}
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

void CCharacter::TakeItem(int id)
{
	m_haveItem[id]++;
	CItem::ITEM_FUNC itemFunc = CItemDataBase::GetInstance()->GetItemData((CItemDataBase::EItemType)id)->GetWhenPickFunc();

	if (itemFunc != nullptr)
	{
		itemFunc(this, m_haveItem[id]);
	}
}

//--------------------------------------------------------------
// 攻撃
//--------------------------------------------------------------
void CCharacter::Attack(CCharacter* pEnemy, float SkillMul)
{
	m_nonCombat = false;

	if (IsSuccessRate(m_criticalRate.GetMax()))
	{// クリティカルかどうか
		m_isCritical = true;
		m_numCritical++;
	}

	// ダメージを与えた処理	
	CItemManager::GetInstance()->AllWhenInflict(this, m_haveItem, pEnemy);

	// プレイヤーのダメージを計算
	int damage = CalDamage(SkillMul);

	// アイテムによるダメージの加算
	damage += m_addDamage;

	if(m_isCritical)
	{
		damage *= m_criticalDamage.GetMax();
	}

	// エネミーにダメージを与える。
	pEnemy->Damage(damage, pEnemy);

	if (pEnemy->IsDied())
	{// エネミーが死んだとき
		CItemManager::GetInstance()->AllWhenDeath(this, m_haveItem, pEnemy);
	}

	// 攻撃付与されている状態異常を作動させる
	for (int i = 0; i < m_attackAbnormal.size(); i++)
	{
		if (!m_attackAbnormal[i])
		{
			return;
		}

		CAbnormal::ABNORMAL_ACTION_FUNC abnormalFunc = CAbnormalDataBase::GetInstance()->GetAbnormalData((CAbnormalDataBase::EAbnormalType)i)->GetWhenAttackFunc();

		if (abnormalFunc != nullptr)
		{
			abnormalFunc(this, i, pEnemy);
		}
	}
}

//--------------------------------------------------------------
// ダメージ
//--------------------------------------------------------------
void CCharacter::Damage(const int inDamage, CCharacter* inCharacter)
{
	// ダメージを受けた処理
	CItemManager::GetInstance()->AllWhenReceive(inCharacter, inCharacter->m_haveItem, this);

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

	// UI生成
	D3DXVECTOR3 pos = m_pos;
	pos.x += FloatRandom(20.0f, -20.0f);
	pos.y += FloatRandom(40.0f, 0.0f);
	pos.z += FloatRandom(20.0f, -20.0f);
	CDamegeUI::Create(pos,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),dmg);

	hp->AddCurrent(-dmg);

	// アイテムによるダメージンの加算の初期化
	m_addDamage = 0.0f;

	if (m_hp.GetCurrent() <= 0)
	{// 死亡処理
		Died();
	}
}

//--------------------------------------------------------------
// ダメージ計算関数
//--------------------------------------------------------------
int CCharacter::CalDamage(float SkillAtkMul)
{// 攻撃力 * 

	int CalDamage =
		(int)(((m_attack.GetBase() + m_attack.GetAddItem() + m_attack.GetBuffItem()) *
		(m_attack.GetMulBuff() * m_attack.GetMulItem() * SkillAtkMul)));

	return CalDamage;
}

//--------------------------------------------------------------
// 回復
//--------------------------------------------------------------
void CCharacter::Heal(int heal)
{
	int HealHp = heal;
	int HealHpCheck = m_hp.GetCurrent() + HealHp;

	if (HealHpCheck >= m_hp.GetMax())
	{
		HealHp = m_hp.GetMax() - m_hp.GetCurrent();
	}

	m_hp.AddCurrent(HealHp);
}

//--------------------------------------------------------------
// 割合回復
//--------------------------------------------------------------
void CCharacter::RatioHeal(float heal)
{
	float ratio = m_hp.GetCurrent() * heal;
	if (ratio <= 1)
	{
		ratio = 1.0f;
	}

	Heal(ratio);
}

//--------------------------------------------------------------
// 自動回復
//--------------------------------------------------------------
void CCharacter::Regenation()
{
	m_RegenetionCnt++;

	if (m_regenetionTime.GetBase() <= m_RegenetionCnt)
	{
		m_RegenetionCnt = 0;
		Heal(m_regenetion.GetBase());
	}
}

//--------------------------------------------------------------
// 死亡処理
//--------------------------------------------------------------
void CCharacter::Died()
{
	m_isDied = true;
	std::list<CCharacter*> list = CMap::GetMap()->GetCharacterList();
	list.remove(this);
	CMap::GetMap()->SetCharacterList(list);
}

//--------------------------------------------------------------
// 移動量
//--------------------------------------------------------------
void CCharacter::Move()
{
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

		CAbnormal::ABNORMAL_FUNC abnormalFunc = CAbnormalDataBase::GetInstance()->GetAbnormalData((CAbnormalDataBase::EAbnormalType)i)->GetWhenAllWayFunc();

		if (abnormalFunc == nullptr)
		{
			continue;
		}

		for (int &data : m_haveAbnormal[i].s_Time)
		{
			data++;
		}

		m_haveAbnormal[i].s_interval++;

		for (int data : m_haveAbnormal[i].s_Time)
		{
			if (data >= m_haveAbnormal[i].s_effectTime)
			{// 状態異常を削除する
				CAbnormal::ABNORMAL_FUNC LostFunc = CAbnormalDataBase::GetInstance()->GetAbnormalData((CAbnormalDataBase::EAbnormalType)i)->GetWhenClearFunc();

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

//--------------------------------------------------------------
// 主に押し出しの当たり判定
//--------------------------------------------------------------
void CCharacter::Collision()
{
	bool isGround = false;

	CMap* map = CMap::GetMap();
	D3DXVECTOR3 pos = GetPos();

	// 選択できる物体との押し出し当たり判定
	std::list<CSelectEntity*> list = map->GetSelectEntityList();
	for (CSelectEntity* inSelectEntity : list)
	{
		CCollisionBox* collisionBox = inSelectEntity->GetCollisionBox();

		if (collisionBox == nullptr)
		{
			continue;
		}

		if (!(m_collision->ToBox(collisionBox, true)))
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

	// マップモデル
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

	// マップメッシュ
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
}

//--------------------------------------------------------------
// 状態異常の種類の個数の獲得
//--------------------------------------------------------------
int CCharacter::GetAbnormalTypeCount()
{
	int abnormal_type_count = 0;
	
	// 付与されている状態異常をカウントする
	for (int i = 0; i < m_haveAbnormal.size(); i++)
	{
		if (m_haveAbnormal[i].s_stack <= 0)
		{
			continue;
		}

		abnormal_type_count++;
	}

	return abnormal_type_count;
}
