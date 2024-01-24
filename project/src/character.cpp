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
#include "model_skin.h"
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
#include "collision_box.h"

#include "application.h"
#include "mode.h"

//==============================================================
// 定数宣言
//==============================================================
const int CCharacter::MAX_SKILL(4);
const int CCharacter::MAX_NON_COMBAT_TIME(300);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CCharacter::CCharacter(int nPriority) : m_haveItem{},
	m_extrusion(nullptr)
{
	CMap *map = CApplication::GetInstance()->GetMap();
	if (map != nullptr)
	{
		map->InCharacterList(this);
	}
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
	m_isInertiaMoveLock = false;
	m_isToFaceRot = true;
	m_isHitDamage = false;

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
	m_attack.Init(10);
	m_attack.SetCurrent(10);
	m_attackSpeed.Init(1.0f);
	m_attackSpeed.SetCurrent(1.0f);
	m_defense.Init(10);
	m_defense.SetCurrent(10);
	m_criticalRate.Init(0.0f);
	m_criticalRate.SetCurrent(0.0f);
	m_criticalDamage.Init(2.0f);
	m_criticalDamage.SetCurrent(2.0f);
	m_movePower.Init(4.0f);
	m_movePower.SetCurrent(4.0f);
	m_dashPower.Init(1.55f);
	m_dashPower.SetCurrent(1.55f);
	m_jumpPower.Init();
	m_jumpPower.SetCurrent(5.0f);
	m_jumpCount.Init(1);
	m_jumpCount.SetCurrent(0);
	m_jumpCount.AttachMax();
	m_money.Init();
	m_money.SetCurrent(500000);
	m_regenetionTime.Init(60);
	m_regenetion.Init(1);
	m_RegenetionCnt = 0;
	m_exp = 0;
	m_level = 1;
	m_reqExp = m_level * 100.0f;
	m_destRot = 0.0f;

	m_isStun = false;
	m_isBlock = false;
	m_isAtkCollision = false;
	m_addDamage = 0.0f;
	m_forwardJumpPoewer = 1.0f;
	m_itemMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_effectTime = 0;
	m_isAccel = false;
	m_nonComAddSpeed = 0.0f;

	for (int i = 0; i < CAbnormalDataBase::ABNORMAL_MAX; i++)
	{
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

	m_extrusion = CCollisionBox::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f));
	m_extrusion->SetParent(&m_pos);

	m_skinModel = CSkinMesh::Create();
	return S_OK;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CCharacter::Update()
{
	// 更新処理
	CObject::Update();

	m_effectTime--;
	if (m_effectTime > 0)
	{
		AddPos(GetItemMove());
	}
	else
	{
		m_effectTime = 0;
	}

	// 常に起動するアイテム
	CItemManager::GetInstance()->AllWhenAllways(this, m_haveItem);

	RotateToFace();

	Collision();

	if (!m_isMoveLock && !m_isInertiaMoveLock)
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

	if (m_pos.y < -900.0f)
	{
		SetPos(m_groundPos);
	}

	if (m_state == STATE::GROUND)
	{
		m_groundPos = m_pos;
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

	m_skinModel->SetMtxWorld(m_mtxWorld);
}

//--------------------------------------------------------------
// 位置の設定
//--------------------------------------------------------------
void CCharacter::SetPos(const D3DXVECTOR3 & inPos)
{
	m_skinModel->SetPos(inPos);
	CObject::SetPos(inPos);
}
 
//--------------------------------------------------------------
// 向きの設定
//--------------------------------------------------------------
void CCharacter::SetRot(const D3DXVECTOR3 & inRot)
{
	m_skinModel->SetRot(inRot);
	CObject::SetRot(inRot);
}

//--------------------------------------------------------------
// アイテムを拾う
//--------------------------------------------------------------
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
// ダメージを与える
//--------------------------------------------------------------
void CCharacter::DealDamage(CCharacter* pEnemy, float SkillMul)
{
	m_nonCombat = false;

	if (IsSuccessRate(/*m_criticalRate.GetMax()*/1.0f))
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
	pEnemy->TakeDamage(damage,this);

	if (pEnemy->IsDied())
	{// エネミーが死んだとき
		CItemManager::GetInstance()->AllWhenDeath(this, m_haveItem, pEnemy);
	}
}

//--------------------------------------------------------------
// ダメージを受ける
//--------------------------------------------------------------
void CCharacter::TakeDamage(const int inDamage, CCharacter* inChara)
{
	// ダメージを受けた処理
	CItemManager::GetInstance()->AllWhenReceive(this, m_haveItem, inChara);

	if (inChara)
	{
		m_isHitDamage = true;
	}

	int dmg = inDamage;

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

	// ダメージUI生成
	D3DXVECTOR3 pos = m_pos;
	pos.x += FloatRandom(m_size.x, -m_size.x);
	pos.y += FloatRandom(m_size.y, 0.0f);
	pos.z += FloatRandom(m_size.x, -m_size.x);
	CDamegeUI::Create(pos,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),dmg);

	// ダメージ計算
	CStatus<int>* hp = GetHp();

	hp->AddCurrent(-dmg);

	// アイテムによるダメージンの加算の初期化
	m_addDamage = 0.0f;

	if (m_hp.GetCurrent() <= 0)
	{// 死亡処理
		Died();
	}
}

//--------------------------------------------------------------
// ダメージ(防御なし)
//--------------------------------------------------------------
void CCharacter::AbDamage(const int inDamage)
{
	int dmg = inDamage;

	// ダメージ計算
	CStatus<int>* hp = GetHp();

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
	CDamegeUI::Create(pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), dmg);

	hp->AddCurrent(-dmg);

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
		(int)(((m_attack.GetBase() + m_attack.GetAddItem() + m_attack.GetBuff()) *
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

	// 回復しなかったら
	if (HealHp <= 0)
	{
		return;
	}

	// ダメージUI生成
	D3DXVECTOR3 pos = m_pos;
	pos.x += FloatRandom(20.0f, -20.0f);
	pos.y += FloatRandom(40.0f, 0.0f);
	pos.z += FloatRandom(20.0f, -20.0f);
	CDamegeUI::Create(pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), HealHp);

	m_hp.AddCurrent(HealHp);
}

//--------------------------------------------------------------
// 割合回復
//--------------------------------------------------------------
void CCharacter::RatioHeal(float heal)
{
	float ratio = m_hp.GetCurrent() * heal;

	if (ratio <= 1.0f)
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
	std::list<CCharacter*> list = CApplication::GetInstance()->GetModeClass()->GetMap()->GetCharacterList();
	list.remove(this);
	CApplication::GetInstance()->GetMap()->SetCharacterList(list);
}

//--------------------------------------------------------------
// 描画を切る
//--------------------------------------------------------------
void CCharacter::SetDisplay(bool display)
{
	CObject::SetDisplay(display);
	m_skinModel->SetDisplay(display);
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
	for (size_t i = 0; i < m_haveAbnormal.size(); i++)
	{
		CAbnormal* abnormal = CAbnormalDataBase::GetInstance()->GetAbnormalData((CAbnormalDataBase::EAbnormalType)i);

		if (m_haveAbnormal[i].s_stack <= 0)
		{
			continue;
		}

		CAbnormal::ABNORMAL_FUNC abnormalFunc = abnormal->GetWhenAllWayFunc();

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
				CAbnormal::ABNORMAL_FUNC LostFunc = abnormal->GetWhenClearFunc();

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

	CMap* map = CApplication::GetInstance()->GetMap();
	D3DXVECTOR3 pos = GetPos();
	if (map == nullptr)
	{
		return;
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
			FallDamage();
			isGround = true;
		}
	}

	// 押し出し位置
	for (CCharacter* chara : map->GetCharacterList())
	{
		if (chara == nullptr || m_collision == nullptr || chara->m_extrusion == nullptr)
		{
			continue;
		}

		if (m_collision->ToBox(chara->m_extrusion, true))
		{// 押し出した位置
			D3DXVECTOR3 extrusion = m_collision->GetPosWorld();
			SetPos(extrusion);
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
// 落下ダメージ
//--------------------------------------------------------------
void CCharacter::FallDamage()
{
	if (m_move.y >= -10.0f)
	{
		return;
	}

	float speed = m_move.y * 0.5f;

	int dmg = -speed;

	if (dmg <= 0)
	{
		return;
	}

	// ダメージ計算
	CStatus<int>* hp = GetHp();

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
	CDamegeUI::Create(pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), dmg);

	hp->AddCurrent(-dmg);

	if (m_hp.GetCurrent() <= 0)
	{
		m_hp.SetCurrent(1);
	}

	m_move.y = 0.0f;
}

//--------------------------------------------------------------
// 向いている向きを回転させる
//--------------------------------------------------------------
void CCharacter::RotateToFace()
{
	// Y軸向きを慣性で回転
	D3DXVECTOR3 move = GetMove();
	move.y = 0.0f;
	if (D3DXVec3Length(&move) != 0.0f)
	{
		D3DXVec3Normalize(&move, &move);
		m_destRot = atan2f(move.x, move.z);
	}

	float dest = m_destRot - m_rot.y;
	dest *= 0.1f;
	AddRot(D3DXVECTOR3(0.0f, dest, 0.0f));
}

//--------------------------------------------------------------
// 状態異常の種類の個数の獲得
//--------------------------------------------------------------
int CCharacter::GetAbnormalTypeCount()
{
	int abnormal_type_count = 0;
	
	// 付与されている状態異常をカウントする
	for (size_t i = 0; i < m_haveAbnormal.size(); i++)
	{
		if (m_haveAbnormal[i].s_stack <= 0)
		{
			continue;
		}

		abnormal_type_count++;
	}

	return abnormal_type_count;
}

//-----------------------------------------
// レベルの加算処理
//-----------------------------------------
void CCharacter::AddLevel()
{
	m_exp = 0;
	m_level++;

	// 必要経験値の設定
	m_reqExp = m_level * 100;

	// 各種ステータスの調整
	m_hp.AddMax(m_hp.GetBase() * (1.0f + (m_level * 0.1f)));
	m_attack.AddBaseState(m_attack.GetBase() * (1 + (m_level * 0.1f)));
	m_attackSpeed.AddBaseState(m_attackSpeed.GetBase() * (1.0f + (m_level * 0.1f)));
	m_movePower.AddBaseState(m_movePower.GetBase() * (1.0f + (m_level * 0.01f)));
}

//-----------------------------------------
// レベルの設定処理
//-----------------------------------------
void CCharacter::SetLevel(int level)
{
	m_level = level;

	// 各種ステータスの調整
	m_hp.AddMax(m_hp.GetBase() * (1.0f + (m_level * 0.1f)));
	m_hp.SetCurrent(m_hp.GetMax());
	m_attack.AddBaseState(m_attack.GetBase() * (1 + (m_level * 0.1f)));
	m_attackSpeed.AddBaseState(m_attackSpeed.GetBase() * (1.0f + (m_level * 0.1f)));
	m_movePower.AddBaseState(m_movePower.GetBase() * (1.0f + (m_level * 0.01f)));
}

//-----------------------------------------
// ExPの加算処理
//-----------------------------------------
void CCharacter::AddExp(int exp)
{
	m_exp++;

	if (m_exp >= m_reqExp)
	{
		AddLevel();
	}
}