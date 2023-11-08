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
	// �₯�Ǐ�� ----------------------------------------------
	m_abnormal[ABNORMAL_FIRE]->SetWhenAddFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->AddUbnormalStack(ABNORMAL_FIRE);
		inCharacter->SetUbnormalTime(ABNORMAL_FIRE, 60);
	});
	m_abnormal[ABNORMAL_FIRE]->SetWhenAlwaysFunc([](CCharacter* inCharacter, int cnt)
	{
		inCharacter->GetHp()->AddCurrent(-1);
	});

	//----------------------------------------------------------
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
