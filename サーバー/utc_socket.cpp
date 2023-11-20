//**************************************************
// ヘッダーをインクルード
//**************************************************
#include "utc_socket.h"
#include "protocol.h"
#include "model.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CUtc_Socket::CUtc_Socket()
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CUtc_Socket::~CUtc_Socket()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CUtc_Socket::Init()
{
	// リストのサイズと敵のサイズを初期化
	m_listSize = 0;
	m_EnemySize = 0;

	// Winsockを初期化
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		perror("WSAStartupに失敗しました");

	}

	// ソケットを作成
	m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_sockfd == -1) {
		perror("ソケットの作成に失敗しました");

	}

	// ここで、ノンブロッキングに設定しています。
	u_long val = 1;
	ioctlsocket(m_sockfd, FIONBIO, &val);

	m_serverAddr.sin_family = AF_INET;
	m_serverAddr.sin_port = htons(50008); // 待ち受けポート番号
	m_serverAddr.sin_addr.s_addr = INADDR_ANY;

	// ソケットをバインド
	if (bind(m_sockfd, (struct sockaddr *)&m_serverAddr, sizeof(m_serverAddr)) == -1) {
		perror("バインドに失敗しました");
		closesocket(m_sockfd);
		WSACleanup();
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CUtc_Socket::Uninit()
{
	closesocket(m_sockfd);
	WSACleanup();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CUtc_Socket::Update()
{
	char recvBuffer[1024];
	char sendBuffer[1024];

	while (1)
	{
		std::string List;
		int m_clientAddrLen = sizeof(m_clientAddr);

		// クライアントからのデータを受信
		int bytesReceived = recvfrom(m_sockfd, recvBuffer, sizeof(recvBuffer), 0, (struct sockaddr *)&m_clientAddr, &m_clientAddrLen);
		if (bytesReceived != -1)
		{

			if (bytesReceived >= 0)
			{
				recvBuffer[bytesReceived] = '\0';
			}

			printf("クライアントからメッセージを受信しました：%s:%d：%s\n", inet_ntoa(m_clientAddr.sin_addr), ntohs(m_clientAddr.sin_port), recvBuffer);
			List = SetComand(recvBuffer, ntohs(m_clientAddr.sin_port));

			if (List.size() != 0)
			{
				// 受信したデータに応答
				//strcpy(sendBuffer, "帰ってきたぞ！");
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
// コマンドを設定
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
		std::cout << "コマンドなし" << Id << std::endl;
		break;

	case COMMAND_TYPE_MOVEID:
		std::cout << "IDによる移動" << std::endl;
		List = _Moveid(recvBuffer, Id);
		std::cout << "設定完了" << std::endl;
		break;

	case COMMAND_TYPE_MOVE:
		std::cout << "移動コマンド" << std::endl;
		List = _Move(recvBuffer, Id);
		break;

	case COMMAND_TYPE_GET:
		std::cout << "取得コマンド" << std::endl;
		List = _GetIs(recvBuffer, Id);
		break;

	case COMMAND_TYPE_POPENEMY:
		std::cout << "敵の出現コマンド" << std::endl;
		List = _PopIs(recvBuffer, Id);
		break;

	case COMMAND_TYPE_GETENEMY:
		std::cout << "敵の情報取得コマンド" << std::endl;
		List = _GetEnemy(recvBuffer, Id);
		break;
	case COMMAND_TYPE_SETMOVE:
		std::cout << "敵の移動設定コマンド" << std::endl;
		List = _MoveEnemy(recvBuffer, Id);
		break;
	default:
		std::cout << "不明なコマンド" << std::endl;
		break;
	}
	return List;
}

//--------------------------------------------------
// D3DXVECTOR3をcharに変換する関数
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

	// aSendDataにデータを格納
	memcpy(aSendData, &DataX, sizeof(float));
	memcpy(aSendData + sizeof(float), &DataY, sizeof(float));
	memcpy(aSendData + 2 * sizeof(float), &DataZ, sizeof(float));

	// 文字列に変換
	std::string stream(aSendData, sizeof(float) * 3);

	return stream; // 文字列に変換したデータを返す
}

//--------------------------------------------------
// 浮動小数点数のバイトオーダーを変換する関数
//--------------------------------------------------
void CUtc_Socket::ConvertFloatToNetworkOrder(float& value)
{
	// 浮動小数点数をバイト列に変換
	uint32_t networkOrder;
	memcpy(&networkOrder, &value, sizeof(float));

	// バイトオーダーを変換
	networkOrder = htonl(networkOrder);

	// バイト列を浮動小数点数に戻す
	memcpy(&value, &networkOrder, sizeof(float));
}

//--------------------------------------------------
// バイトオーダーをホストオーダーに
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
// 送信
//--------------------------------------------------
void CUtc_Socket::Send(char *recvBuffer)
{

}

//--------------------------------------------------
// 受信
//--------------------------------------------------
int CUtc_Socket::Recv(char *recvBuffer, int Size)
{
	// サーバーからの応答を受信
	int receivedBytes = recvfrom(m_sockfd, recvBuffer, Size, 0, NULL, NULL);
	return receivedBytes;
}

//--------------------------------------------------
// Move設定
//--------------------------------------------------
std::string CUtc_Socket::_Move(char *recvBuffer, int id)
{
	std::string List;
	int MyBox;
	bool Ischeck = false;
	// COMMAND_TYPE_MOVEに対するアクションを実行
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
		return std::string("m_modelデータないよ", 0);
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
				// エラーハンドリングを追加するか、プログラムを終了するなどの処理を行うことが重要です。
			}

			if (receivedBytes == 12+12+1)
			{//文字の数違うやつが入った時のロック

				// 受信した文字列をD3DXVECTOR3に変換し、変数に格納
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
				printf("位置:X = %f, Y = %f, Z = %f\n", receivedVector.x, receivedVector.y, receivedVector.z);
				printf("回転:X = %f, Y = %f, Z = %f\n", receivedVectorRot.x, receivedVectorRot.y, receivedVectorRot.z);
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
		// モデルが存在しない場合の処理
	}
	return List;
}

//--------------------------------------------------
// IDの設定
//--------------------------------------------------
std::string CUtc_Socket::_Moveid(char *recvBuffer, int id)
{
	std::string List;
	bool IsOk = false;
	int MyBox;

	// 同じIDのモデルが存在しないか確認
	for (int i = 0; i < m_listSize; i++)
	{
		if (id == m_model[i]->GetId())
		{
			IsOk = true;
		}
	}

	if (!IsOk)
	{
		// COMMAND_TYPE_MOVEIDに対するアクションを実行
		m_model.push_back(new CModel);
		m_model[m_listSize]->Init();
		m_model[m_listSize]->SetId(id);
		List = (char)m_listSize;
		m_listSize++;
	}
	return List;
}

//--------------------------------------------------
// IDの取得
//--------------------------------------------------
std::string CUtc_Socket::_GetIs(char *recvBuffer, int id)
{
	std::string List;
	int MyBox;
	int setCount = 0;
	int count = (int)recvBuffer[1];
	bool IsOk = false;
	count -= 48;

	// 最大数の制限
	// COMMAND_TYPE_MOVEに対するアクションを実行
	for (int i = 0; i < m_listSize; i++)
	{
		if (id != m_model[i]->GetId())
		{//IDとcountの数探す
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
		// 確定
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
		// モデルが存在しない場合の処理
	}
	return List;
}

//--------------------------------------------------
// 敵の座標情報をねじ込む
//--------------------------------------------------
std::string CUtc_Socket::_PopIs(char *recvBuffer, int id)
{
	std::string List;

	// COMMAND_TYPE_MOVEIDに対するアクションを実行
	m_Enemy.push_back(new CModel);
	m_Enemy[m_EnemySize]->Init();
	m_Enemy[m_EnemySize]->SetId(id);

	char recvBufferPos[1024] = {};
	D3DXVECTOR3 receivedVector;

	// サーバーからの応答を受信
	// int receivedBytes = recvfrom(m_sockfd, recvBufferPos, sizeof(recvBufferPos), 0, NULL, NULL);
	int receivedBytes = Recv(recvBufferPos, sizeof(recvBufferPos));

	if (receivedBytes < 0)
	{
		perror("recvfrom failed");
		// エラーハンドリングを追加するか、プログラムを終了するなどの処理を行うことが重要です。
	}

	// 受信した文字列をD3DXVECTOR3に変換し、変数に格納
	std::string receivedData(recvBufferPos, receivedBytes);
	receivedVector = ConvertCharToD3DXVECTOR3(receivedData);
	m_Enemy[m_EnemySize]->SetSeve(receivedVector);
	printf("位置:X = %f, Y = %f, Z = %f\n", receivedVector.x, receivedVector.y, receivedVector.z);

	m_EnemySize++;

	return List;
}

//--------------------------------------------------
// 敵の座標情報を取得する
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
// 敵の移動ポイントを送る
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
		// エラーハンドリングを追加するか、プログラムを終了するなどの処理を行うことが重要です。
	}
	receivedBytes = Recv(recvBufferPos, sizeof(recvBufferPos));

	if (receivedBytes < 0)
	{
		perror("recvfrom failed");
		// エラーハンドリングを追加するか、プログラムを終了するなどの処理を行うことが重要です。
	}
	int Size = (int)recvBufferNum[0];
	// 受信した文字列をD3DXVECTOR3に変換し、変数に格納
	std::string receivedData(recvBufferPos, receivedBytes);

	receivedVector = ConvertCharToD3DXVECTOR3(receivedData);

	
	m_Enemy[Size]->SetPosLocate(receivedVector);
	printf("位置:X = %f, Y = %f, Z = %f\n", receivedVector.x, receivedVector.y, receivedVector.z);

	return std::string();
}

//--------------------------------------------------
// 敵の座標情報を取得する
//--------------------------------------------------
D3DXVECTOR3 CUtc_Socket::ConvertCharToD3DXVECTOR3(const std::string& data)
{
	if (data.size() != sizeof(float) * 3)
	{
		// 適切なサイズのデータが必要な場合のエラーハンドリング
		// ここで適切なエラー処理を行うか、例外を投げるなどの処理を追加してください。
		// throw std::runtime_error("無効なデータサイズ");
		printf("サーバーからの応答：サイズ不足\n");
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
