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
// �N���X
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
	int m_desTimarMax;	// ������ő厞��
	int m_desTimar;		// �����鎞��

	int m_textSize;		// �����̃T�C�Y
	int m_addNumber;	// 1�̕��������Z�����܂ł̎���
	int m_addCount;		// ���������Z�����܂ł̃J�E���g
	int m_addLetter;	// �������ړ���邩�w��

	bool m_isRelease;

	LPD3DXFONT m_font = nullptr;

	std::string m_text;
	std::string m_allText;
};
#endif
