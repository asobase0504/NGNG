//============================
//
// serverê›íË
// Author:hamada ryuuga
//
//============================

#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "main.h"

#include "client.h"


//ç\ë¢ëÃ
class CUdp_Listner;
class  CTcp_Listener;

class  CListener
{
public:

	struct CListnerList
	{
		CUdp_Listner* m_udp;
		CTcp_Listener* m_tcp;
	};

	CListener();
	~CListener();
	bool Init(const char*plPAddress, int nPortNum);
	CClient* Accept();
	void Uninit(void);
	void UninitOn();
	CUdp_Listner* GetUdpListner() { return m_udp; }
	CTcp_Listener* GetTcpListener() { return m_tcp; }

private:

	
	SOCKET m_udpSockServer;
	SOCKET m_tcpSockServer;

	CUdp_Listner* m_udp;
	CTcp_Listener* m_tcp;

};



#endif