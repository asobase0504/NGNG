//**************************************************
// 
// �t�H���g
// Author  : HamadaRyuuga
// Author  : Yuda Kaito
// 
//**************************************************
#ifndef _FONT_H_	//���̃}�N����`������ĂȂ�������
#define _FONT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// ��`
//==================================================
class CFont
{
public: /* ��` */
	enum FONT
	{
		FONT_MYOUTYOU = 0,
		FONT_SOUEIKAKU,
		FONT_MAX,
		FONT_NONE,	// �g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

	static const char* s_FontName[];	// �t�@�C���p�X
public:
	CFont();		// �f�t�H���g�R���X�g���N�^
	~CFont();	// �f�X�g���N�^

public: /* �����o�֐� */
	static void Load(FONT inTexture);		// �w��̓ǂݍ���
	static void ReleaseAll();				// �S�Ă̔j��
	static void Release(FONT inTexture);	// �w��̔j��
	static LPDIRECT3DTEXTURE9 GetFont(std::string words,FONT inTexture);	// ���̎擾

private: /* �����o�֐� */
	static void LoadWords(std::string inWords, FONT inTexture);
private: /* �����o�ϐ� */

	static std::array<HFONT, FONT_MAX>  m_hFont;
	static std::array<LOGFONT, FONT_MAX> m_lf;
	static std::array<LPDIRECT3DTEXTURE9, FONT_MAX> m_texFont;	// �e�N�X�`���̏��
};

#endif // !_FONT_H_

