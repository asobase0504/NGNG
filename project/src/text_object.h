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
private:

	D3DXCOLOR col;
	int m_DesTimarMax;	//消える最大時間
	int m_DesTimar;		//消える時間

	int m_TextSize;			// 文字のサイズ
	int m_Addnumber;		// 1つの文字が加算されるまでの時間
	int m_AddCount;			// 文字が加算されるまでのカウント
	int m_AddLetter;		// 何文字目入れるか指定
	int m_wordsPopCount;	// 文字を出した最大数
	int m_wordsPopCountX;	// 横に文字を出した数
	int m_newlineCount;		// 改行の数
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
