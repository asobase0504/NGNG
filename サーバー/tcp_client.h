//============================
//
// clientê›íË
// Author:hamada ryuuga
//
//============================

#ifndef _TCP_CKIENT_H_
#define _TCP_CKIENT_H_

#include "main.h"


//ç\ë¢ëÃ


class  CTcp_client
{
public:
	CTcp_client();
	~CTcp_client();
	bool Init(const char*plPAddress, int nPortNum); bool Init(SOCKET sock);
	int Send(const char*pSendData, int nSendDataSize);
	int Recv(char*pRecvData, int nRecvDataSize);
	int Sendto(const char*pSendData, int nSendDataSize);
	int Recvfrom(char*pRecvData, int nRecvDataSize);
	void Uninit(void);
	SOCKET GetSock() {return m_sock;}
	sockaddr_in GetSockAdd() { return m_clientAddr; }
private:
	SOCKET m_sock;
	sockaddr_in m_serverAddr;
	sockaddr_in m_clientAddr;
};

#endif