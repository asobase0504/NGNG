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
	using ITEM_FUNC = void(*)(CCharacter*, int);
public:
	CItem(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItem();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	static CItem* Create(CItemDataBase::EItemType inId);

	void SetWhenPickFunc(ITEM_FUNC inFunc) { m_getFunc = inFunc; }
	void SetWhenLostFunc(ITEM_FUNC inFunc) { m_lostFunc = inFunc; }
	void SetWhenAllWayFunc(ITEM_FUNC inFunc) { m_allwayFunc = inFunc; }
	void SetWhenDamageFunc(ITEM_FUNC inFunc) { m_hitFunc = inFunc; }
	void SetWhenHitFunc(ITEM_FUNC inFunc) { m_hitFunc = inFunc; }

	ITEM_FUNC GetWhenPickFunc() { return m_getFunc; }
	ITEM_FUNC GetWhenLostFunc() { return m_lostFunc; }
	ITEM_FUNC GetWhenAllWayFunc() { return m_allwayFunc; }
	ITEM_FUNC GetWhenDamageFunc() { return m_hitFunc; }
	ITEM_FUNC GetWhenHitFunc() { return m_hitFunc; }

private:
	ITEM_FUNC m_getFunc;
	ITEM_FUNC m_lostFunc;
	ITEM_FUNC m_allwayFunc;
	ITEM_FUNC m_damageFunc;
	ITEM_FUNC m_hitFunc;
};
#endif	// _ITEM_DATA_H_