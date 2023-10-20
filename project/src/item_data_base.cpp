#include "item_data_base.h"
#include "item.h"

#include "character.h"

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

	// ジャンプ回数上昇アイテムの設定-----------------------------
	m_item[ITEM_POWER_UP]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetJumpCount()->AddItemEffect(1); });
	m_item[ITEM_POWER_UP]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetJumpCount()->AddItemEffect(-1); });

	m_item[ITEM_DANGO] = CItem::Create(ITEM_DANGO);
	//--------------------------------------------------------------

	// だんごの設定-------------------------------------------------
	m_item[ITEM_DANGO]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetHp()->AddItemEffect(50); });
	m_item[ITEM_DANGO]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetHp()->AddItemEffect(-50); });
	//--------------------------------------------------------------

	// 下駄の設定----------------------------------------------------
	m_item[ITEM_GETA]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetSpeed()->AddItemEffect(0.15f); });
	m_item[ITEM_GETA]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetSpeed()->AddItemEffect(-0.15f); });
	//--------------------------------------------------------------

	// 傘の設定-----------------------------------------------------
	m_item[ITEM_UMBRELLA]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetDefense()->AddItemEffect(5); });
	m_item[ITEM_UMBRELLA]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetDefense()->AddItemEffect(-5); });
	//--------------------------------------------------------------

	// ひょうたん---------------------------------------------------
	m_item[ITEM_HYOUTAN]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.075f); 
		inCharacter->GetSpeed()->AddItemEffect(0.075f); });
	m_item[ITEM_HYOUTAN]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.075f);
	inCharacter->GetSpeed()->AddItemEffect(-0.075f); });
	//--------------------------------------------------------------

	// 竹の水筒-----------------------------------------------------
	m_item[ITEM_BANBOO_WATERBOX]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.15f);});
	m_item[ITEM_BANBOO_WATERBOX]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.15f); });
	//--------------------------------------------------------------


	// お守り-------------------------------------------------------
	m_item[ITEM_OMAMORI]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.1f); });
	m_item[ITEM_OMAMORI]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.1f); });
	//--------------------------------------------------------------

	// 熊の木彫り(保留)---------------------------------------------
	m_item[ITEM_KIBORI]->SetWhenDamageFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		// 15%の確率でブロックする。
	});
	//--------------------------------------------------------------

	// ばくちく(保留)-----------------------------------------------
	m_item[ITEM_BAKUTIKU]->SetWhenHitFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		// 攻撃時に5%の確率でスタンさせる。
	});
	//--------------------------------------------------------------

	// まきびし-----------------------------------------------------
	m_item[ITEM_MAKIBISI]->SetWhenHitFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		// 攻撃時に敵に移動速度-5%にする状態異常を付与する。
	});
	//--------------------------------------------------------------

	// 首級---------------------------------------------------------
	m_item[ITEM_HEAD]->SetWhenHitFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{

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
