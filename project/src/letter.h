//**************************************************************
//
// ����ݒ�
// Author:hamada ryuuga
//
//**************************************************************
#ifndef _LETTER_H_			// ���̃}�N����`������ĂȂ�������
#define _LETTER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//--------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------
std::string WStringToString(std::wstring oWString);
std::wstring StringToWString(std::string oString);
std::string UTF8toSjis(std::string srcUTF8);
std::string SjistoUTF8(std::string srcSjis);

#endif