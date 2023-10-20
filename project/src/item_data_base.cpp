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

	// �W�����v�񐔏㏸�A�C�e���̐ݒ�-----------------------------
	m_item[ITEM_POWER_UP]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetJumpCount()->AddItemEffect(1); });
	m_item[ITEM_POWER_UP]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetJumpCount()->AddItemEffect(-1); });

	m_item[ITEM_DANGO] = CItem::Create(ITEM_DANGO);
	//--------------------------------------------------------------

	// ���񂲂̐ݒ�-------------------------------------------------
	m_item[ITEM_DANGO]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetHp()->AddItemEffect(50); });
	m_item[ITEM_DANGO]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetHp()->AddItemEffect(-50); });
	//--------------------------------------------------------------

	// ���ʂ̐ݒ�----------------------------------------------------
	m_item[ITEM_GETA]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetSpeed()->AddItemEffect(0.15f); });
	m_item[ITEM_GETA]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetSpeed()->AddItemEffect(-0.15f); });
	//--------------------------------------------------------------

	// �P�̐ݒ�-----------------------------------------------------
	m_item[ITEM_UMBRELLA]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetDefense()->AddItemEffect(5); });
	m_item[ITEM_UMBRELLA]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetDefense()->AddItemEffect(-5); });
	//--------------------------------------------------------------

	// �Ђ傤����---------------------------------------------------
	m_item[ITEM_HYOUTAN]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.075f); 
		inCharacter->GetSpeed()->AddItemEffect(0.075f); });
	m_item[ITEM_HYOUTAN]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.075f);
	inCharacter->GetSpeed()->AddItemEffect(-0.075f); });
	//--------------------------------------------------------------

	// �|�̐���-----------------------------------------------------
	m_item[ITEM_BANBOO_WATERBOX]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.15f);});
	m_item[ITEM_BANBOO_WATERBOX]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.15f); });
	//--------------------------------------------------------------


	// �����-------------------------------------------------------
	m_item[ITEM_OMAMORI]->SetWhenPickFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(0.1f); });
	m_item[ITEM_OMAMORI]->SetWhenLostFunc([](CCharacter* inCharacter, int cnt)
	{	inCharacter->GetAtkSpd()->AddItemEffect(-0.1f); });
	//--------------------------------------------------------------

	// �F�̖ؒ���(�ۗ�)---------------------------------------------
	m_item[ITEM_KIBORI]->SetWhenDamageFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		// 15%�̊m���Ńu���b�N����B
	});
	//--------------------------------------------------------------

	// �΂�����(�ۗ�)-----------------------------------------------
	m_item[ITEM_BAKUTIKU]->SetWhenHitFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		// �U������5%�̊m���ŃX�^��������B
	});
	//--------------------------------------------------------------

	// �܂��т�-----------------------------------------------------
	m_item[ITEM_MAKIBISI]->SetWhenHitFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{
		// �U�����ɓG�Ɉړ����x-5%�ɂ����Ԉُ��t�^����B
	});
	//--------------------------------------------------------------

	// ��---------------------------------------------------------
	m_item[ITEM_HEAD]->SetWhenHitFunc([](CCharacter* inCharacter, int cnt, CCharacter* outCharacter)
	{

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
