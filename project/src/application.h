//**************************************************************
//
// �}�l�W���[
// Author : �l�c����
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _MANEAGER_H_			// ���̃}�N����`������ĂȂ�������
#define _MANEAGER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "renderer.h"

//==============================================================
// �O���錾
//==============================================================
class CRenderer;
class CInput;
class CTexture;
class CMode;
class CFade;
class CSound;
class CTaskGroup;
class CObjectXGroup;
class CColor;

//==============================================================
// �}�l�W���[�N���X
//==============================================================
class CApplication
{
public:

	static const D3DXVECTOR3 CENTER_POS;	// �����ʒu

	//���(���[�h)�̎��
	enum MODE
	{
		MODE_TITLE = 0,		// �^�C�g�����
		MODE_GAME,			// �Q�[�����
		MODE_EDIT,			// �G�f�B�^���
		MODE_FADE,			// �t�F�[�h���
		MODE_TUTORIAL,		// �`���[�g���A�����
		MODE_MAX
	};

/* �V���O���g�� */
private: // �ÓI�����o�[�ϐ�
	static CApplication* m_pApplication;
public: // �ÓI�֐�
	static CApplication* GetInstance();
private:
	CApplication();

public:	// �����o�[�֐�
	~CApplication();

	HRESULT Init(HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	void SetWcex(WNDCLASSEX inWcex) { m_wcex = inWcex; }
	WNDCLASSEX GetWcex() { return m_wcex; }

	HWND GetWindow() { return m_window; }

	CRenderer* GetRenderer() { return m_renderer; }
	CTexture* GetTexture() { return m_texture; }
	CTaskGroup* GetTaskGroup() { return m_taskGroup; }
	CObjectXGroup* GetObjectXGroup() { return m_objectXGroup; }
	CFade* GetFade() { return m_fade; }

	void SetMode(CApplication::MODE inMode);
	MODE* GetMode() { return &m_modeType; }


	CMode* GetModeClass() { return m_mode; }
	CSound* GetSound() { return m_sound; }
	CColor* GetColor() { return m_color; }

private:
	CTexture* m_texture;
	CRenderer* m_renderer;
	CTaskGroup* m_taskGroup;
	CFade* m_fade;
	CMode* m_mode;
	CSound* m_sound;
	CColor* m_color;
	CObjectXGroup* m_objectXGroup;
	MODE m_modeType;

	HWND m_window;
	WNDCLASSEX m_wcex;
};
#endif
