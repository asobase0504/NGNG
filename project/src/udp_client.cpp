//============================
//
// �N���C�A���g�ݒ�
// Author:hamada ryuuga
//
//============================

//**************************************************
// �w�b�_�[���C���N���[�h
//**************************************************
#include "udp_client.h"

#include <sys/types.h>

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CUdp_Client::CUdp_Client()
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CUdp_Client::~CUdp_Client()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
bool CUdp_Client::Init(const char*plPAddress, int nPortNum)
{
	m_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		printf("socket�@error");
		return false;
	}
	memset(&m_clientAddr, 0, sizeof(m_clientAddr));
	m_clientAddr.sin_family = AF_INET;
	m_clientAddr.sin_port = htons(nPortNum);
	m_clientAddr.sin_addr.S_un.S_addr = inet_addr(plPAddress);

	return true;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CUdp_Client::Uninit()
{
	closesocket(m_sock);
	WSACleanup();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CUdp_Client::UpData()
{	
}

//--------------------------------------------------
// ���M
//--------------------------------------------------
void CUdp_Client::Send(const char *pSendData, int Size)
{
	if (m_sock == INVALID_SOCKET)
	{
		return;
	}

	sendto(m_sock, pSendData, Size, 0, (struct sockaddr *)&m_clientAddr, sizeof(m_clientAddr));

}

//--------------------------------------------------
// ��M
//--------------------------------------------------
int CUdp_Client::Recv(char *recvBuffer, int Size)
{
	// �T�[�o�[����̉�������M

	int addrLen = sizeof((struct sockaddr_in)m_clientAddr);
	int receivedBytes = recvfrom(m_sock, recvBuffer, Size, 0, (struct sockaddr *)&m_clientAddr, &addrLen);

	return receivedBytes;
}

//-------------------------------
// �ʐM
//-------------------------------
bool CUdp_Client::Connect()
{
	int addr = m_clientAddr.sin_addr.S_un.S_addr;
	//sizeof()
	sendto(m_sock, (const char*)&addr, sizeof(addr), 0, (struct sockaddr *)&m_clientAddr, sizeof(m_clientAddr));
	return true;
}
