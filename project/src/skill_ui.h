//==================================================
// skillUI.h
// Author: 梶田大夢
//==================================================
#ifndef _SUKILLUI_H_
#define _SUKILLUI_H_

//**************************************************
// インクルード
//**************************************************
#include "object.h"
#include "status.h"
#include "skill.h"

//**************************************************
// 前方前言　実態はNG　ポインタだけならOK
//**************************************************
class CProcedure;
class CObject2d;

//**************************************************
// クラス
//**************************************************
class CSKILLUI : public CObject
{
public:
	CSKILLUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CSKILLUI();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	static CSKILLUI* Create(CSkill* inSkill);

private:
	CSkill* m_skill;
	CProcedure* m_procedure;
	CObject2d* m_ground;
	CObject2d* m_display;
	int m_ct;
};

#endif // _TIMER_H_
