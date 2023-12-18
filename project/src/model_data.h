//============================
//
// 座標があるモデル
// Author:hamada ryuuga
//
//============================

<<<<<<< Updated upstream
#ifndef _MODEL_DATE_H_
#define _MODEL_DATE_H_


static const int Max = 1024;
static const int MaxModel = 15;
static const int MaxPlayer = 4;


struct item_data
{
	int itemData[5];
};

struct abnormal_data
{
	int abnormalData[5];
};
=======
#ifndef _MODEL_DATA_H_
#define _MODEL_DATA_H_


static const int Max = 1024;
static const int MaxModel = 20;

static const int P1 = 1345;
static const int P2 = 2333;
static const int P3 = 3204;
static const int P4 = 4650;

>>>>>>> Stashed changes

class CModelData
{

public:
<<<<<<< Updated upstream
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
		item_data m_haveItem;
		abnormal_data m_haveAbnormal;
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
	void SetCommu(SPlayerDate Set) { m_CommuData = Set; };
	bool IsUse;
	SPlayerDate m_CommuData;
};

class CDataPack
{

public:
=======

	//にんずう
	static const int MAX_P = 2;

	//ーーーーーーー
	//プレイヤー
	//ーーーーーーー
	struct SPlayerList
	{
		D3DXVECTOR3 m_pos;
		D3DXVECTOR3 m_rot;
		int m_motion;
		int m_haveItemRightId;
		int m_haveItemLeftId;
		bool m_pushBomComands;
	};

	//ーーーーーーー
	//エネミー
	//ーーーーーーー
>>>>>>> Stashed changes
	struct SEnemyData
	{
		bool isUse;
		bool isDiscovery;
<<<<<<< Updated upstream
		D3DXVECTOR3 Pos;

	};
	struct SPlayerData
	{
		bool isUse;
		bool isDiscovery;
		D3DXVECTOR3 m_rot;
		D3DXVECTOR3 m_pos;
		item_data m_haveItem;
		abnormal_data m_haveAbnormal;

	};
	
=======
		bool isMap;
		D3DXVECTOR3 Pos;
	};

	//ーーーーーーー
	//ギミック
	//ーーーーーーー
	struct SGimmickData
	{
		bool isUse;
		bool isMap;
	};
>>>>>>> Stashed changes
	struct SSendData
	{
		enum EDATA
		{
			ESENDDATA_ENEMY,
		};


		SSendData(int id) :mId(id) {}
		int mId;
	};
<<<<<<< Updated upstream
	
	
	struct SSendPack : public SSendData
	{
	public:
		SSendPack();
		~SSendPack();
		SPlayerData Player[MaxPlayer];

		void SetPlayer(SSendPack data)
		{
			for (int i = 0; i < MaxPlayer; i++)
			{
				Player[i] = data.Player[i];
			}
			
		}


	};



};

=======
	struct SSendPack : public SSendData
	{
	public:
		SPlayerList m_PlayData;
		int m_popEnemy;
		int m_popGimmick;
		SEnemyData m_isPopEnemy[MaxModel];
		SGimmickData m_isPopGimmick[MaxModel];
		int m_addscore;
		int m_score;
		bool m_IsGame;
		int m_MyId;
		int m_log;
		SSendPack() : SSendData(ESENDDATA_ENEMY)
		{
			for (int i = 0; i < MaxModel; i++)
			{
				m_isPopEnemy[i].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_isPopEnemy[i].isDiscovery = false;
				m_isPopEnemy[i].isUse = false;
				m_isPopGimmick[i].isMap = false;
				m_isPopGimmick[i].isUse = false;
			}


		}
		void SetList(std::string modelList)
		{

			if (modelList.size() != Max)
			{
				return;
			}
			m_PlayData.m_pos = D3DXVECTOR3(modelList[0], modelList[1], modelList[2]);
			m_PlayData.m_rot = D3DXVECTOR3(modelList[3], modelList[4], modelList[5]);
			m_PlayData.m_motion = modelList[6];
		}

	};
	struct SPlayerData
	{
		SSendPack Player;
		void SetPlayerClear();
		void SetPlayer(SSendPack data)
		{
			Player = data;
		}
		void SetPlayerCast(const char* data)
		{
			Player = *((SSendPack*)data);
		}
	};
public:

	CModelData();
	~CModelData();

	SPlayerData* GetCommu() { return &m_CommuData; };
	void SetCommu(SPlayerData Set) { m_CommuData = Set; };
	bool* GetUse() { return &IsUse; };
	void SetUse(bool Set) { IsUse = Set; };
	bool IsUse;
	SPlayerData m_CommuData;
};

struct SSendMap
{
	int sendMap;
	bool isMap;
};

//ーーーーーーー
//送り返すデータ
//ーーーーーーー
class CReceiveData
{
public:
	struct SReceiveList
	{
		CModelData::SPlayerList m_PlayrData[CModelData::MAX_P];
		CModelData::SEnemyData m_isPopEnemy[MaxModel];
		CModelData::SGimmickData m_isPopGimmick[MaxModel];
		int m_score;
		int m_log;
		bool m_IsGame;
		void Init();
		void SetListPlayr(CModelData::SPlayerList player, int playerId);
		void SetListEnemy(CModelData::SEnemyData* Enemy);
		void SetListGimmick(CModelData::SGimmickData* Gimmick);
	};

};
>>>>>>> Stashed changes
#endif