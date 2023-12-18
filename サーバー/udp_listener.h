//============================
//
// 背景
// Author:hamada ryuuga
//
//============================
#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

//**************************************************
// インクルード
//**************************************************
class CUdp_Client;
//**************************************************
// クラス
//**************************************************
// ソケット通信クラス
class CUdp_Listner
{
public:
	CUdp_Listner();
	~CUdp_Listner();

	bool Init(const char*plPAddress, int nPortNum);

	void Uninit();
	void UpData();

	void SetSockfd(SOCKET sockfd) { m_sockfd = sockfd; }

	CUdp_Client* Accept();


private:
	SOCKET m_sockfd;
	sockaddr_in m_serverAddr;
	sockaddr_in m_clientAddr;
	int m_nPortNum;
};

#endif
