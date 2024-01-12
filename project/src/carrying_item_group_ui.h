//==================================================
//
// �������Ă���A�C�e��UI�Q
// Author: YudaKaito
//
//==================================================
#ifndef _CARRYING_ITEM_GROUP_UI_H_
#define _CARRYING_ITEM_GROUP_UI_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "object.h"
#include "item_data_base.h"
#include "carrying_item_ui.h"

//**************************************************
// �O���O���@���Ԃ�NG�@�|�C���^�����Ȃ�OK
//**************************************************
class CObject2d;
class CProcedure;
class CCarryingItemUI;

//**************************************************
// �N���X
//**************************************************
class CCarryingItemGroupUI : public CObject
{
public:
	CCarryingItemGroupUI();
	~CCarryingItemGroupUI();

	HRESULT Init() override;
	void Update() override;

	CCarryingItemUI* CreateCarryingItemUI(CItemDataBase::EItemType, const unsigned int* = nullptr);

private:
	void Alignment();	// ����

private:
	// �`�敨
	std::list<CCarryingItemUI*> m_uiList;
	CObject2d* m_bg;
};

#endif // _TIMER_H_