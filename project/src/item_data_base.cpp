#include "item_data_base.h"
#include "item.h"

#include "character.h"

//==============================================================
// �ÓI�����o�[�ϐ��̐錾
//==============================================================
CItemDataBase* CItemDataBase::m_instance(nullptr);

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CItemDataBase::CItemDataBase()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
void CItemDataBase::Init()
{
	m_item[ITEM_POWER_UP] = CItem::Create(ITEM_POWER_UP);
	
	// �W�����v�񐔏㏸�A�C�e���̐ݒ�
	m_item[ITEM_POWER_UP]->SetWhenPickFunc([](CCharacter* inCharacter,int cnt)
	{
		CStatus<unsigned int> jumpCount = inCharacter->GetJumpCount();
		jumpCount.AddItemEffect(1);
		inCharacter->SetJumpCount(jumpCount);
	});

	m_item[ITEM_DANGO] = CItem::Create(ITEM_DANGO);

	// ���񂲂̐ݒ�
	m_item[ITEM_DANGO]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{
		CStatus<int> HPup = *inCharacter->GetHp();
		HPup.AddItemEffect(50);
		inCharacter->SetHp(HPup);
	});

	m_item[ITEM_GETA] = CItem::Create(ITEM_GETA);

	// ���ʂ̐ݒ�
	m_item[ITEM_GETA]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{
		CStatus<float> Spdup = inCharacter->GeSpeed();
		Spdup.AddItemEffect(1.2f);
		inCharacter->SetSpeed(Spdup);
	});
}

//--------------------------------------------------------------
// ������
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
