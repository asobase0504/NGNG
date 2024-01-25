//==================================================
// moneyUI.h
// Author: ���c�喲
//==================================================
#ifndef _UI_BG_H_
#define _UI_BG_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object2d.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2d;
class CProcedure;

//**************************************************
// �N���X
//**************************************************
class CUIBackGround : public CObject
{
public:
	CUIBackGround();
	~CUIBackGround();

	static CUIBackGround* Create(D3DXVECTOR2, D3DXVECTOR2,float);

	void SetPouseUpdate(bool isUpdate) override;
private:
	// �`�敨
	CObject2d* m_bg;		// �w�i
	CObject2d* m_outLine;	// outline
	CObject2d* m_corner[8];	// �p
};

#endif // _TIMER_H_