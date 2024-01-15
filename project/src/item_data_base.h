//**************************************************************
//
// item_data.h
// Author : Buriya HIROHITO
// 
//**************************************************************
#ifndef _ITEM_DATA_
#define _ITEM_DATA_

class CItem;

class CItemDataBase
{
public:
	enum ERarity
	{
		RARITY_NONE = -1,
		RARITY_COMMON = 0,
		RARITY_UNCOMMON,
		RARITY_RARE,
		RARITY_LOSE,	// はずれ(運の祭壇用)
		RARITY_MAX,
		RARITY_NOSELECT, // 選ばれることのないアイテム(エリート用とか)
	};

	enum EItemType
	{
		ITEM_NONE = -1,
		ITEM_DANGO,				// だんご
		ITEM_SHURIKEN,			// 手裏剣
		ITEM_GETA,				// 下駄
		ITEM_UMBRELLA,			// 傘
		ITEM_HYOUTAN,			// ひょうたん
		ITEM_BANBOO_WATERBOX,	// 竹の水筒
		ITEM_OMAMORI,			// お守り
		ITEM_KIBORI,			// 熊の木彫り
		ITEM_BAKUTIKU,			// 爆竹
		ITEM_MAKIBISI,			// まきびし
		ITEM_HEAD,				// 首級
		ITEM_KUNAI,				// くない
		ITEM_FUR,				// 毛皮
		ITEM_KITUNEMEN,			// 狐面
		ITEM_KAZAGURUMA,		// 風車
		ITEM_KOBAN,				// 小判
		ITEM_ONIMEN,			// 鬼面
		ITEM_BROKEN_KABUTO,		// 壊れた兜
		ITEM_CROW_FEATHER,		// カラスの羽
		ITEM_TOISI,				// 砥石
		ITEM_DRIP_BAG,			// 点滴袋
		ITEM_CHICK,				// ひよこ
		ITEM_ZOURI,				// 草履
		ITEM_ARROW,				// 矢
		ITEM_SEED,				// 種子
		ITEM_FETTERS,			// 足枷
		ITEM_SHIELD,			// 盾
		ITEM_TABI,				// たび
		ITEM_FLINT,				// 火打石
		ITEM_FLOWER,			// 花
		ITEM_IRON_WIRE,			// 鉄線
		ITEM_HANNYA,			// はんにゃのめん
		ITEM_ELITE,				// エリートかどうか
		ITEM_MAX
	};
private:
	explicit CItemDataBase();
	static CItemDataBase* m_instance;
	void Init();

public:
	static CItemDataBase* GetInstance();
	~CItemDataBase();

	static void Uninit();

public:
	CItem* GetItemData(EItemType inState) { return m_item[inState]; }
	std::string GetItemName(EItemType inState) { return m_itemInfo[inState][0]; }
	std::string GetItemMemo(EItemType inState) { return m_itemInfo[inState][1]; }
	std::string GetItemIconTextureKey(EItemType inState) { return m_itemInfo[inState][2]; }

private:	// メンバ変数
	std::array<CItem*, ITEM_MAX> m_item;
	std::array<std::string[3], ITEM_MAX> m_itemInfo;	// 情報体

	int m_countKill;	// 殺した数
	int m_maxAddLife;	// 増やせる最大値
	int m_frame;		// 効果時間
};

using item_count = std::array<unsigned int, CItemDataBase::ITEM_MAX>;
#endif	// _ITEM_DATA_
