﻿//**************************************************************
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
#include "arrow.h"
#include "flower.h"

#include "utility.h"

//==============================================================
// 静的メンバー変数の宣言
//==============================================================
CItemDataBase* CItemDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CItemDataBase::CItemDataBase() : m_countKill(0), m_maxAddLife(0)
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CItemDataBase::Init()
{
	CItem* item;

	// 全て生成だけしとく
	for (int i = 0; i < ITEM_MAX; i++)
	{
		m_item[i] = CItem::Create((EItemType)i);
		m_itemInfo[i][0] = "未記入----";
		m_itemInfo[i][1] = "--効果--\n改行";
		m_itemInfo[i][2] = "ITEM_DANGO_O1";
		m_item[i]->SetModel("BOX");
	}

	item = m_item[ITEM_DANGO];
	item->SetModel("ITEM_DANGO");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_DANGO][0] = "だんご";
	m_itemInfo[ITEM_DANGO][1] = "ＨＰが増える";
	m_itemInfo[ITEM_DANGO][2] = "ITEM_DANGO_O1";
	// だんごの設定-------------------------------------------------
	/* HP+50(+50)増加 */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetHp()->AddMax(50);
		inCharacter->GetHp()->AddItemEffect(50);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetHp()->AddMax(-50);
		inCharacter->GetHp()->AddItemEffect(-50);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_GETA];
	item->SetModel("ITEM_GETA");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_GETA][0] = "下駄";
	m_itemInfo[ITEM_GETA][1] = "移動速度が増える";
	m_itemInfo[ITEM_GETA][2] = "ITEM_GETA";
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
	m_itemInfo[ITEM_UMBRELLA][0] = "傘";
	m_itemInfo[ITEM_UMBRELLA][1] = "防御力が増える";
	m_itemInfo[ITEM_UMBRELLA][2] = "ITEM_UMBRELLA";
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
	m_itemInfo[ITEM_HYOUTAN][0] = "ひょうたん";
	m_itemInfo[ITEM_HYOUTAN][1] = "攻撃速度と移動速度が増える";
	m_itemInfo[ITEM_HYOUTAN][2] = "ITEM_HYOUTAN";
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
	m_itemInfo[ITEM_BANBOO_WATERBOX][0] = "竹の水筒";
	m_itemInfo[ITEM_BANBOO_WATERBOX][1] = "攻撃速度が増える";
	m_itemInfo[ITEM_BANBOO_WATERBOX][2] = "ITEM_BANBOO_WATERBOX";
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
	m_itemInfo[ITEM_OMAMORI][0] = "お守り";
	m_itemInfo[ITEM_OMAMORI][1] = "クリティカル率が増える";
	m_itemInfo[ITEM_OMAMORI][2] = "ITEM_OMAMORI";
	// お守り-------------------------------------------------------
	/* クリティカル率を10%(+10%)上昇させる。 */
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetCriticalRate()->AddItemEffect(0.1f);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	
		inCharacter->GetCriticalRate()->AddItemEffect(-0.1f);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KIBORI];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_KIBORI][0] = "熊の木彫り";
	m_itemInfo[ITEM_KIBORI][1] = "確率でブロックする";
	m_itemInfo[ITEM_KIBORI][2] = "ITEM_KIBORI";
	// 熊の木彫り---------------------------------------------
	item->SetWhenReceiveFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 15%(+15%)の確率でブロックする。
		for (int Cnt = 0; Cnt < cnt; Cnt++)
		{
			if (IsSuccessRate(0.15f))
			{// 15%の確率
				inCharacter->DamageBlock(true);
				break;
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_BAKUTIKU];
	item->SetModel("ITEM_BAKUTIKU");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_BAKUTIKU][0] = "ばくちく";
	m_itemInfo[ITEM_BAKUTIKU][1] = "スタンさせる";
	m_itemInfo[ITEM_BAKUTIKU][2] = "ITEM_BAKUTIKU";
	// ばくちく(保留)-----------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 攻撃時に5%の確率で敵を2秒間スタンさせる。
		for (int Cnt = 0; Cnt < cnt; Cnt++)
		{
			if (IsSuccessRate(0.05f))
			{// 5%の確率
				outCharacter->AddAbnormalStack(CAbnormalDataBase::ABNORMAL_STUN);
				break;
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_MAKIBISI];
	item->SetModel("ITEM_MAKIBISI");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_MAKIBISI][0] = "まきびし";
	m_itemInfo[ITEM_MAKIBISI][1] = "移動速度を低下させる";
	m_itemInfo[ITEM_MAKIBISI][2] = "ITEM_MAKIBISI";
	// まきびし-----------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 攻撃時に敵に移動速度-5%にする状態異常を付与する。
		for (int Cnt = 0; Cnt < cnt; Cnt++)
		{
			if (IsSuccessRate(0.05f))
			{// 攻撃時に5%の確率でスロウさせる。
				outCharacter->AddAbnormalStack(CAbnormalDataBase::ABNORMAL_SLOW);
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_DOSU];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_DOSU][0] = "ドス";
	m_itemInfo[ITEM_DOSU][1] = "敵を倒した時、回復する";
	m_itemInfo[ITEM_DOSU][2] = "ITEM_DOSU";
	// 首級---------------------------------------------------------
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒した時、HPの1%(+1%)を回復する。
		float percent = 0;
		for (int Cnt = 0; Cnt < cnt; Cnt++)
		{// 持ってる数、割合を増やす
			percent += 1;
		}

		// 最大体力を取得
		float hpMax = (float)inCharacter->GetHp()->GetMax();
		// 回復する値
		float recovery = hpMax * (percent / 100.0f);
		inCharacter->Heal((int)recovery);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KUNAI];
	item->SetModel("ITEM_KUNAI");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_KUNAI][0] = "クナイ";
	m_itemInfo[ITEM_KUNAI][1] = "体力が90%以上の敵に対して\nダメージが増加する";
	m_itemInfo[ITEM_KUNAI][2] = "ITEM_KUNAI";
	// クナイ---------------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 体力が90%以上の敵に対して70%(+70%)ダメージが増加する。
		// 最大体力を取得
		float hpMax = (float)outCharacter->GetHp()->GetMax();
		// 現在の体力
		float hpCurrent = (float)outCharacter->GetHp()->GetCurrent();

		// 体力の割合を計算
		float percent = (hpCurrent / hpMax * 100.0f);

		if (percent >= 90.0f)
		{// 相手の体力が90%以上だった時
			float addParcent = 0;

			for (int Cnt = 0; Cnt < cnt; Cnt++)
			{// 持ってる数、割合を増やす
				addParcent += 70;
			}
			float nowAtk = (float)inCharacter->GetAtk()->GetCurrent();
			float total = nowAtk * (addParcent / 100.0f);

			nowAtk += total;

			// ダメージの加算
			inCharacter->AddDamage(nowAtk);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KITUNEMEN];
	item->SetModel("ITEM_KITUNENOOMEN");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_KITUNEMEN][0] = "狐面";
	m_itemInfo[ITEM_KITUNEMEN][1] = "クリティカルヒットで攻撃速度が\n上昇する";
	m_itemInfo[ITEM_KITUNEMEN][2] = "ITEM_KITUNEMEN";
	// 狐面---------------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// クリティカルヒットで攻撃速度が12%上昇する。最大値は36% (+36%)。// TODO　未検証
		if (inCharacter->GetIsCritical())
		{
			float addAtkSpdPercent = 0;
			float numCritical = (float)inCharacter->GetNumCritical();

			for (int i = 0; i < numCritical; i++)
			{// ヒットした数足す
				addAtkSpdPercent += 12.0f;
			}

			float maxPercent = 0;

			for (int i = 0; i < cnt; i++)
			{// アイテムの所持数分、足す
				maxPercent += 36.0f;
			}

			if (maxPercent < addAtkSpdPercent)
			{// 上限を超えた場合
				addAtkSpdPercent = maxPercent;
			}

			// 現在のスピードを取得
			float currentAtkSpd = inCharacter->GetAtkSpd()->GetCurrent();
			// 増やす割合の計算
			float total = currentAtkSpd * (addAtkSpdPercent / 100.0f);
			
			currentAtkSpd += total;

			// 設定
			inCharacter->GetAtkSpd()->SetCurrent(currentAtkSpd);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KAZAGURUMA];
	item->SetModel("ITEM_KAZAGURUMA");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_KAZAGURUMA][0] = "風車";
	m_itemInfo[ITEM_KAZAGURUMA][1] = "敵を倒すと確率で全てのクールダウンを\nリセットする";
	m_itemInfo[ITEM_KAZAGURUMA][2] = "ITEM_KAZAGURUMA";
	// 風車---------------------------------------------------------
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒すと18%の確率で全てのクールダウンをリセットする
		for (int i = 0; i < cnt; i++)
		{
			if (IsSuccessRate(0.18f))
			{
				for (int j = 0; j < CCharacter::MAX_SKILL; j++)
				{
					inCharacter->GetSkill(j)->SetCT(0);
				}
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_KOBAN];
	item->SetModel("ITEM_KOBAN");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_KOBAN][0] = "小判";
	m_itemInfo[ITEM_KOBAN][1] = "敵を倒すと確率で金塊が出現する";
	m_itemInfo[ITEM_KOBAN][2] = "ITEM_KOBAN";
	// 小判---------------------------------------------------------
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵を倒した際4%の確率で金塊が出現する (+4%)
		float probability = 0.0f;

		for (int j = 0; j < cnt; j++)
		{
			probability += 0.04f;
		}

		if (IsSuccessRate(probability))
		{
			CGoldNugget* obj = CGoldNugget::Create();
			obj->SetPos(outCharacter->GetPos());
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_DENDENDAIKO];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_DENDENDAIKO][0] = "電電太鼓";
	m_itemInfo[ITEM_DENDENDAIKO][1] = "体力が一定以下になったエリートモンスターを\n即死させる";
	m_itemInfo[ITEM_DENDENDAIKO][2] = "ITEM_DENDENDAIKO";
	// 壊れた兜---------------------------------------------------------
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 体力が13%以下になったエリートモンスターを即死させる (+13%)
		if (outCharacter->GetIsElite())
		{
			float parcent = 0.0f;

			for (int i = 0; i < cnt; i++)
			{
				parcent += 13.0f;
			}

			// 一定の体力以下になった敵を殺す
			float hp = (float)outCharacter->GetHp()->GetMax();
			hp *= (parcent / 100.0f);

			float hpCurrent = (float)outCharacter->GetHp()->GetCurrent();

			if (hpCurrent <= hp)
			{// 現在の体力が規定値以下だったら
				outCharacter->GetHp()->AddItemEffect(-hp);
			}
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_CROW_FEATHER];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_CROW_FEATHER][0] = "カラスの羽";
	m_itemInfo[ITEM_CROW_FEATHER][1] = "ジャンプ回数が増える";
	m_itemInfo[ITEM_CROW_FEATHER][2] = "ITEM_CROW_FEATHER";
	// カラスの羽---------------------------------------------------------
	// ジャンプ回数 +1 (+1)	// なんか増えないなんで　TODO
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->GetJumpCount()->AddItemEffect(1);
	});
	item->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{ 
		inCharacter->GetJumpCount()->AddItemEffect(-1);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_TOISI];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_TOISI][0] = "砥石";
	m_itemInfo[ITEM_TOISI][1] = "クリティカル確率が上昇し、クリティカルが発生するごとに\n体力が回復する";
	m_itemInfo[ITEM_TOISI][2] = "ITEM_TOISI";
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
			for (int Cnt = 0; Cnt < cnt; Cnt++)
			{
				healHp += 8;
			}
			inCharacter->Heal(healHp);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_DRIP_BAG];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_DRIP_BAG][0] = "点滴袋";
	m_itemInfo[ITEM_DRIP_BAG][1] = "敵を倒すごとに体力が永続的に1増える";
	m_itemInfo[ITEM_DRIP_BAG][2] = "ITEM_DRIP_BAG";
	// 点滴袋---------------------------------------------------------
	// 敵を倒すごとに体力が永続的に1増える。最大100まで (最大 +100)
	item->SetWhenDeathFunc([this](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		// 最大値を決める
		m_maxAddLife = cnt * 100;
		// 敵を倒した数をカウント
		m_countKill++;

		if (m_countKill > m_maxAddLife)
		{// 最大値を超えたら増やさない
			return;
		}

		inCharacter->GetHp()->AddMax(1);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_CHICK];
	item->SetModel("ITEM_HIYOKO");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_CHICK][0] = "ひよこ";
	m_itemInfo[ITEM_CHICK][1] = "走りながらジャンプすると前方に飛び出す";
	m_itemInfo[ITEM_CHICK][2] = "ITEM_CHICK";
	// ひよこ---------------------------------------------------------
	// 走りながらジャンプすると前方に10m飛び出す (+10m)
	item->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{
		float forwardJumpPower = 0.0f;

		for (int Cnt = 0; Cnt < cnt; Cnt++)
		{
			forwardJumpPower += 10.0f;
		}

		inCharacter->SetForwardJumpPoewer(forwardJumpPower);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_ZOURI];
	item->SetModel("ITEM_ZOURI");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_ZOURI][0] = "草履";
	m_itemInfo[ITEM_ZOURI][1] = "敵を倒すとスピードが上がる";
	m_itemInfo[ITEM_ZOURI][2] = "ITEM_ZOURI";
	// 草履---------------------------------------------------------
	// 敵を倒すと移動速度が125%上がり、1(+0.5)秒間消える
	item->SetWhenDeathFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 敵が死んだら
		float nowSpeed = 0;
		nowSpeed = inCharacter->GetSpeed()->GetCurrent();
		nowSpeed *= 1.25f;

		int frame = 60;

		for (int i = 0; i < cnt; i++)
		{
			frame += 30;
		}

		// 加算
		inCharacter->SetAcceleration(nowSpeed);
		inCharacter->SetIsAccel(true);
		inCharacter->SetEffectTime(frame);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_SEED];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_SEED][0] = "種子";
	m_itemInfo[ITEM_SEED][1] = "攻撃ヒット時に体力を回復する";
	m_itemInfo[ITEM_SEED][2] = "ITEM_SEED";
	// 種子---------------------------------------------------------
	// 攻撃ヒット時に体力を1回復する (回復量+1)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		int heal = 0;

		for (int i = 0; i < cnt; i++)
		{
			heal += 1;
		}

		inCharacter->Heal(heal);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FETTERS];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_FETTERS][0] = "足枷";
	m_itemInfo[ITEM_FETTERS][1] = "攻撃を当てた敵の移動速度が減少する";
	m_itemInfo[ITEM_FETTERS][2] = "ITEM_FETTERS";
	// 足枷---------------------------------------------------------
	// 攻撃を当てた敵の移動速度が2秒間60%減少する (秒数 +2)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO 逆に早くなってる？
		outCharacter->AddAbnormalStack(CAbnormalDataBase::ABNORMAL_SLOW);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_WADAIKO];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_WADAIKO][0] = "和太鼓";
	m_itemInfo[ITEM_WADAIKO][1] = "非戦闘時の移動速度があがる";
	m_itemInfo[ITEM_WADAIKO][2] = "ITEM_WADAIKO";
	// たび---------------------------------------------------------
	// 非戦闘時の移動速度 +30% (+30%)
	item->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{
		if (inCharacter->GetIsNonCombat())
		{
			float speed = inCharacter->GetSpeed()->GetCurrent();

			int addParcent = 0;
			for (int Cnt = 0; Cnt < cnt; Cnt++)
			{
				addParcent += 30;
			}

			float speedUp = speed * (addParcent / 100.0f);
			inCharacter->SetNonComAddSpeed(speed);
			inCharacter->SetEffectTime(5);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FLOWER];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_FLOWER][0] = "花";
	m_itemInfo[ITEM_FLOWER][1] = "テレポーターイベント中近くの味方を\n回復するヒーリングノヴァを生成する";
	m_itemInfo[ITEM_FLOWER][2] = "ITEM_FLOWER";
	// 花---------------------------------------------------------
	// テレポーターイベント中近くの味方を50%回復するヒーリングノヴァを発する (+1回) 
	item->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{
		if (inCharacter->GetIsTeleporter())
		{// 起動したら
			float radius = (float)cnt * 300;	// 値調整　TODO
			CFlower* obj = CFlower::Create(inCharacter->GetPos(), radius);
			inCharacter->SetIsTeleporter(false);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_ELITE];
	item->SetRerity(RARITY_NOSELECT);
	m_itemInfo[ITEM_ELITE][0] = "エリート";
	m_itemInfo[ITEM_ELITE][1] = "持っているものはエリートになる";
	m_itemInfo[ITEM_ELITE][2] = "ITEM_DANGO_O1";
	// エリート---------------------------------------------------------
	// 持っているものはエリートになる
	item->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
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

	return S_OK;
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
	CTask::Uninit();
	if (m_instance != nullptr)
	{
		m_instance = nullptr;
	}
}
