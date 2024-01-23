//============================
//
// �e�L�X�g�\������ׂ��
// Author:hamada ryuuga
//
//============================

#include "text_object.h"
#include "renderer.h"
#include "utility.h"
#include "input.h"
#include <Shlwapi.h>

//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CText::CText() : CObject(CTaskGroup::LEVEL_2D_UI)
{
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CText::~CText()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CText::Init()
{
	CObject::Init();
	m_newlineCount = 0;
	m_wordsPopCount = 0;
	m_wordsPopCountX = 0;
	m_AddCount = 0;
	m_Text = "";

	m_isRelease = false;
	m_DesTimar = 0;
	m_func = nullptr;

	return S_OK;
}

//=============================================================================
// �j���֐�
//=============================================================================
void CText::Uninit()
{
	for (int wordsCount = 0; wordsCount < m_TextSize; wordsCount++)
	{
		if (m_words[wordsCount] != nullptr)
		{
			m_words[wordsCount]->Uninit();
		}
	}
	CObject::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CText::Update()
{
	CObject::Update();

	D3DXVECTOR3 Pos= GetPos();
	m_AddCount++;
	if (m_AddCount >= m_Addnumber)
	{
		if (m_AddLetter < m_TextSize)
		{
			m_Text += m_ALLText[m_AddLetter];
			std::string txt = m_Text;
			if (txt != "")
			{//�󔒃`�F�b�N
				if (IsSjisLeadByte(m_ALLText[m_AddLetter]) && m_AddLetter < m_TextSize)
				{
					//�������ꕶ�������
					m_AddLetter++;
					m_Text += m_ALLText[m_AddLetter];
					m_AddLetter++;
					m_words[m_wordsPopCount] = CWords::Create(m_Text.c_str(),
						D3DXVECTOR3(Pos.x + (m_size.x * 2.15f * (m_wordsPopCountX + 1)), Pos.y + m_newlineCount * m_size.y * 2.15f, Pos.z),
						m_size,
						m_FontType);
					m_wordsPopCount++;
					m_wordsPopCountX++;
				}
				else
				{
					if (m_Text != "\n")
					{	//����Ȃ������Ƃ�
						m_AddLetter++;
						m_words[m_wordsPopCount] = CWords::Create(m_Text.c_str(),
							D3DXVECTOR3(Pos.x + m_size.x * 2.15f * (m_wordsPopCountX + 1), Pos.y + m_newlineCount * 100.0f, Pos.z),
							m_size * 0.75f,	// ���p�������������������B�l�͓K��
							m_FontType);
						m_wordsPopCount++;
						m_wordsPopCountX++;
					}
					else
					{//���s�R�[�h�������Ƃ�
						m_wordsPopCountX = m_wordsPopCountXfast;
						m_AddLetter++;
						m_newlineCount++;
					}
				}

			}
		}
		m_Text = "";
		m_AddCount = 0;
	}

	if (m_isRelease)
	{
		//������ݒ�
		m_DesTimar--;

		if (m_DesTimar <= 0)
		{
			if (m_func != nullptr)
			{
				m_func();
			}
			Uninit();
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CText *CText::Create(D3DXVECTOR3 SetPos, D3DXVECTOR3 SetSize, int DeleteTime, int SpeedText, const char * Text, CFont::FONT Type, int wordsPopCountX, bool Nottimerdelete)
{
	CText * pObject = nullptr;
	pObject = new CText();

	if (pObject != nullptr)
	{
		pObject->SetCountXfast(wordsPopCountX);
		pObject->Init();

		pObject->SetPos(SetPos);
		pObject->SetSize(SetSize);
		pObject->SetFont(Type);
		pObject->Releasetimer(DeleteTime);
		pObject->TextLetter(Text, SpeedText);

		pObject->SetRelease(Nottimerdelete);
	}

	return pObject;
}

CText * CText::Create(const D3DXVECTOR2 & inPos, const D3DXVECTOR2 & inSize, const char * Text)
{
	return Create(D3DXVECTOR3(inPos.x, inPos.y,0.0f), D3DXVECTOR3(inSize.x, inSize.y, 0.0f),0,0,Text);

}


//=============================================================================
// �����܂ł̎��Ԑݒ�֐�
//=============================================================================
void CText::Releasetimer(int nTimar)
{
	m_DesTimar = nTimar;
	m_DesTimarMax = m_DesTimar;
	m_isRelease = true;
}

//=============================================================================
// �����܂ł̎��Ԑݒ�֐�
//=============================================================================
void CText::TextLetter(const char * Text, int SpeedText)
{
	m_ALLText = Text;
	m_TextSize = m_ALLText.size();
	m_Addnumber = SpeedText;
	m_AddLetter = 0;
	m_words.resize(m_TextSize);
}

//=============================================================================
// ���ł��鎞�̃C�x���g�ݒ�
//=============================================================================
void CText::Setfunc(std::function<void(void)> func)
{
	m_func = func;
}

void CText::SetColor(const D3DXCOLOR & inColor)
{
	CObject::SetColor(inColor);
	for (CWords* words : m_words)
	{
		if (words == nullptr)
		{
			continue;
		}

		words->SetColor(inColor);
	}
}
