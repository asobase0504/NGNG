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
	//========================================================================================================
	// �₯�Ǐ�� 
	// ���� : ���b2(*�X�^�b�N��)�̃_���[�W��^����
	//========================================================================================================
	m_abnormal[ABNORMAL_FIRE] = CAbnormal::Create(ABNORMAL_FIRE);
	// �J�n
	m_abnormal[ABNORMAL_FIRE]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 300);
		inCharacter->SetTargetInterval(id, 20);
	});
	// �펞
	m_abnormal[ABNORMAL_FIRE]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent(-1 * ab_ct[id].s_stack);
	});
	// ����������
	m_abnormal[ABNORMAL_FIRE]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 20);
	});
	// ��������
	m_abnormal[ABNORMAL_FIRE]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{});

	//========================================================================================================
	// ������ 
	// ���� : ���b�ő�̗͂�10%�����_���[�W��^����
	//========================================================================================================
	m_abnormal[ABNORMAL_BURN] = CAbnormal::Create(ABNORMAL_BURN);
	// �J�n
	m_abnormal[ABNORMAL_BURN]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 180);
		inCharacter->SetTargetInterval(id, 60);
	});
	// �펞
	m_abnormal[ABNORMAL_BURN]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent((inCharacter->GetHp()->GetMax() * 0.1f) * ab_ct[id].s_stack);
	});
	// �U��
	m_abnormal[ABNORMAL_BURN]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// ����
	m_abnormal[ABNORMAL_BURN]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});

	//========================================================================================================
	// �₯�Ǐ�� 
	// ���� : 1�b����2(*�X�^�b�N��)�̃_���[�W��^����
	//========================================================================================================
	m_abnormal[ABNORMAL_BLEED] = CAbnormal::Create(ABNORMAL_BLEED);

	// �J�n
	m_abnormal[ABNORMAL_BLEED]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 600);
		inCharacter->SetTargetInterval(id, 60);
	});
	// �펞
	m_abnormal[ABNORMAL_BLEED]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();
		
		// �t�^����Ă����Ԉُ��tik�𑝂₷
		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent(-2 * ab_ct[id].s_stack);
	});
	// �U��
	m_abnormal[ABNORMAL_BLEED]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// ����
	m_abnormal[ABNORMAL_BLEED]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});

	//========================================================================================================
	// �X�^�����
	// ���� : �ꎞ�I�ɍs���s�\�ɂȂ�
	//========================================================================================================
	m_abnormal[ABNORMAL_STUN] = CAbnormal::Create(ABNORMAL_STUN);
	
	// �J�n
	m_abnormal[ABNORMAL_STUN]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		CCharacter* c = inCharacter;
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 60);
	});

	// �U��
	m_abnormal[ABNORMAL_STUN]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 60);
		inCharacter->SetStun(true);
	});
	// �펞
	m_abnormal[ABNORMAL_STUN]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{});
	// ����
	m_abnormal[ABNORMAL_STUN]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->SetStun(false);
	});

	//==========================================================================================================
	// �X���E��� 
	// ���� : ��Ԉُ�ɂ��������L�����N�^�[�̈ړ����x��-50%����
	//==========================================================================================================
	m_abnormal[ABNORMAL_SLOW] = CAbnormal::Create(ABNORMAL_SLOW);

	// �J�n
	m_abnormal[ABNORMAL_SLOW]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 300);
		
		if (inCharacter->GetAbnormalCount()[id].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(-inCharacter->GetSpeed()->GetMax() * 0.5f);
		}
	});
	// �U��
	m_abnormal[ABNORMAL_SLOW]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 300);
	
		if (inCharacter->GetAbnormalCount()[id].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(-inCharacter->GetSpeed()->GetMax() * 0.5f);
		}

	});
	// �펞
	m_abnormal[ABNORMAL_SLOW]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
	});
	// ����
	m_abnormal[ABNORMAL_SLOW]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
		if (inCharacter->GetAbnormalCount()[id].s_stack == 1)
		{
			inCharacter->GetSpeed()->AddCurrent(inCharacter->GetSpeed()->GetMax() * 0.5f);
		}
	});

	//========================================================================================================
	// �ŏ��
	// ���� : ���b�����_���[�W��^����
	//========================================================================================================
	m_abnormal[ABNORMAL_POISON] = CAbnormal::Create(ABNORMAL_POISON);

	// �J�n
	m_abnormal[ABNORMAL_POISON]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 600);
		inCharacter->SetTargetInterval(id, 60);
	});
	// �펞
	m_abnormal[ABNORMAL_POISON]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		// �t�^����Ă����Ԉُ��tik�𑝂₷
		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent((inCharacter->GetHp()->GetMax() * 0.05f) * ab_ct[id].s_stack);
	});
	// �U��
	m_abnormal[ABNORMAL_POISON]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// ����
	m_abnormal[ABNORMAL_POISON]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});

	//========================================================================================================
	// �u�a���
	// ���� : ���bHP��2(*�X�^�b�N��)�̃_���[�W��^����
	//========================================================================================================
	m_abnormal[ABNORMAL_PLAGUE] = CAbnormal::Create(ABNORMAL_PLAGUE);

	// �J�n
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenAddFunc([](CCharacter* inCharacter, int id)
	{
		inCharacter->AddUbnormalStack(id);
		inCharacter->SetUbnormalTime(id, 600);
		inCharacter->SetTargetInterval(id, 60);
	});
	// �펞
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenAllWayFunc([](CCharacter* inCharacter, int id)
	{
		abnormal_count ab_ct = inCharacter->GetAbnormalCount();

		// �t�^����Ă����Ԉُ��tik�𑝂₷
		inCharacter->SetInterval(id, 0);
		inCharacter->GetHp()->AddCurrent((-2 * ab_ct[id].s_stack) * ab_ct[id].s_stack);
	});
	// �U��
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenAttackFunc([](CCharacter* inCharacter, int id, CCharacter* outCharacter)
	{
		outCharacter->AddUbnormalStack(id);
		outCharacter->SetUbnormalTime(id, 600);
		outCharacter->SetTargetInterval(id, 60);
	});
	// ����
	m_abnormal[ABNORMAL_PLAGUE]->SetWhenClearFunc([](CCharacter* inCharacter, int id)
	{
	});
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
