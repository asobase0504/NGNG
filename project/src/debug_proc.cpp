//**************************************************************
//
// �f�o�b�N�\���N���X(debug_proc.cpp)
// Author : �������l
// �T�v : �f�o�b�N�\���������s��
//
//**************************************************************

//==============================================================
// �C���N���[�h
//==============================================================
#include "debug_proc.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "line.h"

//==============================================================
// �ÓI�����o�ϐ��̒�`
//==============================================================
LPD3DXFONT CDebugProc::m_font = nullptr;	// �t�H���g���
std::string CDebugProc::m_str;				// �o�^������
bool CDebugProc::m_use = false;	// �t�H���g���

//--------------------------------------------------------------
// ������̓o�^
// Author : �������l
// �T�v : �����ɐݒ肳�ꂽ�������o�^����
//--------------------------------------------------------------
void CDebugProc::Print(const char *pFormat, ...)
{
	if (!m_use)
	{
		return;
	}

	// �ϐ�
	char aStrCpy[0xfff] = {};

	// ���X�g�̍쐬
	va_list args;
	va_start(args, pFormat);
	vsprintf(&aStrCpy[0], pFormat, args);
	va_end(args);

	m_str += aStrCpy;
}

//--------------------------------------------------------------
// ������̕`��
// Author : �������l
// �T�v : �o�^���ꂽ�������`�悷��
//--------------------------------------------------------------
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	if (CInput::GetKey()->Trigger(DIK_0, -1))
	{
		CLine::m_alldisplay = !CLine::m_alldisplay;
		m_use = !m_use;
	}
	else if (CInput::GetKey()->Trigger(DIK_9, -1))
	{
		CLine::m_alldisplay = !CLine::m_alldisplay;
	}

	if (!m_use)
	{
		// �e�L�X�g�`��
		RECT rect = { 0, 0, 1280, 720 };
		m_font->DrawText(NULL, "�y 0 �z : �\��\n", -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
		return;
	}
	else
	{
		m_str = "�y 0 �z : ��\��\n" + m_str;
	}

	RECT rect = { 0, 0, 1280, 720 };

	// �e�L�X�g�`��
	m_font->DrawText(NULL, m_str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
	m_str.clear();
#endif // _DEBUG
}

//--------------------------------------------------------------
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//--------------------------------------------------------------
CDebugProc::CDebugProc()
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//--------------------------------------------------------------
CDebugProc::~CDebugProc()
{
}

//--------------------------------------------------------------
// ������
// Author : �������l
// �T�v : �����o�ϐ��̏����l��ݒ�
//--------------------------------------------------------------
void CDebugProc::Init()
{// �f�o�C�X�ւ̃|�C���^�̎擾
#ifdef _DEBUG
	m_use = true;
#endif // _DEBUG

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("HGRSGU.TTC"), &m_font);
}

//--------------------------------------------------------------
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//--------------------------------------------------------------
void CDebugProc::Uninit()
{
	if (!m_use)
	{
		return;
	}

	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_font != nullptr)
	{
		m_font->Release();
		m_font = nullptr;
	}
}