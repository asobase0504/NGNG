//**************************************************************
//
// arrow.h
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ARROW_H_
#define _ARROW_H_

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
class CArrow : public CObjectX
{
public:
	CArrow(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);
	~CArrow();

	HRESULT Init() override;
	void Update() override;

	static CArrow* Create();

	bool GetIsHit() { return m_isHit; }

private:
	void HitEnemy_();

private:
	CCollisionBox* m_collision;
	bool m_isHit;
};
#endif	// _GOLD_NUGGET_H_