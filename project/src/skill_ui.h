//==================================================
// skillUI.h
// Author: ���c�喲
//==================================================
#ifndef _SUKILLUI_H_
#define _SUKILLUI_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"
#include "status.h"
#include "skill.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CProcedure;
class CObject2d;

//**************************************************
// �N���X
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
