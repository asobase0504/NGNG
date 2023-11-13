//**************************************************************
//
// item
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ABNORMAL_H_
#define _ABNORMAL_H_

//==============================================================
// include
//==============================================================
#include "task.h"
#include "character.h"
#include "item_data_base.h"

//==============================================================
// �O���錾
//==============================================================
class CCharacter;

//==============================================================
// �N���X
//==============================================================
class CAbnormal : public CTask
{
public:
	using ABNORMAL_FUNC = void(*)(CCharacter*, int);
	using ABNORMAL_ACTION_FUNC = void(*)(CCharacter*, int, CCharacter*);
public:
	CAbnormal(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CAbnormal();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override {}

	static CAbnormal* Create(CAbnormalDataBase::EAbnormalType inId);

	void SetWhenAddFunc(ABNORMAL_FUNC inFunc) { m_getFunc = inFunc; }				// ��Ԉُ���󂯂��Ƃ��̏���
	void SetWhenClearFunc(ABNORMAL_FUNC inFunc) { m_lostFunc = inFunc; }			// �񕜂������̏���
	void SetWhenAllWayFunc(ABNORMAL_FUNC inFunc) { m_allwayFunc = inFunc; }			// �펞�������Ă��鏈��
	void SetWhenAttackFunc(ABNORMAL_ACTION_FUNC inFunc) { m_attackFunc = inFunc; }	// �U�����̏���

	void SetEffectTime(int eTime) { m_effectTime = eTime; }

	ABNORMAL_FUNC GetWhenAddFunc() { return m_getFunc; }
	ABNORMAL_FUNC GetWhenClearFunc() { return m_lostFunc; }
	ABNORMAL_FUNC GetWhenAllWayFunc() { return m_allwayFunc; }
	ABNORMAL_ACTION_FUNC GetWhenAttackFunc() { return m_attackFunc; }

private:
	ABNORMAL_FUNC m_getFunc;
	ABNORMAL_FUNC m_lostFunc;
	ABNORMAL_FUNC m_allwayFunc;
	ABNORMAL_ACTION_FUNC m_attackFunc;

	int m_effectTime;

};
#endif	// _ITEM_DATA_H_