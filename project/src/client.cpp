//============================
//
// ���C���ݒ�
// Author:hamada ryuuga
//
//============================
#include "tcp_client.h"
#include "udp_client.h"
#include "client.h"


//--------------------------
//�R���X�g
//--------------------------
CClient::CClient()
{
	m_Socket = new CClientList;
	m_Socket->m_udp = new CUdp_Client;
	m_Socket->m_tcp = new CTcp_Client;
}
//--------------------------
//�f�X�g���N�g
//--------------------------
CClient::~CClient()
{
}

//--------------------------
//������
//--------------------------
bool CClient::Init(const char*plPAddress, int nPortNum)
{


	m_Socket->m_udp->Init(plPAddress, nPortNum);
	m_Socket->m_tcp->Init(plPAddress, nPortNum);

	return true;
}
//--------------------------
//�I�[�o�[���[�h������
//--------------------------
bool CClient::Init(CClientList* List)
{

	m_Socket = List;

	return true;
}
//--------------------------
//�ڑ�
//--------------------------
int CClient::Send(const char*pSendData, int nSendDataSize, CONNECT_TYPE type)
{
	switch (type)
	{
	case CClient::TYPE_UDP:
		m_Socket->m_udp->Send(pSendData, nSendDataSize);
		break;
	case CClient::TYPE_TUP:
		m_Socket->m_tcp->Send(pSendData, nSendDataSize);
		break;
	case CClient::MAX_TYPE:
		break;
	default:
		break;
	}

	return nSendDataSize;
}

//--------------------------
//�ԐM
//--------------------------
int CClient::Recv(char*pRecvData, int nRecvDataSize, CONNECT_TYPE type)
{

	int nRecvByte = 0;
	switch (type)
	{
	case CClient::TYPE_UDP:
		nRecvByte = m_Socket->m_udp->Recv(pRecvData, nRecvDataSize);
		break;
	case CClient::TYPE_TUP:
		nRecvByte = m_Socket->m_tcp->Recv(pRecvData, nRecvDataSize);
		break;
	case CClient::MAX_TYPE:
		break;
	default:
		break;
	}
	return nRecvByte;
}

//--------------------------
//�j��
//--------------------------
void CClient::Uninit(void)
{
	if (m_Socket->m_udp != nullptr)
	{
		m_Socket->m_udp->Uninit();
		// �������̉��
		delete m_Socket->m_udp;
		m_Socket->m_udp = nullptr;
	}

	if (m_Socket->m_tcp != nullptr)
	{
		m_Socket->m_tcp->Uninit();
		// �������̉��
		delete m_Socket->m_tcp;
		m_Socket->m_tcp = nullptr;
	}

	if (m_Socket!= nullptr)
	{//������
		delete m_Socket;
		m_Socket = nullptr;
	}

}
