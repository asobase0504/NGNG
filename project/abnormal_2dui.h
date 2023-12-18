//==================================================
// moneyUI.h
// Author: ���c�喲
//==================================================
#ifndef _PLAYER_ABNORMAL_UI_H_
#define _PLAYER_ABNORMAL_UI_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"
#include "abnormal_data_base.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2d;
class CProcedure;

//**************************************************
// �N���X
//**************************************************
class CAbnormal2DUI : public CObject
{
public:
	CAbnormal2DUI();
	~CAbnormal2DUI();

	HRESULT Init() override;
	void Update() override;

	static CAbnormal2DUI* Create(const int* inStock,CAbnormalDataBase::EAbnormalType inType);

	CAbnormalDataBase::EAbnormalType GetType() { return m_inType; }

	void SetPos(const D3DXVECTOR3&) override;

private:
	// �`�敨
	CObject2d* m_abnormalLogo;	// ��Ԉُ탍�S
	CProcedure* m_stack;		// ����

	CAbnormalDataBase::EAbnormalType m_inType;
	bool m_isDisplayStack;
	const int* m_stackCnt;		// stack��
};

#endif // _TIMER_H_