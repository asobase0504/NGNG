//============================
//
// メイン設定
// Author:hamada ryuuga
//
//============================
#include "main.h"
#include "tcp_listener.h"

#include "listener.h"
#include "client.h"

#include "model_data.h"

#include "udp_client.h"
#include <thread>

using namespace std;


int g_nRoomCount;

std::string EndAccess = "exit";
namespace nl = nlohmann;
const char* pathToJSON = "data/input.json";
CListener*pListenr = nullptr;

CModelData::SPlayerData player[MAX_P];
int m_hostPlayer;

void ThreadA(CClient*pClient)
{
	char aSendData[256] = {};

	int Data2 = 0;
	char aRecvData[50] = {};
	char aRecvData2[50] = {};
	char aRecvData3[50] = {};
	char aRecvData4[50] = {};

	pClient->Recv(&aRecvData[0], sizeof(int), CClient::TYPE_TUP);

	memcpy(&m_hostPlayer, &aRecvData[0], (int)sizeof(int));

	CClient*pClient2;
	CClient*pClient3;
	CClient*pClient4;

	pClient2 = pListenr->Accept();

	pClient2->Recv(&aRecvData2[0], sizeof(int), CClient::TYPE_TUP);

	memcpy(&Data2, &aRecvData2[0], (int)sizeof(int));
	

	pClient3 = pListenr->Accept();

	pClient3->Recv(&aRecvData3[0], sizeof(int), CClient::TYPE_TUP);

	memcpy(&Data2, &aRecvData3[0], (int)sizeof(int));

	pClient4 = pListenr->Accept();

	pClient4->Recv(&aRecvData4[0], sizeof(int), CClient::TYPE_TUP);

	memcpy(&Data2, &aRecvData4[0], (int)sizeof(int));
	printf("二つつながった\n");

	// スレッド生成
	thread th(CommuniCationClient, pClient, pClient2, pClient3, pClient4, pListenr);

	// スレッドを切り離す
	th.join();

}

void main(void)
{
	g_nRoomCount = 0;
	WSADATA wasData;
	m_hostPlayer = 0;
	int nErr = WSAStartup(WINSOCK_VERSION, &wasData);

	if (nErr != 0)
	{
		printf("was　error");
	}
	pListenr = new CListener;


	if (pListenr->Init(INADDR_ANY, 13678))
	{
		while (1)
		{
			CClient*pClient = pListenr->Accept();

			
			std::thread th(ThreadA, pClient);
			g_nRoomCount++;
			// 部屋を作り終えるまでブロック
			th.join();
			pListenr->UninitOn();
		}
		
	}

	pListenr->UninitOn();
	WSACleanup();

}

//--------------------------
// 1部屋事のマルチスレッド
//--------------------------
void CommuniCationClient(CClient *pSendRecvP1, CClient *pSendRecvP2, CClient *pSendRecvP3, CClient *pSendRecvP4, CListener *pServer)
{
	int nRecv = 1;
	int nUdpRecv = 0;
	int nSendTimer = 0;
	fd_set fds, readfds;
	SOCKET maxfd, sock[MAX_P];
	char aRecvData[2048];
	bool IsMapSelect;
	int score = 0;

	CReceiveData::SReceiveList sendData;
	sendData.Init();
	player[0].Player.m_MyId = P1;
	player[1].Player.m_MyId = P2;
	player[2].Player.m_MyId = P3;
	player[3].Player.m_MyId = P4;
	FD_ZERO(&readfds);
	cout << "部屋数 : " << g_nRoomCount << "\n" << endl;

	// ソケットの入手
	sock[0] = pSendRecvP1->GetUdp()->GetSock();
	sock[1] = pSendRecvP2->GetUdp()->GetSock();
	sock[2] = pSendRecvP3->GetUdp()->GetSock();
	sock[3] = pSendRecvP4->GetUdp()->GetSock();

	bool SetInit[4];
	SetInit[0] = false;
	SetInit[1] = false;
	SetInit[2] = false;
	SetInit[3] = false;

	player[0].Player.m_IsGame = true;
	player[1].Player.m_IsGame = true;
	player[2].Player.m_IsGame = true;
	player[3].Player.m_IsGame = true;

	for (int nCnt = 0; nCnt < MAX_P; nCnt++)
	{
		// 監視ソケットの登録
		FD_SET(sock[nCnt], &readfds);
	}
	// 最大ソケットの判定
	if (sock[0] > sock[1]&& sock[0] >sock[2] && sock[0] >sock[3])
	{
		maxfd = sock[0];
	}
	else if (sock[1] > sock[0] && sock[1] >sock[2] && sock[1] >sock[3])
	{
		maxfd = sock[1];
	}
	else if (sock[2] > sock[0] && sock[2] >sock[1] && sock[2] >sock[3])
	{
		maxfd = sock[2];
	}
	else if (sock[3] > sock[0] && sock[3] >sock[1] && sock[3] >sock[2])
	{
		maxfd = sock[3];
	}

	while (1)
	{
		memcpy(&fds, &readfds, sizeof(fd_set));
		// ソケットの監視
		select(maxfd + 3, &fds, NULL, NULL, NULL);
		// プレイヤー1にsendされていたら
		if (FD_ISSET(sock[0], &fds))
		{
			nRecv = pSendRecvP1->Recv(&aRecvData[0], sizeof(CModelData::SSendPack), CClient::TYPE_UDP);
		
			if (nRecv == sizeof(CModelData::SSendPack))
			{
				CModelData::SSendPack Data;
				memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendPack));

				player[0].SetPlayer(Data);

				sendData.SetListPlayr(Data.m_PlayData,0);
				sendData.SetListEnemy(&Data.m_isPopEnemy[0]);
				sendData.SetListGimmick(&Data.m_isPopGimmick[0]);

				score += Data.m_addscore;
				Data.m_score = score;
				SetInit[0] = true;
			}
		}
		// プレイヤー2にsendされていたら
		if (FD_ISSET(sock[1], &fds))
		{
			nRecv = pSendRecvP2->Recv(&aRecvData[0], sizeof(CModelData::SSendPack), CClient::TYPE_UDP);
			if (nRecv == sizeof(CModelData::SSendPack))
			{
				CModelData::SSendPack Data;
				memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendPack));

				player[1].SetPlayer(Data);

				sendData.SetListPlayr(Data.m_PlayData, 1);
				sendData.SetListEnemy(&Data.m_isPopEnemy[0]);
				sendData.SetListGimmick(&Data.m_isPopGimmick[0]);

				score += Data.m_addscore;
				Data.m_score = score;
				SetInit[1] = true;
			}
		}
		// プレイヤー2にsendされていたら
		if (FD_ISSET(sock[2], &fds))
		{
			nRecv = pSendRecvP2->Recv(&aRecvData[0], sizeof(CModelData::SSendPack), CClient::TYPE_UDP);
			if (nRecv == sizeof(CModelData::SSendPack))
			{
				CModelData::SSendPack Data;
				memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendPack));

				player[2].SetPlayer(Data);

				sendData.SetListPlayr(Data.m_PlayData, 2);
				sendData.SetListEnemy(&Data.m_isPopEnemy[0]);
				sendData.SetListGimmick(&Data.m_isPopGimmick[0]);

				score += Data.m_addscore;
				Data.m_score = score;
				SetInit[2] = true;
			}
		}
		// プレイヤー2にsendされていたら
		if (FD_ISSET(sock[3], &fds))
		{
			nRecv = pSendRecvP2->Recv(&aRecvData[0], sizeof(CModelData::SSendPack), CClient::TYPE_UDP);
			if (nRecv == sizeof(CModelData::SSendPack))
			{
				CModelData::SSendPack Data;
				memcpy(&Data, &aRecvData[0], (int)sizeof(CModelData::SSendPack));

				player[3].SetPlayer(Data);

				sendData.SetListPlayr(Data.m_PlayData, 3);
				sendData.SetListEnemy(&Data.m_isPopEnemy[0]);
				sendData.SetListGimmick(&Data.m_isPopGimmick[0]);

				score += Data.m_addscore;
				Data.m_score = score;
				SetInit[3] = true;
			}
		}

		if (SetInit[0] &&SetInit[1] &&SetInit[2] &&SetInit[3])
		{
			nRecv = pSendRecvP1->Send((const char*)&sendData, sizeof(CReceiveData::SReceiveList), CClient::TYPE_UDP);
			nRecv = pSendRecvP2->Send((const char*)&sendData, sizeof(CReceiveData::SReceiveList), CClient::TYPE_UDP);
			nRecv = pSendRecvP3->Send((const char*)&sendData, sizeof(CReceiveData::SReceiveList), CClient::TYPE_UDP);
			nRecv = pSendRecvP4->Send((const char*)&sendData, sizeof(CReceiveData::SReceiveList), CClient::TYPE_UDP);

			SetInit[0] = false;
			SetInit[1] = false;
			SetInit[2] = false;
			SetInit[3] = false;
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
	cout << "部屋が解散されました。\n" << endl;
	cout << "部屋数 : [" << g_nRoomCount <<"]\n"<< endl;
}

void MapSend(CClient *pSendRecvP1, CClient *pSendRecvP2, CListener *pServer,int ID)
{
	int nRecv = 1;
	int nSendTimer = 0;
	fd_set fds, readfds;
	SOCKET maxfd, sock[MAX_P];
	char aRecvData[1024];
	bool IsMapSelect;
	int score = 0;
	FD_ZERO(&readfds);
	SSendMap map;
	map.isMap = false;
	map.sendMap = 0;
	char aSendData[256] = {};


	cout << "マップえらんでます :部屋の数[" << g_nRoomCount<< "]\n" << endl;

	// ソケットの入手
	sock[0] = pSendRecvP1->GetTcp()->GetSock();
	sock[1] = pSendRecvP2->GetTcp()->GetSock();

	for (int nCnt = 0; nCnt < MAX_P; nCnt++)
	{
		// 監視ソケットの登録
		FD_SET(sock[nCnt], &readfds);
	}
	// 最大ソケットの判定
	if (sock[0] > sock[1])
	{
		maxfd = sock[0];
	}
	else if (sock[1] > sock[0])
	{
		maxfd = sock[1];
	}

	while (!map.isMap)
	{

		if (ID == 0)
		{
			printf("ホストは「最初に繋いだPC」です\n");
			pSendRecvP1->Recv(&aRecvData[0], sizeof(SSendMap), CClient::TYPE_TUP);
			memcpy(&map, &aRecvData, sizeof(SSendMap));
			pSendRecvP2->Send(&aRecvData[0], sizeof(SSendMap), CClient::TYPE_TUP);
		}

		if (ID == 1)
		{
			printf("ホストは「二番目に繋いだPC」です\n");
			pSendRecvP2->Recv(&aRecvData[0], sizeof(SSendMap), CClient::TYPE_TUP);
			memcpy(&map, &aRecvData, sizeof(SSendMap));
			pSendRecvP1->Send(&aRecvData[0], sizeof(SSendMap), CClient::TYPE_TUP);
		}
	}

	printf("[MAP]確認送信[%d]番目マップ\n", map.sendMap);

	bool bMapConnect = true;
	memcpy(&aSendData[0], &bMapConnect, sizeof(bool));
	pSendRecvP1->Send(&aSendData[0], sizeof(bool), CClient::TYPE_TUP);

	// プレイヤー2にsend
	memcpy(&aSendData[0], &bMapConnect, sizeof(bool));
	pSendRecvP2->Send(&aSendData[0], sizeof(bool), CClient::TYPE_TUP);

	player[0].Player.m_IsGame = true;
	player[1].Player.m_IsGame = true;

}

