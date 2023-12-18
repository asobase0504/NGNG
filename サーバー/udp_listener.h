//============================
//
// �w�i
// Author:hamada ryuuga
//
//============================
#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

//**************************************************
// �C���N���[�h
//**************************************************
class CUdp_Client;
//**************************************************
// �N���X
//**************************************************
// �\�P�b�g�ʐM�N���X
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
