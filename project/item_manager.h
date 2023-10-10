//**************************************************************
//
// item_manager
// Author: Buriya Kota
//
//**************************************************************
#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_

//==============================================================
// include
//==============================================================
#include "object2d.h"

//==============================================================
// �O���錾
//==============================================================
class CItemModel;

//==============================================================
// �N���X
//==============================================================
class CItemManager : public CTask
{
public:
	CItemManager(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CItemManager();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// �A�C�e���̐����v���Z�X
	static CItemManager* Create();

private:
	// �A�C�e���̃f�[�^�ƃ��f���f�[�^��ID
	int m_itemId;
	// �A�C�e���̃f�[�^(�X�e�[�^�X�A�b�v�����`�Ƃ�)

	// �A�C�e���̃��f���f�[�^
	CItemModel* m_itemModel;
};
#endif	// _ITEM_MANAGER_H_

//�A�C�e���}�l�[�W���[�� �K�v���Ǝv�����́B
//- �o�����Ă���A�C�e�����f��
