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
// �O���錾
//==============================================================
class CObject2d;
class CText;

//==============================================================
// �N���X
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
	CObject2d* m_bg;
	CText* m_text;
};
#endif	// _GOLD_NUGGET_H_