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
void CItemDataBase::Init()
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
	m_itemInfo[ITEM_GETA][2] = "ITEM_DANGO_O2";
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
	m_itemInfo[ITEM_UMBRELLA][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_HYOUTAN][2] = "ITEM_DANGO_O3";
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
	m_itemInfo[ITEM_BANBOO_WATERBOX][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_OMAMORI][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_KIBORI][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_BAKUTIKU][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_MAKIBISI][2] = "ITEM_DANGO_O1";
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

	item = m_item[ITEM_HEAD];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_HEAD][0] = "首級";
	m_itemInfo[ITEM_HEAD][1] = "敵を倒した時、回復する";
	m_itemInfo[ITEM_HEAD][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_KUNAI][2] = "ITEM_DANGO_O1";
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

	item = m_item[ITEM_FUR];
	item->SetModel("BOX");
	item->SetRerity(RARITY_COMMON);
	m_itemInfo[ITEM_FUR][0] = "毛皮";
	m_itemInfo[ITEM_FUR][1] = "シールドを得る";
	m_itemInfo[ITEM_FUR][2] = "ITEM_DANGO_O1";
	// 毛皮---------------------------------------------------------
	item->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{// 最大体力の8%のシールドを得る。	// TODO　未検証
		if (inCharacter->GetIsShield())
		{// シールドを回復する状態の時
			// 最大体力を取得
			int hpMax = inCharacter->GetHp()->GetMax();

			// 増やす割合
			int percent = 0;

			for (int Cnt = 0; Cnt < cnt; Cnt++)
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
	m_itemInfo[ITEM_KITUNEMEN][0] = "狐面";
	m_itemInfo[ITEM_KITUNEMEN][1] = "クリティカルヒットで攻撃速度が\n上昇する";
	m_itemInfo[ITEM_KITUNEMEN][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_KAZAGURUMA][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_KOBAN][2] = "ITEM_DANGO_O1";
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

	item = m_item[ITEM_ONIMEN];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_ONIMEN][0] = "鬼面";
	m_itemInfo[ITEM_ONIMEN][1] = "4つ以上のデバフがついた敵に死の印が付き、\n受けるダメージが増加する";
	m_itemInfo[ITEM_ONIMEN][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_BROKEN_KABUTO][0] = "壊れた兜";
	m_itemInfo[ITEM_BROKEN_KABUTO][1] = "体力が一定以下になったエリートモンスターを\n即死させる";
	m_itemInfo[ITEM_BROKEN_KABUTO][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_CROW_FEATHER][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_TOISI][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_DRIP_BAG][2] = "ITEM_DANGO_O1";
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

	// ↑チェック済み-----------------------------------------------
	item = m_item[ITEM_CHICK];
	item->SetModel("ITEM_HIYOKO");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_CHICK][0] = "ひよこ";
	m_itemInfo[ITEM_CHICK][1] = "走りながらジャンプすると前方に飛び出す";
	m_itemInfo[ITEM_CHICK][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_ZOURI][0] = "草履";
	m_itemInfo[ITEM_ZOURI][1] = "敵を倒すと移動速度が一定時間上がる";
	m_itemInfo[ITEM_ZOURI][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_ARROW][0] = "矢";
	m_itemInfo[ITEM_ARROW][1] = "敵を倒すと移動速度が一定時間上がる";
	m_itemInfo[ITEM_ARROW][2] = "ITEM_DANGO_O1";
	// 矢---------------------------------------------------------
	// プライマリースキルを発動すると、矢も投げて、400%(+100%)の基礎ダメージを与える。
	// 最大3(+1)個の矢を持つことができ、10秒経つとリロードされる
	item->SetWhenUseSkill([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 矢を発射 TODO
		//inCharacter->GetRot()
		//CArrow* obj = CArrow::Create();
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_SEED];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_SEED][0] = "種子";
	m_itemInfo[ITEM_SEED][1] = "攻撃ヒット時に体力を回復する";
	m_itemInfo[ITEM_SEED][2] = "ITEM_DANGO_O1";
	// 種子---------------------------------------------------------
	// 攻撃ヒット時に体力を1回復する (回復量+1)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		inCharacter->Heal(1);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FETTERS];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_FETTERS][0] = "足枷";
	m_itemInfo[ITEM_FETTERS][1] = "攻撃を当てた敵の移動速度が減少する";
	m_itemInfo[ITEM_FETTERS][2] = "ITEM_DANGO_O1";
	// 足枷---------------------------------------------------------
	// 攻撃を当てた敵の移動速度が2秒間60%減少する (秒数 +2)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// 
		outCharacter->AddAbnormalStack(CAbnormalDataBase::ABNORMAL_SLOW);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_SHIELD];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_SHIELD][0] = "盾";
	m_itemInfo[ITEM_SHIELD][1] = "走っている間はアーマーが増加する";
	m_itemInfo[ITEM_SHIELD][2] = "ITEM_DANGO_O1";
	// 盾---------------------------------------------------------
	// 走っている間はアーマーが30増加する (+30)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		if (inCharacter->GetIsRunning())
		{
			int armor = 0;

			for (int Cnt = 0; Cnt < cnt; Cnt++)
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
	m_itemInfo[ITEM_TABI][0] = "たび";
	m_itemInfo[ITEM_TABI][1] = "非戦闘時の移動速度があがる";
	m_itemInfo[ITEM_TABI][2] = "ITEM_DANGO_O1";
	// たび---------------------------------------------------------
	// 非戦闘時の移動速度 +30% (+30%) // TODO
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

			speed += speed * (addParcent / 100);
			inCharacter->GetSpeed()->SetCurrent(speed);
		}
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_FLINT];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_FLINT][0] = "火打石";
	m_itemInfo[ITEM_FLINT][1] = "発火の効果で、与えるダメージが時間の経過とともに増える";
	m_itemInfo[ITEM_FLINT][2] = "ITEM_DANGO_O1";
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
	m_itemInfo[ITEM_FLOWER][0] = "花";
	m_itemInfo[ITEM_FLOWER][1] = "テレポーターイベント中近くの味方を\n回復するヒーリングノヴァを生成する";
	m_itemInfo[ITEM_FLOWER][2] = "ITEM_DANGO_O1";
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

	item = m_item[ITEM_IRON_WIRE];
	item->SetModel("BOX");
	item->SetRerity(RARITY_UNCOMMON);
	m_itemInfo[ITEM_IRON_WIRE][0] = "鉄線";
	m_itemInfo[ITEM_IRON_WIRE][1] = "ダメージを受けた際、周囲の敵にダメージを与える";
	m_itemInfo[ITEM_IRON_WIRE][2] = "ITEM_DANGO_O1";
	// 鉄線---------------------------------------------------------
	// ダメージを受けた際、周囲25m(+10m)以内にいる敵最大5体に160%のダメージを与える (+2体)
	item->SetWhenReceiveFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
	});
	//--------------------------------------------------------------

	item = m_item[ITEM_HANNYA];
	item->SetModel("BOX");
	item->SetRerity(RARITY_RARE);
	m_itemInfo[ITEM_IRON_WIRE][0] = "般若面";
	m_itemInfo[ITEM_IRON_WIRE][1] = "1秒以内に4体の敵を倒すと6秒間フレンジー状態になる";
	m_itemInfo[ITEM_IRON_WIRE][2] = "ITEM_DANGO_O1";
	// 般若面---------------------------------------------------------
	// 1秒以内に4体の敵を倒すと6秒間フレンジー状態になる。フレンジー発動中は移動速度が50%、攻撃速度が100%上昇する (+4秒)
	item->SetWhenInflictFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{// TODO
		//inCharacter->GetCriticalRate()->AddItemEffect(5);
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
