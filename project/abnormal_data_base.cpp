#include "abnormal_data_base.h"
#include "abnormal.h"

#include "character.h"
#include "utility.h"

//==============================================================
// �ÓI�����o�[�ϐ��̐錾
//==============================================================
CAbnormalDataBase* CAbnormalDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CAbnormalDataBase::CAbnormalDataBase()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
void CAbnormalDataBase::Init()
{
	m_abnormal[ABNORMAL_FIRE] = CAbnormal::Create(ABNORMAL_FIRE);
	// �₯�Ǐ�� ==============================================================================================
	m_abnormal[ABNORMAL_FIRE]->SetWhenAddFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->AddUbnormalStack(ABNORMAL_FIRE);
		inCharacter->SetUbnormalTime(ABNORMAL_FIRE, 300);
		inCharacter->SetTargetInterval(ABNORMAL_FIRE, 20);
	});
	m_abnormal[ABNORMAL_FIRE]->SetWhenAllWayFunc([](CCharacter* inCharacter, int cnt)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		inCharacter->SetInterval(ABNORMAL_FIRE, 0);
		inCharacter->GetHp()->AddCurrent(-1 * ab_ct[cnt].s_stack);
	});
	m_abnormal[ABNORMAL_FIRE]->SetWhenAttackFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(ABNORMAL_FIRE);
		outCharacter->SetUbnormalTime(ABNORMAL_FIRE, 600);
		outCharacter->SetTargetInterval(ABNORMAL_FIRE, 20);
	});
	m_abnormal[ABNORMAL_FIRE]->SetWhenClearFunc([](CCharacter* inCharacter, int cnt)
	{
	});
	//==========================================================================================================

	m_abnormal[ABNORMAL_BLEED] = CAbnormal::Create(ABNORMAL_BLEED);
	// �o����� ================================================================================================
	m_abnormal[ABNORMAL_BLEED]->SetWhenAddFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->AddUbnormalStack(ABNORMAL_BLEED);
		inCharacter->SetUbnormalTime(ABNORMAL_BLEED, 300);
		inCharacter->SetTargetInterval(ABNORMAL_BLEED, 10);
	});
	m_abnormal[ABNORMAL_BLEED]->SetWhenAllWayFunc([](CCharacter* inCharacter, int cnt)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();
		
		// �t�^����Ă����Ԉُ��tik�𑝂₷
		inCharacter->SetInterval(ABNORMAL_BLEED, 0);
		inCharacter->GetHp()->AddCurrent(-2 * ab_ct[cnt].s_stack);
	});
	m_abnormal[ABNORMAL_BLEED]->SetWhenAttackFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(ABNORMAL_BLEED);
		outCharacter->SetUbnormalTime(ABNORMAL_BLEED, 600);
		outCharacter->SetTargetInterval(ABNORMAL_BLEED, 30);
	});
	m_abnormal[ABNORMAL_BLEED]->SetWhenClearFunc([](CCharacter* inCharacter, int cnt)
	{
	});
	//==========================================================================================================

	m_abnormal[ABNORMAL_STUN] = CAbnormal::Create(ABNORMAL_STUN);
	// �X�^����� ================================================================================================
	m_abnormal[ABNORMAL_STUN]->SetWhenAddFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->AddUbnormalStack(ABNORMAL_STUN);
		inCharacter->SetUbnormalTime(ABNORMAL_STUN, 60);
	});

	m_abnormal[ABNORMAL_STUN]->SetWhenAttackFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(ABNORMAL_STUN);
		outCharacter->SetUbnormalTime(ABNORMAL_STUN, 60);
		inCharacter->SetStun(true);
	});
	m_abnormal[ABNORMAL_STUN]->SetWhenAllWayFunc([](CCharacter* inCharacter, int cnt)
	{});

	m_abnormal[ABNORMAL_STUN]->SetWhenClearFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->SetStun(false);
	});
	//==========================================================================================================

	m_abnormal[ABNORMAL_SLOW] = CAbnormal::Create(ABNORMAL_SLOW);
	// �X���E��� ================================================================================================
	m_abnormal[ABNORMAL_SLOW]->SetWhenAddFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->AddUbnormalStack(ABNORMAL_SLOW);
		inCharacter->SetUbnormalTime(ABNORMAL_SLOW, 300);
		
		if (inCharacter->GetAbnormalCount()[cnt].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(-inCharacter->GetSpeed()->GetMax() * 0.5f);
		}
	});

	m_abnormal[ABNORMAL_SLOW]->SetWhenAttackFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		inCharacter->AddUbnormalStack(ABNORMAL_SLOW);
		inCharacter->SetUbnormalTime(ABNORMAL_SLOW, 300);
	
		if (inCharacter->GetAbnormalCount()[cnt].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(-inCharacter->GetSpeed()->GetMax() * 0.5f);
		}

	});
	m_abnormal[ABNORMAL_SLOW]->SetWhenAllWayFunc([](CCharacter* inCharacter, int cnt)
	{
	});

	m_abnormal[ABNORMAL_SLOW]->SetWhenClearFunc([](CCharacter* inCharacter, int cnt)
	{
		if (inCharacter->GetAbnormalCount()[cnt].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(inCharacter->GetSpeed()->GetMax() * 0.5f);
		}
	});
	//==========================================================================================================
}

//--------------------------------------------------------------
// ������
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
