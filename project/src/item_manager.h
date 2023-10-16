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
#include "item_data.h"

//==============================================================
// �O���錾
//==============================================================
class CItemModel;
class CItem;

//==============================================================
// �N���X
//==============================================================
class CItemManager : public CTask
{
public:	// �V���O���g���p�̃C���X�^���X
	static CItemManager* GetInstance();
private:
	CItemManager(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	static CItemManager* m_itemManager;
public:
	~CItemManager();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void CreateItem(const D3DXVECTOR3& inPos, ITEM_TYPE inId);

	std::list<CItemModel*>& GetPopItemModel() { return m_itemModel; }
private:
	// �A�C�e���̃^�C�v
	ITEM_TYPE m_itemType;

	// �A�C�e���̃f�[�^(�X�e�[�^�X�A�b�v�����`�Ƃ�)
	CItem* m_itemData;

	// �o�����Ă���A�C�e���̃��f���f�[�^
	std::list<CItemModel*> m_itemModel;
};
#endif	// _ITEM_MANAGER_H_

