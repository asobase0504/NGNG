//**************************************************************
//
// item_data_base
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "item_data_base.h"
#include "item.h"

#include "character.h"
#include "skill.h"
#include "gold_nugget.h"
#include "utility.h"

//==============================================================
// 静的メンバー変数の宣言
//==============================================================
CItemDataBase* CItemDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CItemDataBase::CItemDataBase()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
void CItemDataBase::Init()
{
	CItem* item;

	// 全て生成だけしとく
	for (int i = 0; i < ITEM_MAX; i++)
	{
		m_item[i] = CItem::Create((EItemType)i);
	}

	item = m_item[ITEM_DANGO];
	item->SetModel("ITEM_DANGO");
	item->SetRerity(RARITY_COMMON);
	// だんごの設定-------------------------------------------------
	/* HP+50(+50)増加 */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetHp()->AddItemEffect(50);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetHp()->AddItemEffect(-50);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_GETA];
	item->SetModel("ITEM_GETA");
	item->SetRerity(RARITY_COMMON);
	// 下駄の設定----------------------------------------------------
	/* 移動速度増加+0.15(0.15) */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetSpeed()->AddItemEffect(0.15f);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetSpeed()->AddItemEffect(-0.15f);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_UMBRELLA];
	item->SetModel("ITEM_UMBRELLA");
	item->SetRerity(RARITY_COMMON);
	// 傘の設定-----------------------------------------------------
	/* 防御力を+5(+5)する */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetDefense()->AddItemEffect(5);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetDefense()->AddItemEffect(-5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_HYOUTAN];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	// ひょうたん---------------------------------------------------
	/* 攻撃速度と移動速度を +0.075%(0.075)ずつする */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetAtkSpd()->AddItemEffect(0.075f);
		inCharacter->GetSpeed()->AddItemEffect(0.075f);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetAtkSpd()->AddItemEffect(-0.075f);
		inCharacter->GetSpeed()->AddItemEffect(-0.075f);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_BANBOO_WATERBOX];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	// 竹の水筒-----------------------------------------------------
	/* 攻撃速度を+0.15%(0.15)ずつする */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetAtkSpd()->AddItemEffect(0.15f);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetAtkSpd()->AddItemEffect(-0.15f);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_OMAMORI];
	item->SetModel("ITEM_OMAMORI");
	item->SetRerity(RARITY_COMMON);
	// お守り-------------------------------------------------------
	/* 攻撃速度を+0.1%(0.1%)する */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetAtkSpd()->AddItemEffect(0.1f);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetAtkSpd()->AddItemEffect(-0.1f);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KIBORI];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	// 熊の木彫り---------------------------------------------
	item->SetWhenReceiveFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		for (int Cnt = 0; Cnt <= cnt; Cnt++)
		{
			if (IsSuccessRate(0.15f))
			{// 15%の確率でブロックする。
				inCharacter->DamageBlock(true);
				break;
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_BAKUTIKU];
	item->SetModel("ITEM_BAKUTIKU");
	item->SetRerity(RARITY_COMMON);
	// ばくちく(保留)-----------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		for (int Cnt = 0; Cnt <= cnt; Cnt++)
		{
			if (IsSuccessRate(0.05f))
			{// 攻撃時に5%の確率でスタンさせる。
				outCharacter->SetAttackAbnormal(CAbnormalDataBase::ABNORMAL_STUN, true);
				break;
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_MAKIBISI];
	item->SetModel("ITEM_MAKIBISI");
	item->SetRerity(RARITY_COMMON);
	// まきびし-----------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 攻撃時に敵に移動速度-5%にする状態異常を付与する。
		for (int Cnt = 0; Cnt <= cnt; Cnt++)
		{
			if (IsSuccessRate(0.05f))
			{// 攻撃時に5%の確率でスロウさせる。
				outCharacter->SetAttackAbnormal(CAbnormalDataBase::ABNORMAL_SLOW, true);
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_HEAD];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	// 首級---------------------------------------------------------
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒した時、HPの1%(+1%)を回復する。
		int percent = 0;
		for (int Cnt = 0; Cnt <= cnt; Cnt++)
		{// 持ってる数、割合を増やす
			percent += 1;
		}

		// 最大体力を取得
		int hpMax = inCharacter->GetHp()->GetMax();
		// 回復する値
		int recovery = (int)(hpMax * (percent / 100));
		inCharacter->GetHp()->AddItemEffect(recovery);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KUNAI];
	item->SetModel("ITEM_KUNAI");
	item->SetRerity(RARITY_COMMON);
	// クナイ---------------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 体力が90%以上の敵に対して70%(+70%)ダメージが増加する。
		// 最大体力を取得
		int hpMax = outCharacter->GetHp()->GetMax();
		// 現在の体力
		int hpCurrent = outCharacter->GetHp()->GetCurrent();

		// 体力の割合を計算
		int percent = (int)(hpCurrent / hpMax * 100);

		if (percent >= 90)
		{// 相手の体力が90%以上だった時
			int addParcent = 0;

			for (int Cnt = 0; Cnt <= cnt; Cnt++)
			{// 持ってる数、割合を増やす
				addParcent += 70;
			}
			int nowAtk = inCharacter->GetAtk()->GetCurrent();
			nowAtk += nowAtk * (addParcent / 100);

			// ダメージ計算
			inCharacter->GetAtk()->SetCurrent(nowAtk);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FUR];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	// 毛皮---------------------------------------------------------
	item->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{// 最大体力の8%のシールドを得る。
		if (inCharacter->GetIsShield())
		{// シールドを回復する状態の時
			// 最大体力を取得
			int hpMax = inCharacter->GetHp()->GetMax();

			// 増やす割合
			int percent = 0;

			for (int Cnt = 0; Cnt <= cnt; Cnt++)
			{// 持ってる数、割合を増やす
				percent += 8;
			}

			int addShield = (int)(hpMax * (percent / 100));

			// プレイヤーのシールドに加算する処理
			inCharacter->GetBarrier()->AddItemEffect(addShield);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KITUNEMEN];
	item->SetModel("ITEM_KITUNENOOMEN");
	item->SetRerity(RARITY_UNCOMMON);
	// 狐面---------------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// クリティカルヒットで攻撃速度が12%上昇する。最大値は36% (+36%)。
		if (inCharacter->GetIsCritical())
		{
			int addAtkSpdPercent = 0;
			int numCritical = inCharacter->GetNumCritical();

			for (int i = 0; i < numCritical; i++)
			{// ヒットした数足す
				addAtkSpdPercent += 12;
			}

			int maxPercent = 0;

			for (int i = 0; i <= numCritical; i++)
			{// アイテムの所持数分、足す
				maxPercent += 36;
			}

			if (maxPercent < addAtkSpdPercent)
			{// 上限を超えた場合
				addAtkSpdPercent = maxPercent;
			}

			// 現在のスピードを取得
			float currentAtkSpd = inCharacter->GetAtkSpd()->GetCurrent();
			// 増やす割合の計算
			currentAtkSpd += currentAtkSpd * (addAtkSpdPercent / 100);
			// 設定
			inCharacter->GetAtkSpd()->SetCurrent(currentAtkSpd);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KAZAGURUMA];
	item->SetModel("ITEM_KAZAGURUMA");
	item->SetRerity(RARITY_UNCOMMON);
	// 風車---------------------------------------------------------
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒すと18%の確率で全てのクールダウンをリセットする
		for (int i = 0; i < cnt; i++)
		{
			if (!IsSuccessRate(0.18f))
			{
				continue;
			}

			for (int j = 0; j < CCharacter::MAX_SKILL; j++)
			{
				inCharacter->GetSkill(j)->SetCT(0);
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KOBAN];
	item->SetModel("ITEM_KOBAN");
	item->SetRerity(RARITY_UNCOMMON);
	// 小判---------------------------------------------------------
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒した際4%の確率で金塊が出現する (+4%)
		float probability = 0.0f;

		for (int j = 0; j <= cnt; j++)
		{
			probability += 0.04f;
		}

		if (IsSuccessRate(1.0f))
		{
			CGoldNugget* obj = CGoldNugget::Create();
			obj->SetPos(outCharacter->GetPos());
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_ONIMEN];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 鬼面---------------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 4つ以上のデバフがついた敵に死の印が付き、受けるダメージが7秒間(+7秒)50%増加する
		int numDebuff = outCharacter->GetAbnormalTypeCount();

		if (numDebuff >= 4)
		{// デバフを付与する　TODO
			//outCharacter->SetAttackAbnormal(CAbnormalDataBase::ABNORMAL_STUN, true);
		}

	});
	//--------------------------------------------------------------

	item = m_item[ITEM_BROKEN_KABUTO];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 壊れた兜---------------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 体力が13%以下になったエリートモンスターを即死させる (+13%)
		if (outCharacter->GetIsElite())
		{
			int parcent = 0;

			for (int j = 0; j <= cnt; j++)
			{
				parcent += 13;
			}

			// 一定の体力以下になった敵を殺す
			int hp = outCharacter->GetHp()->GetMax();
			hp *= (parcent / 100);

			int hpCurrent = outCharacter->GetHp()->GetCurrent();

			if (hpCurrent <= hp)
			{// 現在の体力が規定値以下だったら
				outCharacter->Died();
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_CROW_FEATHER];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// カラスの羽---------------------------------------------------------
	// ジャンプ回数 +1 (+1)
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->GetJumpCount()->AddItemEffect(1);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{ 
		inCharacter->GetJumpCount()->AddItemEffect(-1);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FLINT];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 砥石---------------------------------------------------------
	// クリティカル確率が5%上昇し、クリティカルが発生するごとに体力が8回復する (回復量 +8)
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{// 取得時
		inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{// なくしたとき
		inCharacter->GetCriticalRate()->AddItemEffect(-5);
	});
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// クリティカル発生時
		if (inCharacter->GetIsCritical())
		{
			int healHp = 0;
			for (int Cnt = 0; Cnt <= cnt; Cnt++)
			{
				healHp += 8;
			}
			inCharacter->GetHp()->AddItemEffect(healHp);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_DRIP_BAG];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 点滴袋---------------------------------------------------------
	// 敵を倒すごとに体力が永続的に1増える。最大100まで (最大 +100)TODO
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		inCharacter->GetHp()->AddItemEffect(1);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_CHICK];
	item->SetModel("ITEM_HIYOKO");
	item->SetRerity(RARITY_UNCOMMON);
	// ひよこ---------------------------------------------------------
	// 走りながらジャンプすると前方に10m飛び出す (+10m)TODO
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_ZOURI];
	item->SetModel("ITEM_ZOURI");
	item->SetRerity(RARITY_UNCOMMON);
	// 草履---------------------------------------------------------
	// 敵を倒すと移動速度が125%上がり、1(+0.5)秒間消える
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵が死んだら
		// 現在の速度
		float currentSpeed = inCharacter->GetSpeed()->GetCurrent();

		// スピードが上がる割合を計算
		currentSpeed *= (125 / 100);

		// 加算
		inCharacter->GetSpeed()->AddItemEffect(currentSpeed);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_ARROW];
	item->SetModel("ITEM_ARROW");
	item->SetRerity(RARITY_UNCOMMON);
	// 矢---------------------------------------------------------
	// プライマリースキルを発動すると、矢も投げて、400%(+100%)の基礎ダメージを与える。
	// 最大3(+1)個の矢を持つことができ、10秒経つとリロードされる
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_SEED];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 種子---------------------------------------------------------
	// 攻撃ヒット時に体力を1回復する (回復量+1)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		inCharacter->GetHp()->AddItemEffect(1);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FETTERS];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 足枷---------------------------------------------------------
	// 攻撃を当てた敵の移動速度が2秒間60%減少する (秒数 +2)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 
		outCharacter->SetAttackAbnormal(CAbnormalDataBase::ABNORMAL_SLOW, true);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_SHIELD];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 盾---------------------------------------------------------
	// 走っている間はアーマーが30増加する (+30)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		if (inCharacter->GetIsRunning())
		{
			int armor = 0;

			for (int Cnt = 0; Cnt <= cnt; Cnt++)
			{// 持ってる数、割合を増やす
				armor += 30;
			}

			inCharacter->GetBarrier()->AddItemEffect(armor);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_TABI];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// たび---------------------------------------------------------
	// 非戦闘時の移動速度 +30% (+30%)
	item->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{
		if (inCharacter->GetIsNonCombat())
		{
			float speed = inCharacter->GetSpeed()->GetCurrent();

			int addParcent = 0;
			for (int Cnt = 0; Cnt <= cnt; Cnt++)
			{
				addParcent += 30;
			}

			speed += speed * (addParcent / 100);
			inCharacter->GetSpeed()->SetCurrent(speed);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FLINT];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 火打石---------------------------------------------------------
	// 発火の効果で、与えるダメージが時間の経過とともに+300%(+300%)以上増える
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FLOWER];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 花---------------------------------------------------------
	// テレポーターイベント中近くの味方を50%回復するヒーリングノヴァを発する (+1回) 
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_IRON_WIRE];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	// 鉄線---------------------------------------------------------
	// ダメージを受けた際、周囲25m(+10m)以内にいる敵最大5体に160%のダメージを与える (+2体)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_HANNYA];
	item->SetModel("BOX");
	item->SetRerity(RARITY_RARE);
	// 般若面---------------------------------------------------------
	// 1秒以内に4体の敵を倒すと6秒間フレンジー状態になる。フレンジー発動中は移動速度が50%、攻撃速度が100%上昇する (+4秒)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_ELITE];
	item->SetRerity(RARITY_NOSELECT);
	// エリート---------------------------------------------------------
	// 持っているものはエリートになる
	item->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{// 倍率の設定
		int magnification = 2;
		int hp = inCharacter->GetHp()->GetCurrent();
		hp *= magnification;
		inCharacter->GetHp()->SetCurrent(hp);
		int def = inCharacter->GetDefense()->GetCurrent();
		def *= magnification;
		inCharacter->GetDefense()->SetCurrent(def);
		int atk = inCharacter->GetAtk()->GetCurrent();
		atk *= magnification;
		inCharacter->GetAtk()->SetCurrent(atk);
	});
	//--------------------------------------------------------------
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CItemDataBase * CItemDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CItemDataBase;

		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CItemDataBase::~CItemDataBase()
{
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CItemDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}
