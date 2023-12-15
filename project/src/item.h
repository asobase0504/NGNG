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
// 前方宣言
//==============================================================
class CCharacter;

//==============================================================
// クラス
//==============================================================
class CItem : public CTask
{
public:
	using ITEM_FUNC = std::function<void(CCharacter*, int)>;
	using ITEM_ACTION_FUNC = std::function<void(CCharacter*, int, CCharacter*)>;

public:
	CItem(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItem();

	HRESULT Init() override;
	void Uninit() override;
	void Draw() override {}

	static CItem* Create(CItemDataBase::EItemType inId);

	void SetWhenPickFunc(ITEM_FUNC inFunc) { m_getFunc = inFunc; }					// 入手したときの処理
	void SetWhenLostFunc(ITEM_FUNC inFunc) { m_lostFunc = inFunc; }					// 失ったときの処理
	void SetWhenAlwaysFunc(ITEM_FUNC inFunc) { m_allwayFunc = inFunc; }				// 常時発動している処理
	void SetWhenUseSkill(ITEM_ACTION_FUNC inFunc) { m_useSkillFunc = inFunc; }		// スキルを使った時
	void SetWhenDeathFunc(ITEM_ACTION_FUNC inFunc) { m_deathFunc = inFunc; }		// 死亡させたときの処理
	void SetWhenReceiveFunc(ITEM_ACTION_FUNC inFunc) { m_receiveFunc = inFunc; }	// ダメージを受ける時の処理
	void SetWhenInflictFunc(ITEM_ACTION_FUNC inFunc) { m_inflictFunc = inFunc; }	// ダメージを与えた時の処理
	void SetModel(std::string str) { m_itemModelData = str; }

	ITEM_FUNC GetWhenPickFunc() { return m_getFunc; }								// 入手したときの処理
	ITEM_FUNC GetWhenLostFunc() { return m_lostFunc; }								// 失ったときの処理
	ITEM_FUNC GetWhenAllwaysFunc() { return m_allwayFunc; }							// 常時発動している処理
	ITEM_ACTION_FUNC GetWhenUseSkillFunc() { return m_useSkillFunc; }				// スキルを使った時
	ITEM_ACTION_FUNC GetWhenDeathFunc() { return m_deathFunc; }						// 死亡させたときの処理
	ITEM_ACTION_FUNC GetWhenReceiveFunc() { return m_receiveFunc; }					// ダメージを受ける時の処理
	ITEM_ACTION_FUNC GetWhenInflictFunc() { return m_inflictFunc; }					// ダメージを与えた時の処理
	std::string GetModel() { return m_itemModelData; }

	// レアリティ
	void SetRerity(CItemDataBase::ERarity inRarity) { m_rarity = inRarity; }
	CItemDataBase::ERarity GetRerity() { return m_rarity; }

private:
	ITEM_FUNC m_getFunc;
	ITEM_FUNC m_lostFunc;
	ITEM_FUNC m_allwayFunc;

	ITEM_ACTION_FUNC m_useSkillFunc;
	ITEM_ACTION_FUNC m_deathFunc;
	ITEM_ACTION_FUNC m_receiveFunc;
	ITEM_ACTION_FUNC m_inflictFunc;

	std::string m_itemModelData;

	CItemDataBase::ERarity m_rarity;
};
#endif	// _ITEM_DATA_H_