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
		ABNORMAL_MAX
	};

	struct SAbnormalStatus
	{
		int s_stack;
		int s_effectTime;
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
#endif	// _ITEM_DATA_
