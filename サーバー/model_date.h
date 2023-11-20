//============================
//
// ç¿ïWÇ™Ç†ÇÈÉÇÉfÉã
// Author:hamada ryuuga
//
//============================

#ifndef _MODEL_DATE_H_
#define _MODEL_DATE_H_


static const int Max = 1024;
static const int MaxModel = 15;
static const int MaxPlayer = 4;
class CModelData
{
	
public:
	struct SEnemyData
	{
		bool isUse;
		bool isDiscovery;
		D3DXVECTOR3 Pos;

	};
	struct SSendData
	{
		enum EDATA
		{
			ESENDDATA_ENEMY,
		};


		SSendData(int id) :mId(id) {}
		int mId;
	};
	struct SSendEnemy : public SSendData
	{
	public:
		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_rot;
		int m_motion;
		int m_log;
		int m_haveItemRightId;
		int m_haveItemLeftId;
		int m_popEnemy;
		int m_popGimmick;
		bool m_pushBomComands;
		SEnemyData m_isPopEnemy[MaxModel];
		bool m_isPopGimmick[MaxModel];

		SSendEnemy() : SSendData(ESENDDATA_ENEMY)
		{ 
			for (int i = 0; i < MaxModel; i++)
			{
				m_isPopEnemy[i].isDiscovery = false;
				m_isPopEnemy[i].isUse = false;
				m_isPopGimmick[i] = false;
			}
			

		}
		void SetList(std::string modelList)
		{
			
			if (modelList.size() != Max)
			{
				return;
			}
			m_pos = D3DXVECTOR3(modelList[0], modelList[1], modelList[2]);
			m_rot = D3DXVECTOR3(modelList[3], modelList[4], modelList[5]);
			m_motion = modelList[6];
		}
	
	};
	struct SPlayerDate
	{
		SSendEnemy Player;
		
		void SetPlayer(SSendEnemy data)
		{
			Player = data;
		}
		void SetPlayerCast(const char* data)
		{
			Player = *((SSendEnemy*)data);
		}
	};
public:

	CModelData();
	~CModelData();

	SPlayerDate* GetCommu() { return &m_CommuData; };
	void SetCommu(SPlayerDate Set) {  m_CommuData = Set; };
	bool IsUse;
	SPlayerDate m_CommuData;
};

class CDataPack
{

public:
	struct SEnemyData
	{
		bool isUse;
		bool isDiscovery;
		D3DXVECTOR3 Pos;

	};
	struct SPlayerData
	{
		bool isUse;
		bool isDiscovery;
		D3DXVECTOR3 m_rot;
		D3DXVECTOR3 m_pos;

	};
	struct SSendData
	{
		enum EDATA
		{
			ESENDDATA_ENEMY,
		};


		SSendData(int id) :mId(id) {}
		int mId;
	};
	struct SSendPack : public SSendData
	{
	public:
		SSendPack();
		~SSendPack();
		SPlayerData Player[MaxPlayer];
		SEnemyData m_isPopEnemy[MaxModel];

	};
		


};

#endif