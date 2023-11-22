//============================
//
// メイン設定
// Author:hamada ryuuga
//
//============================
#include "main.h"
#include "tcp_listener.h"
#include "model_date.h"
#include <thread>

using namespace std;

struct SSetUp
{
	int m_Num;
	bool bConnect;
};

int g_nRoomCount;

std::string EndAccess = "exit";
namespace nl = nlohmann;
const char* pathToJSON = "data/input.json";
CTcp_Listener*pListenr = nullptr;


void ThreadA(CTcp_client*pClient)
{
	char aSendData[256] = {};

	int Data = 0;
	int Data2 = 0;
	char aRecvData[50] = {};
	char aRecvData2[50] = {};
	pClient->Recv(&aRecvData[0], sizeof(int));
	
	memcpy(&Data, &aRecvData[0], (int)sizeof(int));

	CTcp_client*pClient2;

	pClient2 = pListenr->Accept();

	CTcp_client*pClient3;
	pClient3 = pListenr->Accept();

	CTcp_client*pClient4;
	pClient4 = pListenr->Accept();



	printf("二つつながった");

	SSetUp SetUp;
	SetUp.bConnect = true;
	SetUp.m_Num = 0;

	// プレイヤー1にsend
	pClient->Send((const char*)&SetUp, sizeof(SSetUp));
	SetUp.m_Num++;
	// プレイヤー2にsend

	pClient2->Send((const char*)&SetUp, sizeof(SSetUp));
	SetUp.m_Num++;
	// プレイヤー3にsend

	pClient3->Send((const char*)&SetUp, sizeof(SSetUp));
	SetUp.m_Num++;
	// プレイヤー4にsend

	pClient4->Send((const char*)&SetUp, sizeof(SSetUp));
	SetUp.m_Num++;

	// スレッド生成
	thread th(CommuniCationClient, pClient, pClient2, pClient3, pClient4, pListenr);

	// スレッドを切り離す
	th.detach();

}

void main(void)
{
	g_nRoomCount = 0;

	WSADATA wasData;

	int nErr = WSAStartup(WINSOCK_VERSION, &wasData);

	if (nErr != 0)
	{
		printf("was　error");
	}
	pListenr = new CTcp_Listener;

	if (pListenr->Init(INADDR_ANY, 13567))
	{
		while (1)
		{
			CTcp_client*pClient = pListenr->Accept();

			
			std::thread th(ThreadA, pClient);
			g_nRoomCount++;
			// 部屋を作り終えるまでブロック
			th.join();

		}
		pListenr->Uninit();
	}
	WSACleanup();

}

//--------------------------
// 1部屋事のマルチスレッド
//--------------------------
void CommuniCationClient(CTcp_client *pSendRecvP1, CTcp_client *pSendRecvP2, CTcp_client *pSendRecvP3, CTcp_client *pSendRecvP4, CTcp_Listener *pServer)
{
	int nRecv = 1;
	int nSendTimer = 0;
	fd_set fds, readfds;
	SOCKET maxfd, sock[MAX_P];
	char aRecvData[1024];
	FD_ZERO(&readfds);
	CModelData::SPlayerDate player[MAX_P];
	CDataPack::SSendPack model;

	cout << "部屋数 : " << g_nRoomCount << endl;

	// ソケットの入手
	sock[0] = pSendRecvP1->GetSock();
	sock[1] = pSendRecvP2->GetSock();
	sock[2] = pSendRecvP3->GetSock();
	sock[3] = pSendRecvP4->GetSock();

	for (int nCnt = 0; nCnt < MAX_P; nCnt++)
	{
		// 監視ソケットの登録
		FD_SET(sock[nCnt], &readfds);
	}
	// 最大ソケットの判定
	if (sock[0] > sock[1] && sock[0] > sock[2] && sock[0] > sock[3])
	{
		maxfd = sock[0];
	}
	else if (sock[1] > sock[0] && sock[1] > sock[2] && sock[1] > sock[3])
	{
		maxfd = sock[1];
	}
	else if (sock[2] > sock[0] && sock[2] > sock[1] && sock[2] > sock[3])
	{
		maxfd = sock[2];
	}
	else if (sock[3] > sock[0] && sock[3] > sock[1] && sock[3] > sock[2])
	{
		maxfd = sock[3];
	}
	
	while (nRecv != -1)
	{
		memcpy(&fds, &readfds, sizeof(fd_set));

		// ソケットの監視
		select(maxfd + 1, &fds, NULL, NULL, NULL);
		
		// プレイヤー1にsendされていたら
		if (FD_ISSET(sock[0], &fds))
		{

			nRecv = pSendRecvP1->Recv(&aRecvData[0], sizeof(CModelData::SSendEnemy));

			CModelData::SSendEnemy Data;
			memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendEnemy));

			player[0].SetPlayer(Data);
			
			//pSendRecvP2->Send(&aRecvData[0], sizeof(CModelData::SSendEnemy));

		}
		// プレイヤー2にsendされていたら
		if (FD_ISSET(sock[1], &fds))
		{
			nRecv = pSendRecvP2->Recv(&aRecvData[0], sizeof(CModelData::SSendEnemy));
	
			CModelData::SSendEnemy Data;
			memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendEnemy));
			player[1].SetPlayer(Data);

			//pSendRecvP1->Send(&aRecvData[0], sizeof(CModelData::SSendEnemy));
		}
		if (FD_ISSET(sock[2], &fds))
		{
			nRecv = pSendRecvP3->Recv(&aRecvData[0], sizeof(CModelData::SSendEnemy));

			CModelData::SSendEnemy Data;
			memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendEnemy));

			player[2].SetPlayer(Data);

		}
		if (FD_ISSET(sock[3], &fds))
		{
			nRecv = pSendRecvP4->Recv(&aRecvData[0], sizeof(CModelData::SSendEnemy));

			CModelData::SSendEnemy Data;
			memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendEnemy));

			player[3].SetPlayer(Data);

		}

		nSendTimer++;
		if (nSendTimer >= 10)
		{
			for (int i = 0; i < 4; i++)
			{
				model.Player[i].m_pos = player[i].Player.m_pos;
				model.Player[i].m_rot = player[i].Player.m_rot;
			}
			
			pSendRecvP1->Send((const char*)&model, sizeof(CDataPack::SSendPack));
			pSendRecvP2->Send((const char*)&model, sizeof(CDataPack::SSendPack));
			pSendRecvP3->Send((const char*)&model, sizeof(CDataPack::SSendPack));
			pSendRecvP4->Send((const char*)&model, sizeof(CDataPack::SSendPack));


			nSendTimer = 0;
		}
	}

	pSendRecvP1->Uninit();
	pSendRecvP2->Uninit();
	pSendRecvP3->Uninit();
	pSendRecvP4->Uninit();

	delete pSendRecvP1;
	delete pSendRecvP2;
	delete pSendRecvP3;
	delete pSendRecvP4;

	g_nRoomCount--;
	cout << "部屋が解散されました。" << endl;
	cout << "部屋数 : " << g_nRoomCount << endl;
}

