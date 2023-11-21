//**************************************************************
//
// result
// Author: Buriya Kota
//
//**************************************************************
#ifndef _RESULT_H_
#define _RESULT_H_

//==============================================================
// include
//==============================================================
#include "task.h"

//==============================================================
// ëOï˚êÈåæ
//==============================================================
class CObject2d;

//==============================================================
// ÉNÉâÉX
//==============================================================
class CResult : public CTask
{
private:

public:
	CResult(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);
	~CResult();

	HRESULT Init() override;
	void Update() override;

	static CResult* Create();

private:
	CObject2d* m_title;
};
#endif	// _GOLD_NUGGET_H_