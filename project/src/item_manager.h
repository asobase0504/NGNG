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
// 前方宣言
//==============================================================
class CItemModel;
class CItem;

//==============================================================
// クラス
//==============================================================
class CItemManager : public CTask
{
public:	// シングルトン用のインスタンス
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

private:
	// アイテムのタイプ
	ITEM_TYPE m_itemType;
	// アイテムのデータ(ステータスアップするよ～とか)
	CItem* m_itemData;
	// アイテムのモデルデータ
	CItemModel* m_itemModel;
};
#endif	// _ITEM_MANAGER_H_

// アイテムマネージャーに 必要だと思うもの。
//- 出現しているアイテムモデル

