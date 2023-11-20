//============================
//
// メイン設定のヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _MAIN_H_
#define _MAIN_H_


#define _WINSOCK_DEPRECATED_NO_WARNINGE
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include "nlohmann/json.hpp"
#include "letter.h"
#pragma comment (lib,"ws2_32.lib")
class  CTcp_client;
class CTcp_Listener;

const int MAX_P(4);

void CommuniCationClient(CTcp_client *pSendRecvP1, CTcp_client *pSendRecvP2, CTcp_client *pSendRecvP3, CTcp_client *pSendRecvP4, CTcp_Listener *pServer);


#endif