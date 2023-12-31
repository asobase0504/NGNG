//**************************************************************
//
// gold_nugget
// Author: Buriya Kota
//
//**************************************************************
#ifndef _GOLD_NUGGET_H_
#define _GOLD_NUGGET_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionBox;

//==============================================================
// クラス
//==============================================================
class CGoldNugget : public CObjectX
{
private:

public:
	CGoldNugget(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);
	~CGoldNugget();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	static CGoldNugget* Create();

private:
	void Get_();

private:
	CCollisionBox* m_collision;
};
#endif	// _GOLD_NUGGET_H_