//============================
//
// 背景
// Author:hamada ryuuga
//
//============================
#ifndef _UTC_SOCKET_H_
#define _UTC_SOCKET_H_

//**************************************************
// インクルード
//**************************************************
#include "protocol.h"
class CModel;
//**************************************************
// クラス
//**************************************************
// ソケット通信クラス
class CUtc_Socket
{
public:
	CUtc_Socket();
	~CUtc_Socket();

	void Init();
	void Uninit();
	void Update();
	void LogError(const char* errorMessage);
	void LogInfo(const char* format, ...);

private:
	SOCKET m_sockfd;
	sockaddr_in m_serverAddr;
	sockaddr_in m_clientAddr;
	std::vector<CModel*> m_model;
	std::vector<CModel*> m_Enemy;
	int m_listSize;
	int m_EnemySize;

	void Send(char* recvBuffer);
	int Recv(char* recvBuffer, int Size);
	std::string SetComand(char* recvBuffer, int Id);
	std::string _Moveid(char* recvBuffer, int id);
	std::string _Move(char* recvBuffer, int id);
	std::string _GetIs(char* recvBuffer, int id);
	std::string _PopIs(char* recvBuffer, int id);
	std::string _GetEnemy(char* recvBuffer, int id);
	std::string _MoveEnemy(char* recvBuffer, int id);
	std::string ConvertD3DXVECTOR3ToChar(const D3DXVECTOR3& vector);
	void ConvertFloatToNetworkOrder(float& value);
	float ConvertFloatToHostOrder(float& value);
	D3DXVECTOR3 ConvertCharToD3DXVECTOR3(const std::string& data);
};

#endif

#pragma once
