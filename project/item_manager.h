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
// 前方宣言
//==============================================================
class CItemModel;

//==============================================================
// クラス
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

	// アイテムの生成プロセス
	static CItemManager* Create();

private:
	// アイテムのデータとモデルデータのID
	int m_itemId;
	// アイテムのデータ(ステータスアップするよ～とか)

	// アイテムのモデルデータ
	CItemModel* m_itemModel;
};
#endif	// _ITEM_MANAGER_H_

//アイテムマネージャーに 必要だと思うもの。
//- 出現しているアイテムモデル
