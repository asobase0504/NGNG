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
class CCharacter;
class CObject2d;

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

private:
	CStatus<int>* m_hp;
	CObject2d* m_ground;
	CObject2d* m_bar;
};
#endif	// _ITEM_DATA_H_