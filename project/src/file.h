//**************************************************************
//
// �t�@�C��
// Author : Hamada Ryuuga
//
//**************************************************************
#ifndef _FILE_H_			// ���̃}�N����`������ĂȂ�������
#define _FILE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// �������ϐ��̌^
//==============================================================
enum Type {
	UseChack,	// �z��
	Vector3,	// D3DXVECTOR3�^
	SColor,		// D3DXCOLOR�^
	Float,		// float�^
	Int,		// int�^
	Bool		// bool�^
};

//==============================================================
// ������ɕK�v�ȏ��
//==============================================================
struct ConvTable {
	Type type;			// ����`��
	const char *name;	// Key
	void *store;		// ����������l
};

//==============================================================
// �������l�𕡐��ɑΉ�����B
//==============================================================
struct DeepTable {
	std::vector<ConvTable> table;
	bool* use;
};

//--------------------------------------------------------------
// �v���g�^�C�v�錾
//--------------------------------------------------------------
nlohmann::json LoadJson(const wchar_t* cUrl);
nlohmann::json LoadJson(const char* cUrl);
nlohmann::json LoadJson(std::string cUrl);
void SaveJson(nlohmann::json inJson, const std::string cUrl);
void LoadValueBundledData(nlohmann::json*, DeepTable&);

#endif		// _FILE_H_
