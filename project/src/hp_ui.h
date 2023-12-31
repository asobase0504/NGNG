//**************************************************************
//
// HP_BAR
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _HP_UI_H_
#define _HP_UI_H_

//==============================================================
// include
//==============================================================
#include "object.h"
#include "status.h"

//==============================================================
// 前方宣言
//==============================================================
class CObject2d;
class CProcedure;

//==============================================================
// クラス
//==============================================================
class CHPUI : public CObject
{
public:
	CHPUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CHPUI();

	HRESULT Init() override;
	void Update() override;

	static CHPUI* Create(CStatus<int>* inHp);

	void SetHP(CStatus<int>* inHp) { m_hp = inHp; }

protected:
	// 描画物
	CProcedure* m_current;
	CProcedure* m_max;
	CObject2d* m_ground;
	CObject2d* m_bar;

	CStatus<int>* m_hp;
};

class CBossHPUI : public CHPUI
{
public:
	CBossHPUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI) {}
	~CBossHPUI() {}

	HRESULT Init() override;

};
#endif	// _ITEM_DATA_H_