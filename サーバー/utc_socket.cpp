//**************************************************
// �w�b�_�[���C���N���[�h
//**************************************************
#include "utc_socket.h"
#include "protocol.h"
#include "model.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CUtc_Socket::CUtc_Socket()
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CUtc_Socket::~CUtc_Socket()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CUtc_Socket::Init()
{
	// ���X�g�̃T�C�Y�ƓG�̃T�C�Y��������
	m_listSize = 0;
	m_EnemySize = 0;

	// Winsock��������
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		perror("WSAStartup�Ɏ��s���܂���");

	}

	// �\�P�b�g���쐬
	m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_sockfd == -1) {
		perror("�\�P�b�g�̍쐬�Ɏ��s���܂���");

	}

	// �����ŁA�m���u���b�L���O�ɐݒ肵�Ă��܂��B
	u_long val = 1;
	ioctlsocket(m_sockfd, FIONBIO, &val);

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(50008); // �҂��󂯃|�[�g�ԍ�
	m_serverAddr.sin_addr.s_addr = INADDR_ANY;

	// �\�P�b�g���o�C���h
	if (bind(m_sockfd, (struct sockaddr *)&m_serverAddr, sizeof(m_serverAddr)) == -1) {
		perror("�o�C���h�Ɏ��s���܂���");
		closesocket(m_sockfd);
		WSACleanup();
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CUtc_Socket::Uninit()
{
	closesocket(m_sockfd);
	WSACleanup();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CUtc_Socket::Update()
{
	char recvBuffer[1024];
	char sendBuffer[1024];

	while (1)
	{
		std::string List;
		int m_clientAddrLen = sizeof(m_clientAddr);

		// �N���C�A���g����̃f�[�^����M
		int bytesReceived = recvfrom(m_sockfd, recvBuffer, sizeof(recvBuffer), 0, (struct sockaddr *)&m_clientAddr, &m_clientAddrLen);
		if (bytesReceived != -1)
		{

			if (bytesReceived >= 0)
			{
				recvBuffer[bytesReceived] = '\0';
			}

			printf("�N���C�A���g���烁�b�Z�[�W����M���܂����F%s:%d�F%s\n", inet_ntoa(m_clientAddr.sin_addr), ntohs(m_clientAddr.sin_port), recvBuffer);
			List = SetComand(recvBuffer, ntohs(m_clientAddr.sin_port));

			if (List.size() != 0)
			{
				// ��M�����f�[�^�ɉ���
				//strcpy(sendBuffer, "�A���Ă������I");
				sendto(m_sockfd, List.c_str(), List.size(), 0, (struct sockaddr *)&m_clientAddr, sizeof(m_clientAddr));
			}

			for (int i = 0; i < m_Enemy.size(); i++)
			{

				m_Enemy[i]->Update();
			}
		}

	}
}

//--------------------------------------------------
// �R�}���h��ݒ�
//--------------------------------------------------
std::string CUtc_Socket::SetComand(char *recvBuffer, int Id)
{
	std::string List;
	int data = (int)recvBuffer[0];
	data -= 48;
	COMMAND_TYPE command = (COMMAND_TYPE)data;

	int MyId = Id;

	switch (command)
	{
	case COMMAND_TYPE_NONE:
		std::cout << "�R�}���h�Ȃ�" << Id << std::endl;
		break;

	case COMMAND_TYPE_MOVEID:
		std::cout << "ID�ɂ��ړ�" << std::endl;
		List = _Moveid(recvBuffer, Id);
		std::cout << "�ݒ芮��" << std::endl;
		break;

	case COMMAND_TYPE_MOVE:
		std::cout << "�ړ��R�}���h" << std::endl;
		List = _Move(recvBuffer, Id);
		break;

	case COMMAND_TYPE_GET:
		std::cout << "�擾�R�}���h" << std::endl;
		List = _GetIs(recvBuffer, Id);
		break;

	case COMMAND_TYPE_POPENEMY:
		std::cout << "�G�̏o���R�}���h" << std::endl;
		List = _PopIs(recvBuffer, Id);
		break;

	case COMMAND_TYPE_GETENEMY:
		std::cout << "�G�̏��擾�R�}���h" << std::endl;
		List = _GetEnemy(recvBuffer, Id);
		break;
	case COMMAND_TYPE_SETMOVE:
		std::cout << "�G�̈ړ��ݒ�R�}���h" << std::endl;
		List = _MoveEnemy(recvBuffer, Id);
		break;
	default:
		std::cout << "�s���ȃR�}���h" << std::endl;
		break;
	}
	return List;
}

//--------------------------------------------------
// D3DXVECTOR3��char�ɕϊ�����֐�
//--------------------------------------------------
std::string CUtc_Socket::ConvertD3DXVECTOR3ToChar(const D3DXVECTOR3& vector)
{
	char aSendData[256] = {};

	float DataX = vector.x;
	float DataY = vector.y;
	float DataZ = vector.z;

	ConvertFloatToNetworkOrder(DataX);
	ConvertFloatToNetworkOrder(DataY);
	ConvertFloatToNetworkOrder(DataZ);

	// aSendData�Ƀf�[�^���i�[
	memcpy(aSendData, &DataX, sizeof(float));
	memcpy(aSendData + sizeof(float), &DataY, sizeof(float));
	memcpy(aSendData + 2 * sizeof(float), &DataZ, sizeof(float));

	// ������ɕϊ�
	std::string stream(aSendData, sizeof(float) * 3);

	return stream; // ������ɕϊ������f�[�^��Ԃ�
}

//--------------------------------------------------
// ���������_���̃o�C�g�I�[�_�[��ϊ�����֐�
//--------------------------------------------------
void CUtc_Socket::ConvertFloatToNetworkOrder(float& value)
{
	// ���������_�����o�C�g��ɕϊ�
	uint32_t networkOrder;
	memcpy(&networkOrder, &value, sizeof(float));

	// �o�C�g�I�[�_�[��ϊ�
	networkOrder = htonl(networkOrder);

	// �o�C�g��𕂓������_���ɖ߂�
	memcpy(&value, &networkOrder, sizeof(float));
}

//--------------------------------------------------
// �o�C�g�I�[�_�[���z�X�g�I�[�_�[��
//--------------------------------------------------
float CUtc_Socket::ConvertFloatToHostOrder(float& value)
{
	float List = value;
	uint32_t hostOrder;
	memcpy(&hostOrder, &List, sizeof(float));
	hostOrder = ntohl(hostOrder);
	memcpy(&List, &hostOrder, sizeof(float));
	return List;
}
//--------------------------------------------------
// ���M
//--------------------------------------------------
void CUtc_Socket::Send(char *recvBuffer)
{

}

//--------------------------------------------------
// ��M
//--------------------------------------------------
int CUtc_Socket::Recv(char *recvBuffer, int Size)
{
	// �T�[�o�[����̉�������M
	int receivedBytes = recvfrom(m_sockfd, recvBuffer, Size, 0, NULL, NULL);
	return receivedBytes;
}

//--------------------------------------------------
// Move�ݒ�
//--------------------------------------------------
std::string CUtc_Socket::_Move(char *recvBuffer, int id)
{
	std::string List;
	int MyBox;
	bool Ischeck = false;
	// COMMAND_TYPE_MOVE�ɑ΂���A�N�V���������s
	for (int i = 0; i < m_listSize; i++)
	{
		if (id == m_model[i]->GetId())
		{
			MyBox = i;
			Ischeck = true;
		}
	}

	if (!Ischeck)
	{
		return std::string("m_model�f�[�^�Ȃ���", 0);
	}

	if (m_model[MyBox] != nullptr)
	{
		int Ker = (int)recvBuffer[1];
		Ker -= 48;
		MOVE_TYPE moveKer = (MOVE_TYPE)Ker;

		if (Ker == (MOVE_TYPE)MOVE_TYPE_SETMODEL)
		{
			char recvBufferPos[1024] = {};
			D3DXVECTOR3 receivedVector;
			D3DXVECTOR3 receivedVectorRot;
			int receivedBytes = Recv(recvBufferPos, sizeof(recvBufferPos));

			if (receivedBytes < 0)
			{
				perror("recvfrom failed");
				// �G���[�n���h�����O��ǉ����邩�A�v���O�������I������Ȃǂ̏������s�����Ƃ��d�v�ł��B
			}

			if (receivedBytes == 12+12+1)
			{//�����̐��Ⴄ������������̃��b�N

				// ��M�����������D3DXVECTOR3�ɕϊ����A�ϐ��Ɋi�[
				std::string receivedData(recvBufferPos, receivedBytes);


				std::string receivedPos(receivedData.begin(), receivedData.begin() + 12);
				std::string receivedRot(receivedData.begin() + 12, receivedData.begin() + 24);

				int motion;

				
				motion = (int) recvBufferPos[24];
			
				receivedVector = ConvertCharToD3DXVECTOR3(receivedPos);
				receivedVectorRot = ConvertCharToD3DXVECTOR3(receivedRot);
				m_model[MyBox]->SetSeve(receivedVector);
				m_model[MyBox]->SetRot(receivedVectorRot);
				m_model[MyBox]->SetMotion(motion);
				printf("�ʒu:X = %f, Y = %f, Z = %f\n", receivedVector.x, receivedVector.y, receivedVector.z);
				printf("��]:X = %f, Y = %f, Z = %f\n", receivedVectorRot.x, receivedVectorRot.y, receivedVectorRot.z);
				printf("motion:%d\n", motion);
			}
		}
		else
		{
			int Pow = (int)recvBuffer[2];
			Pow -= 48;
			D3DXVECTOR3 Pos = m_model[MyBox]->SetKer(moveKer);
			List = ConvertD3DXVECTOR3ToChar(Pos);
		}
	}
	else
	{
		// ���f�������݂��Ȃ��ꍇ�̏���
	}
	return List;
}

//--------------------------------------------------
// ID�̐ݒ�
//--------------------------------------------------
std::string CUtc_Socket::_Moveid(char *recvBuffer, int id)
{
	std::string List;
	bool IsOk = false;
	int MyBox;

	// ����ID�̃��f�������݂��Ȃ����m�F
	for (int i = 0; i < m_listSize; i++)
	{
		if (id == m_model[i]->GetId())
		{
			IsOk = true;
		}
	}

	if (!IsOk)
	{
		// COMMAND_TYPE_MOVEID�ɑ΂���A�N�V���������s
		m_model.push_back(new CModel);
		m_model[m_listSize]->Init();
		m_model[m_listSize]->SetId(id);
		List = (char)m_listSize;
		m_listSize++;
	}
	return List;
}

//--------------------------------------------------
// ID�̎擾
//--------------------------------------------------
std::string CUtc_Socket::_GetIs(char *recvBuffer, int id)
{
	std::string List;
	int MyBox;
	int setCount = 0;
	int count = (int)recvBuffer[1];
	bool IsOk = false;
	count -= 48;

	// �ő吔�̐���
	// COMMAND_TYPE_MOVE�ɑ΂���A�N�V���������s
	for (int i = 0; i < m_listSize; i++)
	{
		if (id != m_model[i]->GetId())
		{//ID��count�̐��T��
			if (count == setCount)
			{
				MyBox = i;
				IsOk = true;
			}
			setCount++;
		}
	}

	if (!IsOk)
	{
		// �m��
		List = "NOID";
		return List;
	}

	if (m_model[MyBox] != nullptr)
	{
		D3DXVECTOR3 Pos = m_model[MyBox]->GetPos();
		D3DXVECTOR3 Rot = m_model[MyBox]->GetRot();
		int Motion = m_model[MyBox]->GetMotion();
		List += ConvertD3DXVECTOR3ToChar(Pos);
		List += ConvertD3DXVECTOR3ToChar(Rot);
		List += Motion;
	}
	else
	{
		// ���f�������݂��Ȃ��ꍇ�̏���
	}
	return List;
}

//--------------------------------------------------
// �G�̍��W�����˂�����
//--------------------------------------------------
std::string CUtc_Socket::_PopIs(char *recvBuffer, int id)
{
	std::string List;

	// COMMAND_TYPE_MOVEID�ɑ΂���A�N�V���������s
	m_Enemy.push_back(new CModel);
	m_Enemy[m_EnemySize]->Init();
	m_Enemy[m_EnemySize]->SetId(id);

	char recvBufferPos[1024] = {};
	D3DXVECTOR3 receivedVector;

	// �T�[�o�[����̉�������M
	// int receivedBytes = recvfrom(m_sockfd, recvBufferPos, sizeof(recvBufferPos), 0, NULL, NULL);
	int receivedBytes = Recv(recvBufferPos, sizeof(recvBufferPos));

	if (receivedBytes < 0)
	{
		perror("recvfrom failed");
		// �G���[�n���h�����O��ǉ����邩�A�v���O�������I������Ȃǂ̏������s�����Ƃ��d�v�ł��B
	}

	// ��M�����������D3DXVECTOR3�ɕϊ����A�ϐ��Ɋi�[
	std::string receivedData(recvBufferPos, receivedBytes);
	receivedVector = ConvertCharToD3DXVECTOR3(receivedData);
	m_Enemy[m_EnemySize]->SetSeve(receivedVector);
	printf("�ʒu:X = %f, Y = %f, Z = %f\n", receivedVector.x, receivedVector.y, receivedVector.z);

	m_EnemySize++;

	return List;
}

//--------------------------------------------------
// �G�̍��W�����擾����
//--------------------------------------------------
std::string CUtc_Socket::_GetEnemy(char *recvBuffer, int id)
{
	std::string List;
	List += m_EnemySize;
	for (int i = 0; i < m_EnemySize; i++)
	{
		D3DXVECTOR3 Pos = m_Enemy[i]->GetPos();
		List += ConvertD3DXVECTOR3ToChar(Pos);
	}

	sendto(m_sockfd, List.c_str(), List.size(), 0, (struct sockaddr *)&m_clientAddr, sizeof(m_clientAddr));
	return std::string(List);
}

//--------------------------------------------------
// �G�̈ړ��|�C���g�𑗂�
//--------------------------------------------------
std::string CUtc_Socket::_MoveEnemy(char * recvBuffer, int id)
{
	char recvBufferPos[1024] = {};
	char recvBufferNum[1024] = {};
	D3DXVECTOR3 receivedVector;
	int receivedBytes = Recv(recvBufferNum, sizeof(recvBufferNum));

	if (receivedBytes < 0)
	{
		perror("recvfrom failed");
		// �G���[�n���h�����O��ǉ����邩�A�v���O�������I������Ȃǂ̏������s�����Ƃ��d�v�ł��B
	}
	receivedBytes = Recv(recvBufferPos, sizeof(recvBufferPos));

	if (receivedBytes < 0)
	{
		perror("recvfrom failed");
		// �G���[�n���h�����O��ǉ����邩�A�v���O�������I������Ȃǂ̏������s�����Ƃ��d�v�ł��B
	}
	int Size = (int)recvBufferNum[0];
	// ��M�����������D3DXVECTOR3�ɕϊ����A�ϐ��Ɋi�[
	std::string receivedData(recvBufferPos, receivedBytes);

	receivedVector = ConvertCharToD3DXVECTOR3(receivedData);

	
	m_Enemy[Size]->SetPosLocate(receivedVector);
	printf("�ʒu:X = %f, Y = %f, Z = %f\n", receivedVector.x, receivedVector.y, receivedVector.z);

	return std::string();
}

//--------------------------------------------------
// �G�̍��W�����擾����
//--------------------------------------------------
D3DXVECTOR3 CUtc_Socket::ConvertCharToD3DXVECTOR3(const std::string& data)
{
	if (data.size() != sizeof(float) * 3)
	{
		// �K�؂ȃT�C�Y�̃f�[�^���K�v�ȏꍇ�̃G���[�n���h�����O
		// �����œK�؂ȃG���[�������s�����A��O�𓊂���Ȃǂ̏�����ǉ����Ă��������B
		// throw std::runtime_error("�����ȃf�[�^�T�C�Y");
		printf("�T�[�o�[����̉����F�T�C�Y�s��\n");
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	float LogX, LogY, LogZ;
	std::istringstream stream(data);

	float PosData[3];
	for (int i = 0; i < 3; i++)
	{
		char TestaRecvData[4];

		memcpy(&TestaRecvData[0], &data[(i * 4)], sizeof(float));

		PosData[i] = ConvertFloatToHostOrder(*(float*)&TestaRecvData[0]);
	}

	return D3DXVECTOR3(PosData[0], PosData[1], PosData[2]);
}
