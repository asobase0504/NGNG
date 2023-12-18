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
class  CClient;
class CListener;

const int MAX_P(4);

void MapSend(CClient *pSendRecvP1, CClient *pSendRecvP2, CListener *pServer, int ID);
void MapSendreplay(CClient * pSendRecvP1, CClient * pSendRecvP2, CListener * pServer, int ID, char*receive);
void CommuniCationClient(CClient *pSendRecvP1, CClient *pSendRecvP2, CClient *pSendRecvP3, CClient *pSendRecvP4, CListener *pServer);


#endif