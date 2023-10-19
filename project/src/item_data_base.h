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

	void AllDamage();
public:
	CItem* GetActivityFunc(EItemType inState) { return m_activityFunc[inState]; }
private:

private:	// ÉÅÉìÉoïœêî
	std::array<CItem*, ITEM_MAX> m_activityFunc;
};
#endif	// _ITEM_DATA_
