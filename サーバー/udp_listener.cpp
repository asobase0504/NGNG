//**************************************************
// ヘッダーをインクルード
//**************************************************
#include "udp_client.h"

#include <sys/types.h>
#include "udp_listener.h"
#include <cerrno>  // errno ヘッダをインクルード
#include <cstring> // strerror 関数を使用するために必要
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CUdp_Listner::CUdp_Listner()
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CUdp_Listner::~CUdp_Listner()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
bool CUdp_Listner::Init(const char*plPAddress, int nPortNum)
{

	m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (m_sockfd == INVALID_SOCKET)
	{
		printf("「UDP」socket　error");
		return false;
	}

	printf("「UDP」初期化開始じゃ\n");

	m_nPortNum = nPortNum;   

	memset(&m_serverAddr, 0, sizeof(m_serverAddr));

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(nPortNum);//ポート
	m_serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;//IP


	//bind(m_sockfd, (struct sockaddr*)&m_serverAddr, sizeof(m_serverAddr));

	if (bind(m_sockfd, reinterpret_cast<struct sockaddr*>(&m_serverAddr), sizeof(m_serverAddr)) == -1)
	{
		std::cerr << "Error binding socket." << std::endl;
		closesocket(m_sockfd);
		return false;
	}
	
	return true;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CUdp_Listner::Uninit()
{
	closesocket(m_sockfd);
	WSACleanup();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CUdp_Listner::UpData()
{

}

CUdp_Client * CUdp_Listner::Accept()
{
	char buf[100]; // 受信バッファ

	// 受信バッファの初期化
	memset(buf, 0, sizeof(buf));

	CUdp_Client*pUdp_Socket;
	pUdp_Socket = new CUdp_Client;
	int Size = sizeof(m_serverAddr);
	pUdp_Socket->Init(m_sockfd);
	pUdp_Socket->SetAddr(m_serverAddr);
	int list = pUdp_Socket->Recv(&buf[0], 4);
	//int size = recvfrom(m_sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&m_serverAddr, &Size);




	return pUdp_Socket;
}
