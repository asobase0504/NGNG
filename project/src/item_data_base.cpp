#include "item_data_base.h"
#include "item.h"

#include "character.h"
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
	m_item[ITEM_DANGO] = CItem::Create(ITEM_DANGO);
	// だんごの設定-------------------------------------------------
	/* HP+50(+50)増加 */
	m_item[ITEM_DANGO]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetHp()->AddItemEffect(50); });
	m_item[ITEM_DANGO]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetHp()->AddItemEffect(-50); });

	//--------------------------------------------------------------

	m_item[ITEM_GETA] = CItem::Create(ITEM_GETA);
	// 下駄の設定----------------------------------------------------
	/* 移動速度増加+0.15(0.15) */
	m_item[ITEM_GETA]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetSpeed()->AddItemEffect(0.15f); });
	m_item[ITEM_GETA]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetSpeed()->AddItemEffect(-0.15f); });

	//--------------------------------------------------------------

	m_item[ITEM_UMBRELLA] = CItem::Create(ITEM_UMBRELLA);
	// 傘の設定-----------------------------------------------------
	/* 防御力を+5(+5)する */
	m_item[ITEM_UMBRELLA]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetDefense()->AddItemEffect(5); });
	m_item[ITEM_UMBRELLA]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetDefense()->AddItemEffect(-5); });
	//--------------------------------------------------------------

	m_item[ITEM_HYOUTAN] = CItem::Create(ITEM_HYOUTAN);
	// ひょうたん---------------------------------------------------
	/* 攻撃速度と移動速度を +0.075%(0.075)ずつする */
	m_item[ITEM_HYOUTAN]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.075f); 
		inCharacter->GetSpeed()->AddItemEffect(0.075f); });
	m_item[ITEM_HYOUTAN]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.075f);
	inCharacter->GetSpeed()->AddItemEffect(-0.075f); });
	//--------------------------------------------------------------

	m_item[ITEM_BANBOO_WATERBOX] = CItem::Create(ITEM_BANBOO_WATERBOX);
	// 竹の水筒-----------------------------------------------------
	/* 攻撃速度を+0.15%(0.15)ずつする */
	m_item[ITEM_BANBOO_WATERBOX]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.15f);});
	m_item[ITEM_BANBOO_WATERBOX]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.15f); });
	//--------------------------------------------------------------

	m_item[ITEM_OMAMORI] = CItem::Create(ITEM_OMAMORI);
	// お守り-------------------------------------------------------
	/* 攻撃速度を+0.1%(0.1%)する */
	m_item[ITEM_OMAMORI]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.1f); });
	m_item[ITEM_OMAMORI]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.1f); });
	//--------------------------------------------------------------

	m_item[ITEM_KIBORI] = CItem::Create(ITEM_KIBORI);
	m_item[ITEM_KIBORI]->SetModel("BOX");
	// 熊の木彫り(保留)---------------------------------------------
	m_item[ITEM_KIBORI]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
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

	m_item[ITEM_BAKUTIKU] = CItem::Create(ITEM_BAKUTIKU);
	// ばくちく(保留)-----------------------------------------------
	m_item[ITEM_BAKUTIKU]->SetWhenReceiveFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		for (int Cnt = 0; Cnt <= cnt; Cnt++)
		{
			if (IsSuccessRate(0.05f))
			{// 攻撃時に5%の確率でスタンさせる。
				//outCharacter->DamageBlock(true);
				break;
			}
		}
	});
	//--------------------------------------------------------------

	m_item[ITEM_MAKIBISI] = CItem::Create(ITEM_MAKIBISI);
	// まきびし-----------------------------------------------------
	m_item[ITEM_MAKIBISI]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 攻撃時に敵に移動速度-5%にする状態異常を付与する。
		//outCharacter->DamageBlock(true);
	});

	//--------------------------------------------------------------

	m_item[ITEM_HEAD] = CItem::Create(ITEM_HEAD);
	// 首級---------------------------------------------------------
	m_item[ITEM_HEAD]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
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

	m_item[ITEM_KUNAI] = CItem::Create(ITEM_KUNAI);
	// 首級---------------------------------------------------------
	m_item[ITEM_KUNAI]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
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

	m_item[ITEM_FUR] = CItem::Create(ITEM_FUR);
	// 毛皮---------------------------------------------------------
	m_item[ITEM_FUR]->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
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
			inCharacter->GetBarrier()->SetCurrent(addShield);
		}
	});

	m_item[ITEM_KITUNEMEN] = CItem::Create(ITEM_KITUNEMEN);
	// 狐面---------------------------------------------------------
	m_item[ITEM_KITUNEMEN]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
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

	m_item[ITEM_KAZAGURUMA] = CItem::Create(ITEM_KAZAGURUMA);
	// 風車---------------------------------------------------------
	m_item[ITEM_KAZAGURUMA]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒すと18%の確率で全てのクールダウンをリセットする
		if (outCharacter->IsDied())
		{// TODO

		}
	});

	m_item[ITEM_KOBAN] = CItem::Create(ITEM_KOBAN);
	// 小判---------------------------------------------------------
	m_item[ITEM_KOBAN]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒した際4%の確率で金塊が出現する (+4%) TODO
	});

	m_item[ITEM_ONIMEN] = CItem::Create(ITEM_ONIMEN);
	// 鬼面---------------------------------------------------------
	m_item[ITEM_ONIMEN]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 4つ以上のデバフがついた敵に死の印が付き、受けるダメージが7秒間(+7秒)50%増加する TODO
	});

	m_item[ITEM_BROKEN_KABUTO] = CItem::Create(ITEM_BROKEN_KABUTO);
	// 壊れた兜---------------------------------------------------------
	m_item[ITEM_BROKEN_KABUTO]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 体力が13%以下になったエリートモンスターを即死させる (+13%)TODO
	});

	m_item[ITEM_CROW_FEATHER] = CItem::Create(ITEM_CROW_FEATHER);
	// カラスの羽---------------------------------------------------------
	// ジャンプ回数 +1 (+1)
	m_item[ITEM_CROW_FEATHER]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{ inCharacter->GetJumpCount()->AddItemEffect(1); });
	m_item[ITEM_CROW_FEATHER]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{ inCharacter->GetJumpCount()->AddItemEffect(-1); });
	//--------------------------------------------------------------

	m_item[ITEM_FLINT] = CItem::Create(ITEM_FLINT);
	// 砥石---------------------------------------------------------
	// クリティカル確率が5%上昇し、クリティカルが発生するごとに体力が8回復する (回復量 +8)
	m_item[ITEM_FLINT]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{ inCharacter->GetCriticalRate()->AddItemEffect(5); });
	m_item[ITEM_FLINT]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{ inCharacter->GetCriticalRate()->AddItemEffect(-5); });

	m_item[ITEM_FLINT]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
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

	m_item[ITEM_DRIP_BAG] = CItem::Create(ITEM_DRIP_BAG);
	// 点滴袋---------------------------------------------------------
	// 敵を倒すごとに体力が永続的に1増える。最大100まで (最大 +100)TODO
	m_item[ITEM_DRIP_BAG]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		if (outCharacter->IsDied())
		{
			inCharacter->GetHp()->AddItemEffect(1);
		}
	});
	//--------------------------------------------------------------

	m_item[ITEM_CHICK] = CItem::Create(ITEM_CHICK);
	// ひよこ---------------------------------------------------------
	// 走りながらジャンプすると前方に10m飛び出す (+10m)TODO
	m_item[ITEM_CHICK]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_ZOURI] = CItem::Create(ITEM_ZOURI);
	// ひよこ---------------------------------------------------------
	// 敵を倒すと移動速度が125%上がり、1(+0.5)秒間消える	TODO
	m_item[ITEM_ZOURI]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_ARROW] = CItem::Create(ITEM_ARROW);
	// 矢---------------------------------------------------------
	// プライマリースキルを発動すると、矢も投げて、400%(+100%)の基礎ダメージを与える。
	// 最大3(+1)個の矢を持つことができ、10秒経つとリロードされる
	m_item[ITEM_ARROW]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_SEED] = CItem::Create(ITEM_SEED);
	// 種子---------------------------------------------------------
	// 攻撃ヒット時に体力を1回復する (回復量+1)
	m_item[ITEM_SEED]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		inCharacter->GetHp()->AddItemEffect(1);
	});
	//--------------------------------------------------------------

	m_item[ITEM_FETTERS] = CItem::Create(ITEM_FETTERS);
	// 足枷---------------------------------------------------------
	// 攻撃を当てた敵の移動速度が2秒間60%減少する (秒数 +2)
	m_item[ITEM_FETTERS]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_SHIELD] = CItem::Create(ITEM_SHIELD);
	// 盾---------------------------------------------------------
	// 走っている間はアーマーが30増加する (+30)
	m_item[ITEM_SHIELD]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_TABI] = CItem::Create(ITEM_TABI);
	// たび---------------------------------------------------------
	// 非戦闘時の移動速度 +30% (+30%)
	m_item[ITEM_TABI]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_FLINT] = CItem::Create(ITEM_FLINT);
	// 火打石---------------------------------------------------------
	// 発火の効果で、与えるダメージが時間の経過とともに+300%(+300%)以上増える
	m_item[ITEM_FLINT]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_FLOWER] = CItem::Create(ITEM_FLOWER);
	// 花---------------------------------------------------------
	// テレポーターイベント中近くの味方を50%回復するヒーリングノヴァを発する (+1回) 
	m_item[ITEM_FLOWER]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_IRON_WIRE] = CItem::Create(ITEM_IRON_WIRE);
	// 鉄線---------------------------------------------------------
	// ダメージを受けた際、周囲25m(+10m)以内にいる敵最大5体に160%のダメージを与える (+2体)
	m_item[ITEM_IRON_WIRE]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	m_item[ITEM_HANNYA] = CItem::Create(ITEM_HANNYA);
	// 般若面---------------------------------------------------------
	// 1秒以内に4体の敵を倒すと6秒間フレンジー状態になる。フレンジー発動中は移動速度が50%、攻撃速度が100%上昇する (+4秒)
	m_item[ITEM_HANNYA]->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------
}

//--------------------------------------------------------------
// 初期化
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

CItemDataBase::~CItemDataBase()
{
}

void CItemDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}
