//**************************************************************
//
// abnormal_data_base.h
// Author : Tomidokoro HIROHITO
// 
//**************************************************************
#ifndef _ABNORMAL_DATA_
#define _ABNORMAL_DATA_

class CAbnormal;

class CAbnormalDataBase
{
public:

	enum EAbnormalType
	{
		ABNORMAL_NONE = -1,
		ABNORMAL_FIRE,
		ABNORMAL_STUN,
		ABNORMAL_POISON,
		ABNORMAL_SLOW,
		ABNORMAL_BLEED,
		ABNORMAL_FROZEN,
		ABNORMAL_OIL,
		ABNORMAL_HOOK,
		ABNORMAL_VOID,
		ABNORMAL_SPEED_UP,
		ABNORMAL_ATK_SPD_UP,
		ABNORMAL_MAX
	};

	struct SAbnormalStatus
	{
		int s_effectTime;
		int s_target_interval;
		int s_stack;
		int s_interval;
		std::list<int> s_Time;
	};

private:
	explicit CAbnormalDataBase();
	static CAbnormalDataBase* m_instance;
	void Init();
public:
	static CAbnormalDataBase* GetInstance();
	~CAbnormalDataBase();

	static void Uninit();

public:
	CAbnormal* GetItemData(EAbnormalType inState) { return m_abnormal[inState]; }

private:	// ÉÅÉìÉoïœêî
	std::array<CAbnormal*, ABNORMAL_MAX> m_abnormal;
};

using abnormal_count = std::array<CAbnormalDataBase::SAbnormalStatus, CAbnormalDataBase::ABNORMAL_MAX>;
using abnormal_attack = std::array<bool, CAbnormalDataBase::ABNORMAL_MAX>;
#endif	// _ITEM_DATA_
