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

	enum EItemType
	{
		ITEM_NONE = -1,
		ITEM_POWER_UP,
		ITEM_POWER_ON,
		ITEM_POWER_TO,
		ITEM_DANGO,				// ‚¾‚ñ‚²
		ITEM_SHURIKEN,			// è— Œ•
		ITEM_GETA,				// ‰º‘Ê
		ITEM_UMBRELLA,			// P
		ITEM_HYOUTAN,			// ‚Ğ‚å‚¤‚½‚ñ
		ITEM_BANBOO_WATERBOX,	// ’|‚Ì…“›
		ITEM_OMAMORI,			// ‚¨ç‚è
		ITEM_KIBORI,			// ŒF‚Ì–Ø’¤‚è
		ITEM_BAKUTIKU,			// ”š’|
		ITEM_MAKIBISI,			// ‚Ü‚«‚Ñ‚µ
		ITEM_HEAD,				// ñ‹‰
		ITEM_KUNAI,				// ‚­‚È‚¢
		ITEM_FUR,				// –Ñ”ç
		ITEM_KITUNEMEN,			// ŒÏ–Ê
		ITEM_KAZAGURUMA,		// •—Ô
		ITEM_KOBAN,				// ¬”»
		ITEM_ONIMEN,			// ‹S–Ê
		ITEM_BROKEN_KABUTO,		// ‰ó‚ê‚½Š•
		ITEM_CROW_FEATHER,		// ƒJƒ‰ƒX‚Ì‰H
		ITEM_TOISI,				// “uÎ
		ITEM_DRIP_BAG,			// “_“H‘Ü
		ITEM_CHICK,				// ‚Ğ‚æ‚±
		ITEM_ZOURI,				// ‘—š
		ITEM_ARROW,				// –î
		ITEM_SEED,				// íq
		ITEM_FETTERS,			// ‘«g
		ITEM_SHIELD,			// ‚
		ITEM_TABI,				// ‚½‚Ñ
		ITEM_FLINT,				// ‰Î‘ÅÎ
		ITEM_FLOWER,			// ‰Ô
		ITEM_IRON_WIRE,			// “Sü
		ITEM_HANNYA,			// ‚Í‚ñ‚É‚á‚Ì‚ß‚ñ
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

private:	// ƒƒ“ƒo•Ï”
	std::array<CItem*, ITEM_MAX> m_item;
};

using item_count = std::array<unsigned int, CItemDataBase::ITEM_MAX>;
#endif	// _ITEM_DATA_
