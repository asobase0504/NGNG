//============================
//
// メイン設定
// Author:hamada ryuuga
//
//============================
#include "tcp_client.h"
#include "connect.h"
#include "player_manager.h"
#include "player.h"
#include <thread>

//--------------------------
//コンスト
//--------------------------
CClient::CClient()
{

}
//--------------------------
//デストラクト
//--------------------------
CClient::~CClient()
{
}

//--------------------------
//初期化
//--------------------------
bool CClient::Init(const char*plPAddress, int nPortNum)
{
	WSADATA wasData;

	int nErr = WSAStartup(WINSOCK_VERSION, &wasData);

	if (nErr != 0)
	{
		printf("was　error");
	}

	m_tcpClient = new CTcp_client;
	m_tcpClient->Init(plPAddress, nPortNum);

	for (int i = 0; i < MAX_PL; i++)
	{
		m_player[i] = new CDataPack;
	}
	m_myConnect.myConnect = false;
	m_myConnect.enemyConnect = false;

	std::thread ConnectOn([&] {m_myConnect = ConnectTh(m_tcpClient);});

	// スレッドをきりはなす
	ConnectOn.detach();

	std::thread ConnectRecv(Recv,this);
	// スレッドをきりはなす
	ConnectRecv.detach();
	return true;
}

//--------------------------
//破棄
//--------------------------
void CClient::Uninit(void)
{
	if (m_tcpClient != NULL)
	{
		m_tcpClient->Uninit();
		delete m_tcpClient;
		m_tcpClient = NULL;
	}

	for (int i = 0; i < MAX_PL; i++)
	{
		delete m_player[i];
		m_player[i] = nullptr;
	}
	
	WSACleanup();
}


//=============================================================================
// 通信スレッド
//=============================================================================
CClient::SConnectCheck CClient::ConnectTh(CTcp_client * tcp)
{
	SConnectCheck Connect;
	Connect.myConnect = false;
	Connect.enemyConnect = false;
	char aRecvData[1024];	// 受信データ
	int Timer = 0;
	// つながるまでループ
	while (!Connect.myConnect&&tcp->Connect())
	{

		Connect.myConnect = tcp->Connect();

		Timer++;
		if (Timer >= 2)
		{
			break;
		}
	}
	// 敵がつながるまでループ
	while (!Connect.enemyConnect)
	{
		int isRecv = tcp->Recv(&aRecvData[0], sizeof(bool));
		if (isRecv == 0)
		{
			return Connect;
		}
		memcpy(&Connect.enemyConnect, &aRecvData[0], sizeof(bool));
	}
	return Connect;
}

//=============================================================================
// レシーブスレッド
//=============================================================================
void CClient::Recv(CClient*data)
{
	//m_player[Num];
	// 繋がっている間はループ
	while (1)
	{
		if (!data->m_myConnect.enemyConnect)
		{

		}
		char aRecv[1024];	// 受信データ

		// 受信
		int nRecvSize = data->m_tcpClient->Recv(&aRecv[0], sizeof(CDataPack::SSendPack));

		// 受信データが無かったら
		if (nRecvSize < 0)
		{
			if (data->m_tcpClient != NULL)
			{
				data->m_tcpClient->Uninit();
	
				break;
			}
		}
		CDataPack::SSendPack Data;
		memcpy(&Data, &aRecv[0], (int)sizeof(CDataPack::SSendPack));
		data->m_player[0]->SetPlayer(Data);
	}
}

//=============================================================================
// コレデセンド
//=============================================================================
void  CClient::SendPlayerData(CModelData::SSendEnemy data)
{

	CModelData::SSendEnemy sendData = data;

	

	m_tcpClient->Send((const char*)&sendData, sizeof(CModelData::SSendEnemy));
}