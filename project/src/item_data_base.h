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
		ITEM_DANGO,
		ITEM_SHURIKEN,
		ITEM_GETA,
		ITEM_UMBRELLA,
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

private:	// ÉÅÉìÉoïœêî
	std::array<CItem*, ITEM_MAX> m_item;
};

using item_count = std::array<unsigned int, CItemDataBase::ITEM_MAX>;
#endif	// _ITEM_DATA_
