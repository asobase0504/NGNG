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
class CPlayerAbnormalUI : public CObject
{
public:
	CPlayerAbnormalUI();
	~CPlayerAbnormalUI();

	HRESULT Init() override;
	void Update() override;

	static CPlayerAbnormalUI* Create(const int* inStock,CAbnormalDataBase::EAbnormalType inType);

	CAbnormalDataBase::EAbnormalType GetType() { return m_inType; }

	void SetPos(const D3DXVECTOR3&) override;

private:
	CAbnormalDataBase::EAbnormalType m_inType;
	bool m_isDisplayStack;
	const int* m_stackCnt;		// stack���̃��S
	CObject2d* m_abnormalLogo;
	CProcedure* m_stack;
};

#endif // _TIMER_H_