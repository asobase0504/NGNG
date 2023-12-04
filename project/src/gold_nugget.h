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
// ëOï˚êÈåæ
//==============================================================
class CCollisionBox;

//==============================================================
// ÉNÉâÉX
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
	void Hit_();

private:
	CCollisionBox* m_collision;
};
#endif	// _GOLD_NUGGET_H_