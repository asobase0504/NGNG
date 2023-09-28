//=============================================================================
//
// ���͏��� [directmouse.h]
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUTMOUSE_H_		//���̃}�N����`������Ȃ�������
#define _INPUTMOUSE_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "DirectInput.h"
#include "inputkeydata.h"

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputMouse : public CDirectInput
{
public:
	
private:
	static const int MAX_MOUSE_KEY = 8;		//�}�E�X�̎g���ĂȂ��L�[���܂߂��ő吔

public:
	CInputMouse();
	~CInputMouse()override;
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;		//�}�E�X�̏�����
	void Uninit(void)override;									//�}�E�X�̏I������
	void Update(void)override;									//�}�E�X�̍X�V����

	bool GetPress(MOUSE_KEY eKey);				//�v���X����
	bool GetTrigger(MOUSE_KEY eKey);			//�g���K�[����
	bool GetRelease(MOUSE_KEY eKey);			//�����[�X���̎擾
	bool GetPressAll();							//�I�[���v���X����	
	bool GetTriggerAll();						//�I�[���g���K�[����
	bool GetReleaseAll() ;						//�I�[�������[�X���̎擾
	D3DXVECTOR3 GetMouseCursor(void);		// �}�E�X�J�[�\���̃X�N���[�����W�̎擾
	int GetMouseWheel(void);				// �}�E�X�̃z�C�[���̓�������
	D3DXVECTOR3 GetMouseMove(void);			// �}�E�X�̈ړ��ʂ��o�͏���
	void SetCursorErase(bool bUse) { m_bCursorErase = bUse; ShowCursor(m_bCursorErase);} //��ʓ��̎��J�[�\�����������ǂ���

private:
	LPDIRECTINPUTDEVICE8 m_pDevMouse;				//���͂Ńp�X�ւ̃|�C���^
	DIMOUSESTATE2 m_aKeyState;						//�}�E�X�̃v���X����
	DIMOUSESTATE2 m_aKeyStateTrigger;				//�}�E�X�̃g���K�[����
	DIMOUSESTATE2 m_aKeyStateRelease;				//�}�E�X�̃g���K�[����
	POINT m_Pos;									//�}�E�X�̃J�[�\���p
	HWND m_hWnd;									//�E�B���h�E�n���h��
	bool m_bCursorErase;							//�J�[�\�����������ǂ���
	float m_fWidthWnd;								//�E�B���h�E�̉���
	float m_fHeightWnd;								//�E�B���h�E�̍���

};
#endif