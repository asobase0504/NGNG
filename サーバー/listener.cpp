//============================
//
// ���C���ݒ�
// Author:hamada ryuuga
//
//============================
#include "main.h"
#include "tcp_listener.h"
#include "udp_listener.h"
#include "listener.h"
#include "tcp_client.h"
#include "udp_client.h"

//--------------------------
//�R���X�g
//--------------------------
CListener::CListener()
{
	m_tcpSockServer = INVALID_SOCKET;

	m_udpSockServer = INVALID_SOCKET;
}
//--------------------------
//�f�X�g���N�g
//--------------------------
CListener::~CListener()
{
}


//--------------------------
//������
//--------------------------
bool CListener::Init(const char*plPAddress, int nPortNum)
{
	printf("�X�[�p�[�A�V�X�^���gAI�u�S���v����I�T�[�o�[�̊Ǘ�����`�����I\n");
	m_udp = new CUdp_Listner;
	m_tcp = new CTcp_Listener;

	m_udp->Init(plPAddress, nPortNum);
	m_tcp->Init(plPAddress, nPortNum);


	printf("�A�N�Z�X��������\nIP:%s \nPORT:%d \n", &plPAddress[0],nPortNum);


	return true;
}
//--------------------------
//����������
//--------------------------
CClient* CListener::Accept()
{
	CClient *client  = new CClient;

	printf("�uTCP�vOK �A�N�Z�X�J�n����\n");

	client->SetTcp(m_tcp->Accept());
	printf("�uTCP�vsock:%d\n", client->GetTcp()->GetSock());

	printf("�uTCP�vOK �A�N�Z�X��������\n");

	printf("�uUDP�vOK �A�N�Z�X�J�n����\n");

	client->SetUdp(m_udp->Accept());

	printf("�uUDP�vsock:%d\n", client->GetUdp()->GetSock());
	printf("�uUDP�vsockAddr:%lu\n",client->GetUdp()->GetAddr().sin_addr.S_un.S_addr);

	printf("�uUDP�vOK �A�N�Z�X��������\n");
	printf("�uAll�v OK �A�N�Z�X��������\n");

	return client;
}
//--------------------------
//�j��
//--------------------------
void CListener::Uninit(void)
{
	if (m_udp != nullptr)
	{
		m_udp->Uninit();
		// �������̉��
		delete m_udp;
		m_udp = nullptr;
	}

	if (m_tcp != nullptr)
	{
		m_tcp->Uninit();
		// �������̉��
		delete m_tcp;
		m_tcp = nullptr;
	}

}

//--------------------------
//�j��
//--------------------------
void CListener::UninitOn(void)
{
	if (m_udp != nullptr)
	{
		m_udp->Uninit();
	}

	if (m_tcp != nullptr)
	{
		m_tcp->Uninit();
	}

}