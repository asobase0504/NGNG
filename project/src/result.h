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
// 前方宣言
//==============================================================
class CObject2d;

//==============================================================
// クラス
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