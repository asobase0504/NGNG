//============================
//
// メイン設定
// Author:hamada ryuuga
//
//============================
#include "main.h"
#include "tcp_listener.h"
#include "tcp_client.h"
#include "udp_client.h"

//--------------------------
//コンスト
//--------------------------
CTcp_Listener::CTcp_Listener()
{
	m_sockServer = INVALID_SOCKET;
}
//--------------------------
//デストラクト
//--------------------------
CTcp_Listener::~CTcp_Listener()
{
}


//--------------------------
//初期化
//--------------------------
bool CTcp_Listener::Init(const char*plPAddress, int nPortNum)
{
	m_sockServer = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockServer == INVALID_SOCKET)
	{
		printf("「TCP」socket　error");
		return false;
	}

	printf("「TCP」初期化開始じゃ\n");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);//ポート
	addr.sin_addr.S_un.S_addr = INADDR_ANY;//IP
	bind(m_sockServer, (struct sockaddr*)&addr, sizeof(addr));
	listen(m_sockServer, 10);

	return true;
}
//--------------------------
//あくせくと
//--------------------------
CTcp_Client* CTcp_Listener::Accept()
{
	
	struct sockaddr_in clientAddr;
	int nLength = sizeof(clientAddr);
	CTcp_Client*pTcp_client;
	pTcp_client = new CTcp_Client;

	SOCKET sock = accept(m_sockServer, (struct sockaddr*)&clientAddr, &nLength);

	pTcp_client->Init(sock);

	printf("アクセス中じゃ\n");


	return pTcp_client;
}
//--------------------------
//破棄
//--------------------------
void CTcp_Listener::Uninit(void)
{
	closesocket(m_sockServer);
}
