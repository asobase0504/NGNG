//============================
//
// メイン設定
// Author:hamada ryuuga
//
//============================
#include "main.h"
#include "tcp_listener.h"
#include "udp_listener.h"
#include "listener.h"
#include "tcp_client.h"
#include "udp_client.h"

//--------------------------
//コンスト
//--------------------------
CListener::CListener()
{
	m_tcpSockServer = INVALID_SOCKET;

	m_udpSockServer = INVALID_SOCKET;
}
//--------------------------
//デストラクト
//--------------------------
CListener::~CListener()
{
}


//--------------------------
//初期化
//--------------------------
bool CListener::Init(const char*plPAddress, int nPortNum)
{
	printf("スーパーアシスタントAI「ゴン」じゃ！サーバーの管理を手伝うぞ！\n");
	m_udp = new CUdp_Listner;
	m_tcp = new CTcp_Listener;

	m_udp->Init(plPAddress, nPortNum);
	m_tcp->Init(plPAddress, nPortNum);


	printf("アクセス準備完了\nIP:%s \nPORT:%d \n", &plPAddress[0],nPortNum);


	return true;
}
//--------------------------
//あくせくと
//--------------------------
CClient* CListener::Accept()
{
	CClient *client  = new CClient;

	printf("「TCP」OK アクセス開始じゃ\n");

	client->SetTcp(m_tcp->Accept());
	printf("「TCP」sock:%d\n", client->GetTcp()->GetSock());

	printf("「TCP」OK アクセス完了じゃ\n");

	printf("「UDP」OK アクセス開始じゃ\n");

	client->SetUdp(m_udp->Accept());

	printf("「UDP」sock:%d\n", client->GetUdp()->GetSock());
	printf("「UDP」sockAddr:%lu\n",client->GetUdp()->GetAddr().sin_addr.S_un.S_addr);

	printf("「UDP」OK アクセス完了じゃ\n");
	printf("「All」 OK アクセス完了じゃ\n");

	return client;
}
//--------------------------
//破棄
//--------------------------
void CListener::Uninit(void)
{
	if (m_udp != nullptr)
	{
		m_udp->Uninit();
		// メモリの解放
		delete m_udp;
		m_udp = nullptr;
	}

	if (m_tcp != nullptr)
	{
		m_tcp->Uninit();
		// メモリの解放
		delete m_tcp;
		m_tcp = nullptr;
	}

}

//--------------------------
//破棄
//--------------------------
void CListener::UninitOn(void)
{
	if (m_udp != nullptr)
	{
		m_udp->Uninit();
	}

	if (m_tcp != nullptr)
	{
		m_tcp->Uninit();
	}

}