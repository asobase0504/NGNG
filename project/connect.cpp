//============================
//
// メイン設定
// Author:hamada ryuuga
//
//============================
#include "client.h"
#include "connect.h"
#include "player_manager.h"
#include "player.h"
#include "tcp_client.h"
#include "udp_client.h"

#include <thread>

//--------------------------
//コンスト
//--------------------------
ConnectManager::ConnectManager()
{

}
//--------------------------
//デストラクト
//--------------------------
ConnectManager::~ConnectManager()
{
}

//--------------------------
//初期化
//--------------------------
bool ConnectManager::Init(const char*plPAddress, int nPortNum)
{
	WSADATA wasData;

	int nErr = WSAStartup(WINSOCK_VERSION, &wasData);

	if (nErr != 0)
	{
		printf("was　error");
	}
	m_client = new CClient;

	if (!m_client->Init(plPAddress, nPortNum))
	{
		printf("error");
	}
	else
	{

	}


	std::thread ConnectOn([&] {m_myConnect= ConnectTh(m_client);});

	// スレッドをきりはなす
	ConnectOn.detach();

	std::thread ConnectManagerRecv(RecvPlayerData,this);
	// スレッドをきりはなす
	ConnectManagerRecv.detach();
	return true;
}

//--------------------------
//破棄
//--------------------------
void ConnectManager::Uninit(void)
{
	


	
	WSACleanup();
}


//=============================================================================
// 通信接続スレッド
//=============================================================================
ConnectManager::SConnectCheck ConnectManager::ConnectTh(CClient * Client)
{
	SConnectCheck ConnectManager;
	ConnectManager.myConnect = false;
	ConnectManager.enemyConnect = false;
	char aRecvData[1024];	// 受信データ
	int Timer = 0;
	bool myIs = false;
	int ok = 4;
	// つながるまでループ
	while (!myIs)
	{

		myIs = Client->GetTcp()->Connect();
		Client->GetUdp()->Connect();
		if (myIs)
		{
			Client->Send((const char*)&ok, 4, CClient::TYPE_TUP);
		}
	
	}
	// 敵がつながるまでループ
	while (!ConnectManager.enemyConnect)
	{
		int isRecv = Client->Recv(&aRecvData[0], sizeof(bool), CClient::TYPE_TUP);
		if (isRecv == sizeof(SConnectCheck))
		{
			memcpy(&ConnectManager, &aRecvData[0], sizeof(SConnectCheck));
		}
		
	}
	return ConnectManager;
}

//=============================================================================
// レシーブスレッド
//=============================================================================
void ConnectManager::RecvPlayerData(ConnectManager *list)
{
	// 繋がっている間はループ
	while (1)
	{
	
		char aRecv[2048];	// 受信データ

		// 受信
		int nRecvSize = list->GetClient()->Recv(&aRecv[0], sizeof(CReceiveData::SReceiveList), CClient::TYPE_UDP);


		// 受信データが無かったら
		if (nRecvSize < 0)
		{
			return;
		}
		CReceiveData::SReceiveList List;
		memcpy(&list->m_player, &aRecv[0], (int)sizeof(CReceiveData::SReceiveList));
		
	}
}

//=============================================================================
// Send スレット
//=============================================================================
void  ConnectManager::SendPlayerData(CModelData::SSendPack data)
{
	CModelData::SSendPack sendData = data;

	m_client->Send((const char*)&sendData, sizeof(CModelData::SSendPack), CClient::TYPE_UDP);
}

//=============================================================================
// Send スレット
//=============================================================================
void  ConnectManager::Send(const char*send,int Size, CClient::CONNECT_TYPE Tipe)
{
	//CModelData::SSendPack sendData = data;

	m_client->Send(send, Size, Tipe);
}

//=============================================================================
// Recv スレット
//=============================================================================
int ConnectManager::Recv(char*Recv, int Size, CClient::CONNECT_TYPE Tipe)
{
	//CModelData::SSendPack sendData = data;

	int RecvSize = m_client->Recv(Recv, Size, Tipe);
	return RecvSize;
}