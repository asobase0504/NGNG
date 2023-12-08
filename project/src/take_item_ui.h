//**************************************************************
//
// �擾�����A�C�e���̏��
// Author: Yuda Kaito
//
//**************************************************************
#ifndef _TAKE_ITEM_UI_H_
#define _TAKE_ITEM_UI_H_

//==============================================================
// include
//==============================================================
#include "object.h"
#include "item_data_base.h"
#include <queue>

//==============================================================
// �O���錾
//==============================================================
class CObject2d;
class CText;

//==============================================================
// �N���X
//==============================================================
class CTakeItemUI : public CObject
{
private:
	static const D3DXVECTOR2 CENTER_POS;	// ���S���W
	static const D3DXVECTOR2 ICON_POS;	// �A�C�R���ʒu
	static const D3DXVECTOR2 NAME_POS;	// ���O�ʒu
	static const D3DXVECTOR2 TEXT_POS;	// �e�L�X�g�ʒu
	static const int DISPLAY_TIME;	// �\������
public:
	CTakeItemUI(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CTakeItemUI();

	HRESULT Init() override;
	void Update() override;

	void SetTakeItem(CItemDataBase::EItemType inType);

private:

private:
	CObject2d* m_ground;	// ���n

	int m_displayCnt;		// �\�����Ă���t���[����

	// �`�悷��A�C�e�����
	CObject2d* m_itemIcon;	// �A�C�R��
	CText* m_text;			// ���ʂ̐���
	CText* m_name;			// ���O
};
#endif	// _ITEM_DATA_H_