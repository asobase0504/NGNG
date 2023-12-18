//**************************************************
// �w�b�_�[���C���N���[�h
//**************************************************
#include "udp_client.h"

#include <sys/types.h>
#include "udp_listener.h"
#include <cerrno>  // errno �w�b�_���C���N���[�h
#include <cstring> // strerror �֐����g�p���邽�߂ɕK�v
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CUdp_Listner::CUdp_Listner()
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CUdp_Listner::~CUdp_Listner()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
bool CUdp_Listner::Init(const char*plPAddress, int nPortNum)
{

	m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (m_sockfd == INVALID_SOCKET)
	{
		printf("�uUDP�vsocket�@error");
		return false;
	}

	printf("�uUDP�v�������J�n����\n");

	m_nPortNum = nPortNum;   

	memset(&m_serverAddr, 0, sizeof(m_serverAddr));

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(nPortNum);//�|�[�g
	m_serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;//IP


	//bind(m_sockfd, (struct sockaddr*)&m_serverAddr, sizeof(m_serverAddr));

	if (bind(m_sockfd, reinterpret_cast<struct sockaddr*>(&m_serverAddr), sizeof(m_serverAddr)) == -1)
	{
		std::cerr << "Error binding socket." << std::endl;
		closesocket(m_sockfd);
		return false;
	}
	
	return true;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CUdp_Listner::Uninit()
{
	closesocket(m_sockfd);
	WSACleanup();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CUdp_Listner::UpData()
{

}

CUdp_Client * CUdp_Listner::Accept()
{
	char buf[100]; // ��M�o�b�t�@

	// ��M�o�b�t�@�̏�����
	memset(buf, 0, sizeof(buf));

	CUdp_Client*pUdp_Socket;
	pUdp_Socket = new CUdp_Client;
	int Size = sizeof(m_serverAddr);
	pUdp_Socket->Init(m_sockfd);
	pUdp_Socket->SetAddr(m_serverAddr);
	int list = pUdp_Socket->Recv(&buf[0], 4);
	//int size = recvfrom(m_sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&m_serverAddr, &Size);




	return pUdp_Socket;
}
