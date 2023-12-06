//============================
//
// client設定
// Author:hamada ryuuga
//
//============================

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "model_data.h"


//構造体

class CTcp_client;
class CDataPack;
class  CClient
{

	struct SConnectCheck
	{
		int myConnect;
		bool enemyConnect;
	};

public:
	const int MAX_PL = 4;
public:
	CClient();
	~CClient();
	bool Init(const char*plPAddress, int nPortNum);
	void Uninit(void);
	static SConnectCheck ConnectTh(CTcp_client * tcp);
	static void Recv(CClient*data);
	void SendPlayerData(CModelData::SSendEnemy Data);
	bool GetIsConnect() { return m_myConnect.enemyConnect; }
private:
	CTcp_client *m_tcpClient;
	SConnectCheck m_myConnect;		//自分に接続する
	CDataPack::SSendPack m_player;	//保存するプレイヤーデータの保存先

};

#endif