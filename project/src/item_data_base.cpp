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
	m_item[ITEM_POWER_UP] = CItem::Create(ITEM_POWER_UP);
	m_item[ITEM_POWER_UP]->SetModel("BOX");
	// ジャンプ回数上昇アイテムの設定-----------------------------
	// * ジャンプ回数 +1(+1) *
	m_item[ITEM_POWER_UP]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetJumpCount()->AddItemEffect(1); });
	m_item[ITEM_POWER_UP]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetJumpCount()->AddItemEffect(-1); });
	//--------------------------------------------------------------

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
			// 15%の確率でブロックする。
			if (IsSuccessRate(0.15f))
			{
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
			// 攻撃時に5%の確率でスタンさせる。
			if (IsSuccessRate(0.05f))
			{
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
		int percent = 1;
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
			int addParcent = 70;

			for (int Cnt = 0; Cnt <= cnt; Cnt++)
			{// 持ってる数、割合を増やす
				addParcent += 70;
			}

			// TODO　ダメージ計算
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
			int percent = 8;

			for (int Cnt = 0; Cnt <= cnt; Cnt++)
			{// 持ってる数、割合を増やす
				percent += 8;
			}

			int addShield = (int)(hpMax * (percent / 100));

			// プレイヤーのシールドに加算する処理
			inCharacter->GetBarrier()->SetCurrent(addShield);
		}
	});

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
