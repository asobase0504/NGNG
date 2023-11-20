//============================
//
// メイン設定
// Author:hamada ryuuga
//
//============================
#include "main.h"
#include "tcp_client.h"



//--------------------------
//コンスト
//--------------------------
CTcp_client::CTcp_client()
{
	m_sock = INVALID_SOCKET;
}
//--------------------------
//デストラクト
//--------------------------
CTcp_client::~CTcp_client()
{
}

//--------------------------
//初期化
//--------------------------
bool CTcp_client::Init(const char*plPAddress, int nPortNum)
{
	

	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		printf("socket　error");
		return false;
	}
	const char *pIPAddress = plPAddress;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPortNum);
	addr.sin_addr.S_un.S_addr = inet_addr(pIPAddress);

	if (connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) != 0)
	{
		printf("if　sock error");
		return false;
	}
	return true;
}
//--------------------------
//オーバーロード初期化
//--------------------------
bool CTcp_client::Init(SOCKET sock)
{
	m_sock = sock;
	return true;
}
//--------------------------
//接続
//--------------------------
int CTcp_client::Send(const char*pSendData, int nSendDataSize)
{
	send(m_sock, &pSendData[0], nSendDataSize, 0);

	return nSendDataSize;
}

//--------------------------
//返信
//--------------------------
int CTcp_client::Recv(char*pRecvData, int nRecvDataSize)
{
	
	int nRecvByte = recv(m_sock, &pRecvData[0], nRecvDataSize, 0);

	//printf("%s", &pRecvData[0]);

	return nRecvByte;
}


//--------------------------
//接続
//--------------------------
int CTcp_client::Sendto(const char*pSendData, int nSendDataSize)
{
	sendto(m_sock, &pSendData[0], nSendDataSize, 0, (struct sockaddr *)&m_clientAddr, sizeof(m_clientAddr));

	return strlen(&pSendData[0]) + 1;
}


//--------------------------
//返信
//--------------------------
int CTcp_client::Recvfrom(char*pRecvData, int nRecvDataSize)
{

	//int receivedBytes = recvfrom(m_sock, &pRecvData[0], nRecvDataSize, 0, (struct sockaddr *)&m_clientAddr, sizeof(m_clientAddr));
	printf("%s", &pRecvData[0]);

	return 0;
}

//--------------------------
//破棄
//--------------------------
void CTcp_client::Uninit(void) 
{
	closesocket(m_sock);

}
