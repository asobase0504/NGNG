<<<<<<< Updated upstream
//============================
//
// client�ݒ�
// Author:hamada ryuuga
//
//============================

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "model_data.h"


//�\����

class CTcp_client;
class CDataPack;
class  CClient
{

=======
//============================
//
// client�ݒ�
// Author:hamada ryuuga
//
//============================

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "model_data.h"
#include "client.h"

//�\����

class CClient;
class CDataPack;
class  ConnectManager
{

>>>>>>> Stashed changes
	struct SConnectCheck
	{
		int myConnect;
		bool enemyConnect;
<<<<<<< Updated upstream
	};

public:
	const int MAX_PL = 4;
public:
	CClient();
	~CClient();
	bool Init(const char*plPAddress, int nPortNum);
	void Uninit(void);
	static SConnectCheck ConnectTh(CTcp_client * tcp);
	static void Recv(CClient*data);
	void SendPlayerData(CModelData::SSendEnemy Data);
	bool GetIsConnect() { return m_myConnect.enemyConnect; }
private:
	CTcp_client *m_tcpClient;
	SConnectCheck m_myConnect;		//�����ɐڑ�����
	CDataPack::SSendPack m_player;	//�ۑ�����v���C���[�f�[�^�̕ۑ���

};

=======
	};

public:
	const int MAX_PL = 4;
public:
	ConnectManager();
	~ConnectManager();
	bool Init(const char*plPAddress, int nPortNum);
	void Uninit(void);
	static SConnectCheck ConnectTh(CClient * Client);

	static void RecvPlayerData(ConnectManager *list);
	void SendPlayerData(CModelData::SSendPack Data);

	int Recv(char*Recv, int Size, CClient::CONNECT_TYPE Tipe);
	void Send(const char*send, int Size, CClient::CONNECT_TYPE Tipe);


	bool GetIsConnect() { return m_myConnect.enemyConnect; }
	CClient *GetClient() { return m_client; }

private:
	CClient *m_client;				//�N���C�A���g�����}�l�[�W���[
	SConnectCheck m_myConnect;		//�����ɐڑ�����
	CReceiveData::SReceiveList m_player;	//�ۑ�����v���C���[�f�[�^�̕ۑ���

};

>>>>>>> Stashed changes
#endif