//============================
//
// �t�@�C���ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================
#ifndef _FILE_H_			// ���̃}�N����`������ĂȂ�������
#define _FILE_H_			// ��d�C���N���[�h�h�~�̃}�N����`



//=====================================
// �C���N���[�h
//=====================================
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "nlohmann/json.hpp"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <sstream>

//�\����
typedef struct
{
	//
	std::wstring main_job;
	std::wstring race;
	std::wstring unionsname;
	std::wstring name;
	int nStatus;
}Set;


using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

//=====================================
// �v���g�^�C�v�錾
//=====================================
// ����֐�
pplx::task<void> GetTest(const wchar_t* cUrl);//�ǂݍ���
std::string UTF8toSjis(std::string srcUTF8);//�ϊ�
Set *GetStatus(void);//�Q�b�g
//void SetStatus(void);

#endif

