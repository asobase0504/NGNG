//**************************************************************
//
// 難易度システム
// Author: Tomidokoro Tomoki
//
//**************************************************************
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "task.h"

class CObject2d;
class CUIBackGround;
class CText;

class CPause : public CTask
{
public:
	CPause();
	~CPause();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
	CObject2d* m_BG;
	CText* m_backText;
	CUIBackGround* m_backBG;
	CText* m_retryText;
	CUIBackGround* m_retryBG;
	CText* m_endText;
	CUIBackGround* m_endBG;

	bool m_lag;
};
#endif
