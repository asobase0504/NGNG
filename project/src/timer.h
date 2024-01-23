//==================================================
// moneyUI.h
// Author: ���c�喲
//==================================================
#ifndef _TIMER_H_
#define _TIMER_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2d.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CText;
class CProcedure;

//**************************************************
// �N���X
//**************************************************
class CTimer : public CObject
{
public:
	CTimer();
	~CTimer();

	HRESULT Init() override;
	void Update() override;

	static CTimer* Create();

private:
	int m_time;

	CProcedure* m_second;	// �b
	CProcedure* m_minutes;	// ��
	CText* m_koron;			// �R����
};

#endif // _TIMER_H_