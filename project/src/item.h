//**************************************************************
//
// item
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ITEM_DATA_H_
#define _ITEM_DATA_H_

//==============================================================
// include
//==============================================================
#include "task.h"
#include "character.h"
#include "item_data_base.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;

//==============================================================
// �N���X
//==============================================================
class CItem : public CTask
{
public:
	using ITEM_FUNC = void(*)(CCharacter*, int);
	using ITEM_ACTION_FUNC = void(*)(CCharacter*, int, CCharacter*);
public:
	CItem(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItem();

	HRESULT Init() override;
	void Uninit() override;
	void Draw() override {}

	static CItem* Create(CItemDataBase::EItemType inId);

	void SetWhenPickFunc(ITEM_FUNC inFunc) { m_getFunc = inFunc; }				// ���肵���Ƃ��̏���
	void SetWhenLostFunc(ITEM_FUNC inFunc) { m_lostFunc = inFunc; }				// �������Ƃ��̏���
	void SetWhenAlwaysFunc(ITEM_FUNC inFunc) { m_allwayFunc = inFunc; }			// �펞�������Ă��鏈��
	void SetWhenDeathFunc(ITEM_ACTION_FUNC inFunc) { m_deathFunc = inFunc; }	// ���S�������Ƃ��̏���
	void SetWhenReceiveFunc(ITEM_ACTION_FUNC inFunc) { m_receiveFunc = inFunc; }	// �_���[�W���󂯂鎞�̏���
	void SetWhenInflictFunc(ITEM_ACTION_FUNC inFunc) { m_inflictFunc = inFunc; }	// �_���[�W��^�������̏���
	void SetModel(std::string str) { m_itemModelData = str; }

	ITEM_FUNC GetWhenPickFunc() { return m_getFunc; }
	ITEM_FUNC GetWhenLostFunc() { return m_lostFunc; }
	ITEM_FUNC GetWhenAllWayFunc() { return m_allwayFunc; }
	ITEM_ACTION_FUNC GetWhenDeathFunc() { return m_deathFunc; }
	ITEM_ACTION_FUNC GetWhenReceiveFunc() { return m_receiveFunc; }
	ITEM_ACTION_FUNC GetWhenInflictFunc() { return m_inflictFunc; }
	std::string GetModel() { return m_itemModelData; }

	// ���A���e�B
	void SetRerity(CItemDataBase::ERarity inRarity) { m_rarity = inRarity; }
	CItemDataBase::ERarity GetRerity() { return m_rarity; }

private:
	ITEM_FUNC m_getFunc;
	ITEM_FUNC m_lostFunc;
	ITEM_FUNC m_allwayFunc;

	ITEM_ACTION_FUNC m_deathFunc;
	ITEM_ACTION_FUNC m_receiveFunc;
	ITEM_ACTION_FUNC m_inflictFunc;

	std::string m_itemModelData;

	CItemDataBase::ERarity m_rarity;
};
#endif	// _ITEM_DATA_H_