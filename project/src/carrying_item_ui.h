//==================================================
// moneyUI.h
// Author: ���c�喲
//==================================================
#ifndef _CARRYING_ITEM_UI_H_
#define _CARRYING_ITEM_UI_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"
#include "item_data_base.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2d;
class CProcedure;

//**************************************************
// �N���X
//**************************************************
class CCarryingItemUI : public CObject
{
public:
	CCarryingItemUI();
	~CCarryingItemUI();

	HRESULT Init() override;
	void Update() override;

	static CCarryingItemUI* Create(CItemDataBase::EItemType inType, const int*);

	CItemDataBase::EItemType GetType() { return m_type; }

	void SetPos(const D3DXVECTOR3&) override;

private:
	// �`�敨
	CObject2d* m_ItemLogo;	// ��Ԉُ탍�S
	CProcedure* m_stack;		// ����

	CItemDataBase::EItemType m_type;
	const unsigned int* m_stackCnt;		// stack��
};

#endif // _TIMER_H_