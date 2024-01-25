//==================================================
// moneyUI.h
// Author: 梶田大夢
//==================================================
#ifndef _UI_BG_H_
#define _UI_BG_H_

//**************************************************
// インクルード
//**************************************************
#include "object2d.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CObject2d;
class CProcedure;

//**************************************************
// クラス
//**************************************************
class CUIBackGround : public CObject
{
public:
	CUIBackGround();
	~CUIBackGround();

	static CUIBackGround* Create(D3DXVECTOR2, D3DXVECTOR2,float);

	void SetPouseUpdate(bool isUpdate) override;
private:
	// 描画物
	CObject2d* m_bg;		// 背景
	CObject2d* m_outLine;	// outline
	CObject2d* m_corner[8];	// 角
};

#endif // _TIMER_H_