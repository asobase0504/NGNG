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
#include "item_data_base.h"

//==============================================================
// 前方宣言
//==============================================================
class CItemModel;
class CCharacter;
class CItem;

//==============================================================
// クラス
//==============================================================
class CItemManager : public CTask
{
public:	// シングルトン用のインスタンス
	static CItemManager* GetInstance();
private:
	CItemManager(CTaskGroup::EPriority list = CTaskGroup::LEVEL_SYSTEM);
	static CItemManager* m_itemManager;
public:
	~CItemManager();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// ItemModelの生成
	void CreateItem(const D3DXVECTOR3& inPos, const D3DXMATRIX& boxmtx, CItemDataBase::EItemType inId);
	void CreateRandomItemRarity(const D3DXVECTOR3& inPos, const D3DXMATRIX& boxmtx, CItemDataBase::ERarity);
	CItemDataBase::ERarity CreateRandomItemRarityRate(const D3DXVECTOR3& inPos, const D3DXMATRIX& boxmtx, std::array<float, CItemDataBase::RARITY_MAX> rarityRate);

	std::list<CItemModel*>& GetPopItemModel() { return m_itemModel; }

	void AllWhenPick(CCharacter*,item_count);
	void AllWhenLost(CCharacter*, item_count);
	void AllWhenAllWay(CCharacter*, item_count);
	void AllWhenDamage(CCharacter*, item_count, CCharacter*);
	void AllWhenHit(CCharacter*, item_count, CCharacter*);

private:
	// アイテムのタイプ
	CItemDataBase::EItemType m_itemType;

	// アイテムのデータ(ステータスアップするよ～とか)
	CItem* m_itemData;

	// 出現しているアイテムのモデルデータ
	std::list<CItemModel*> m_itemModel;
};
#endif	// _ITEM_MANAGER_H_

