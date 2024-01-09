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
class CSkillUI : public CObject
{
private:
	static const float UI_SIZE;

public:
	CSkillUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CSkillUI();

	HRESULT Init() override;
	void Update() override;

	static CSkillUI* Create(const D3DXVECTOR3& inPos, CSkill* inSkill);

private:
	CSkill* m_skill;
	CProcedure* m_procedure;
	CObject2d* m_bg;
	CObject2d* m_ground;
	CObject2d* m_display;
	int m_ct;
};

#endif // _TIMER_H_
