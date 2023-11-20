//============================
//
// clientê›íË
// Author:hamada ryuuga
//
//============================

#ifndef _TCP_CKIENT_H_
#define _TCP_CKIENT_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGE
#include <winsock2.h>
#include <stdio.h>
#include <string>

#pragma comment (lib,"ws2_32.lib")


class  CTcp_client
{
public:
	CTcp_client();
	~CTcp_client();
	bool Init(const char*plPAddress,int nPortNum);
	int Send(const char*pSendData, int nSendDataSize);
	int Recv(char*pRecvData, int nRecvDataSize);
	void Uninit();
	bool Connect();
	//void ConnectTh();
private:
	std::string m_Ip;
	int m_nPortNum;
	SOCKET m_sock;
	bool m_sockOk;

	
};

#endif