//============================
//
// clientê›íË
// Author:hamada ryuuga
//
//============================

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "main.h"

#include "tcp_client.h"



//ç\ë¢ëÃ


class  CTcp_Listener
{
public:
	CTcp_Listener();
	~CTcp_Listener();
	bool Init(const char*plPAddress, int nPortNum);
	CTcp_client* Accept();
	void Uninit(void);


private:
	SOCKET m_sockServer;

};



#endif