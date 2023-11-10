#include "abnormal_data_base.h"
#include "abnormal.h"

#include "character.h"
#include "utility.h"

//==============================================================
// 静的メンバー変数の宣言
//==============================================================
CAbnormalDataBase* CAbnormalDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CAbnormalDataBase::CAbnormalDataBase()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
void CAbnormalDataBase::Init()
{
	//========================================================================================================
	// やけど状態 
	// 効果 : 毎秒2(*スタック数)のダメージを与える
	//========================================================================================================
	m_abnormal[ABNORMAL_FIRE] = CAbnormal::Create(ABNORMAL_FIRE);
	// 開始
	m_abnormal[ABNORMAL_FIRE]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 300);
		inCharacter->SetTargetInterval(id, 20);
	});
	// 常時
	m_abnormal[ABNORMAL_FIRE]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent(-1 * ab_ct[id].s_stack);
	});
	// 当たった時
	m_abnormal[ABNORMAL_FIRE]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 20);
	});
	// 失った時
	m_abnormal[ABNORMAL_FIRE]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{});

	//========================================================================================================
	// 炎上状態 
	// 効果 : 毎秒最大体力の10%を削るダメージを与える
	//========================================================================================================
	m_abnormal[ABNORMAL_BURN] = CAbnormal::Create(ABNORMAL_BURN);
	// 開始
	m_abnormal[ABNORMAL_BURN]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 180);
		inCharacter->SetTargetInterval(id, 60);
	});
	// 常時
	m_abnormal[ABNORMAL_BURN]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent((inCharacter->GetHp()->GetMax() * 0.1f) * ab_ct[id].s_stack);
	});
	// 攻撃
	m_abnormal[ABNORMAL_BURN]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// 消失
	m_abnormal[ABNORMAL_BURN]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});

	//========================================================================================================
	// やけど状態 
	// 効果 : 1秒毎に2(*スタック数)のダメージを与える
	//========================================================================================================
	m_abnormal[ABNORMAL_BLEED] = CAbnormal::Create(ABNORMAL_BLEED);

	// 開始
	m_abnormal[ABNORMAL_BLEED]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 600);
		inCharacter->SetTargetInterval(id, 60);
	});
	// 常時
	m_abnormal[ABNORMAL_BLEED]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();
		
		// 付与されている状態異常のtikを増やす
		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent(-2 * ab_ct[id].s_stack);
	});
	// 攻撃
	m_abnormal[ABNORMAL_BLEED]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// 消失
	m_abnormal[ABNORMAL_BLEED]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});

	//========================================================================================================
	// スタン状態
	// 効果 : 一時的に行動不能になる
	//========================================================================================================
	m_abnormal[ABNORMAL_STUN] = CAbnormal::Create(ABNORMAL_STUN);
	
	// 開始
	m_abnormal[ABNORMAL_STUN]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		CCharacter* c = inCharacter;
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 60);
	});

	// 攻撃
	m_abnormal[ABNORMAL_STUN]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 60);
		inCharacter->SetStun(true);
	});
	// 常時
	m_abnormal[ABNORMAL_STUN]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{});
	// 消失
	m_abnormal[ABNORMAL_STUN]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->SetStun(false);
	});

	//==========================================================================================================
	// スロウ状態 
	// 効果 : 状態異常にかかったキャラクターの移動速度を-50%する
	//==========================================================================================================
	m_abnormal[ABNORMAL_SLOW] = CAbnormal::Create(ABNORMAL_SLOW);

	// 開始
	m_abnormal[ABNORMAL_SLOW]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 300);
		
		if (inCharacter->GetAbnormalCount()[id].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(-inCharacter->GetSpeed()->GetMax() * 0.5f);
		}
	});
	// 攻撃
	m_abnormal[ABNORMAL_SLOW]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 300);
	
		if (inCharacter->GetAbnormalCount()[id].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(-inCharacter->GetSpeed()->GetMax() * 0.5f);
		}

	});
	// 常時
	m_abnormal[ABNORMAL_SLOW]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
	});
	// 消失
	m_abnormal[ABNORMAL_SLOW]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
		if (inCharacter->GetAbnormalCount()[id].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(inCharacter->GetSpeed()->GetMax() * 0.5f);
		}
	});

	//========================================================================================================
	// 毒状態
	// 効果 : 毎秒割合ダメージを与える
	//========================================================================================================
	m_abnormal[ABNORMAL_POISON] = CAbnormal::Create(ABNORMAL_POISON);

	// 開始
	m_abnormal[ABNORMAL_POISON]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 600);
		inCharacter->SetTargetInterval(id, 60);
	});
	// 常時
	m_abnormal[ABNORMAL_POISON]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		// 付与されている状態異常のtikを増やす
		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent((inCharacter->GetHp()->GetMax() * 0.05f) * ab_ct[id].s_stack);
	});
	// 攻撃
	m_abnormal[ABNORMAL_POISON]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// 消失
	m_abnormal[ABNORMAL_POISON]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});

	//========================================================================================================
	// 疫病状態
	// 効果 : 毎秒HPの2(*スタック数)のダメージを与える
	//========================================================================================================
	m_abnormal[ABNORMAL_PLAGUE] = CAbnormal::Create(ABNORMAL_PLAGUE);

	// 開始
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 600);
		inCharacter->SetTargetInterval(id, 60);
	});
	// 常時
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		// 付与されている状態異常のtikを増やす
		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent((-2 * ab_ct[id].s_stack) * ab_ct[id].s_stack);
	});
	// 攻撃
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// 消失
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
CAbnormalDataBase * CAbnormalDataBase::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CAbnormalDataBase;

		assert(m_instance != nullptr);

		m_instance->Init();
	}

	return m_instance;
}

CAbnormalDataBase::~CAbnormalDataBase()
{
}

void CAbnormalDataBase::Uninit()
{
	if (m_instance == nullptr)
	{
		return;
	}

	delete m_instance;
	m_instance = nullptr;
}
