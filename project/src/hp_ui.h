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
// ëOï˚êÈåæ
//==============================================================
class CObject2d;
class CProcedure;

//==============================================================
// ÉNÉâÉX
//==============================================================
class CHPUI : public CObject
{
public:
	CHPUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CHPUI();

	HRESULT Init() override;
	void Update() override;

	static CHPUI* Create(CStatus<int>* inHp);

private:
	CStatus<int>* m_hp;
	CProcedure* m_current;
	CProcedure* m_max;
	CObject2d* m_ground;
	CObject2d* m_bar;
};
#endif	// _ITEM_DATA_H_