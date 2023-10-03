//**************************************************************
//
// TEXT
// Author:hamada ryuuga
//
//**************************************************************
#ifndef _TEXT_H_
#define _TEXT_H_

//==============================================================
// include
//==============================================================
#include "object2d.h"

//==============================================================
// クラス
//==============================================================
class CText : public CObject2d
{
public:

	enum Type
	{
		GON = 0,
		MASUO,
		MAX
	};

	CText(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_UI);
	~CText();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CText* Create(Type talkType, int DeleteTime, int SpeedText, const char * Text);

	void ReleaseTimer(int nTimar);
private:
	void TextLetter(const char* Text, int SpeedText);

private:
	D3DXCOLOR  m_col;
	int m_desTimarMax;	// 消える最大時間
	int m_desTimar;		// 消える時間

	int m_textSize;		// 文字のサイズ
	int m_addNumber;	// 1つの文字が加算されるまでの時間
	int m_addCount;		// 文字が加算されるまでのカウント
	int m_addLetter;	// 何文字目入れるか指定

	bool m_isRelease;

	LPD3DXFONT m_font = nullptr;

	std::string m_text;
	std::string m_allText;
};
#endif
