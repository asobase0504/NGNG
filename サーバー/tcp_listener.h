//============================
//
// clientê›íË
// Author:hamada ryuuga
//
//============================

#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

#include "main.h"

#include "tcp_client.h"


//ç\ë¢ëÃ


class  CTcp_Listener
{
public:
	CTcp_Listener();
	~CTcp_Listener();
	bool Init(const char*plPAddress, int nPortNum);
	CTcp_Client* Accept();
	void Uninit(void);


private:
	SOCKET m_sockServer;
};



#endif