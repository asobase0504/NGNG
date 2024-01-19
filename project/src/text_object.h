//============================
//
// TEXT
// Author:hamada ryuuga
//
//============================

#ifndef _TEXT_H_
#define _TEXT_H_

#include "object2d.h"
#include "words.h"

class CText : public CObject
{
public:
	CText(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_BG);
	~CText();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	static CText* Create(D3DXVECTOR3 setPos, D3DXVECTOR3 SetSize, int DeleteTime, int SpeedText, const char * Text, CFont::FONT Type = CFont::FONT_MYOUTYOU, int wordsPopCountX = 0, bool Nottimerdelete = false);
	static CText* Create(const D3DXVECTOR2& inPos, const D3DXVECTOR2& inSize,const char * Text);
	void Releasetimer(int nTimar);
	void CText::Setfunc(std::function<void(void) > func);

	void SetCountXfast(int fast) { m_wordsPopCountXfast = fast; m_wordsPopCountX = m_wordsPopCountXfast; };
	void SetRelease(bool Nottimerdelete) { m_isRelease = Nottimerdelete; };

	void SetColor(const D3DXCOLOR &inColor) override;
private:

	D3DXCOLOR col;
	int m_DesTimarMax;	//������ő厞��
	int m_DesTimar;		//�����鎞��

	int m_TextSize;			// �����̃T�C�Y
	int m_Addnumber;		// 1�̕��������Z�����܂ł̎���
	int m_AddCount;			// ���������Z�����܂ł̃J�E���g
	int m_AddLetter;		// �������ړ���邩�w��
	int m_wordsPopCount;	// �������o�����ő吔
	int m_wordsPopCountX;	// ���ɕ������o������
	int m_newlineCount;		// ���s�̐�
	int m_wordsPopCountXfast;
	bool m_isRelease;

	std::string m_Text;
	std::string m_ALLText;
	CFont::FONT m_FontType;
	std::vector<CWords*> m_words;
	std::function<void(void)> m_func;
	void TextLetter(const char * Text, int SpeedText);
	void SetFont(CFont::FONT FontType) { m_FontType = FontType; };
};
#endif
