//=============================================================================
//
// ���͏��� [directmouse.h]
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
// �T�v : �}�E�X�������s��
//
//=============================================================================

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include <assert.h>
#include <stdio.h>
#include "inputmouse.h"
#include "../application.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CInputMouse::CInputMouse()
{
	memset(&m_aKeyState, 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(&m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));

	m_fHeightWnd = 0.0f;
	m_fWidthWnd = 0.0f;
	m_bCursorErase = true;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CInputMouse::~CInputMouse()
{

}

//=============================================================================
// ������
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
// �T�v : �}�E�X�̃A�N�Z�X�����l���ł����ꍇ�A�������p������
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{

	// ���̓f�o�C�X�i�}�E�X�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �E�B���h�E�n���h���̊i�[
	m_hWnd = hWnd;

	// Device�ւ̃A�N�Z�X�����l��
	m_pDevMouse->Acquire();

	//�E�B���h�E�̉����ƍ����̎擾
	m_fWidthWnd = (float)SCREEN_WIDTH;
	m_fHeightWnd = (float)SCREEN_HEIGHT;

	return S_OK;
}

//=============================================================================
// �I��
// Author : KOZUNA HIROHITO
// �T�v : �}�E�X�̃A�N�Z�X����������A�f�o�C�X���������
//=============================================================================
void CInputMouse::Uninit(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̕���
	if (m_pDevMouse != nullptr)
	{
		m_pDevMouse->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevMouse->Release();
		m_pDevMouse = nullptr;
	}
}

//=============================================================================
// �X�V
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
// �T�v : �}�E�X���͂��ꂽ����ۑ�����
//=============================================================================
void CInputMouse::Update(void)
{
	// �ϐ��錾
	DIMOUSESTATE2 aKeyState;		// �}�E�X���͏��
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevMouse->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{
		for (nCntKey = 0; nCntKey < MAX_MOUSE_KEY; nCntKey++)
		{
			// �}�E�X�g���K�[����ۑ�
			m_aKeyStateTrigger.rgbButtons[nCntKey] = ~m_aKeyState.rgbButtons[nCntKey] & aKeyState.rgbButtons[nCntKey];

			// �}�E�X�����[�X����ۑ�
			m_aKeyStateRelease.rgbButtons[nCntKey] = m_aKeyState.rgbButtons[nCntKey] & ~aKeyState.rgbButtons[nCntKey];
			
		}

		// �}�E�X�v���X����ۑ�
		m_aKeyState = aKeyState;
	}
	else
	{
		// �}�E�X�ւ̃A�N�Z�X�����l��
		m_pDevMouse->Acquire();
	}
}

//=============================================================================
//  �}�E�X�v���X���̎擾
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CInputMouse::GetPress(MOUSE_KEY eKey)
{
	return (m_aKeyState.rgbButtons[eKey] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X�g���K�[���̎擾
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CInputMouse::GetTrigger(MOUSE_KEY eKey)
{
	return (m_aKeyStateTrigger.rgbButtons[eKey] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X�����[�X���̎擾
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CInputMouse::GetRelease(MOUSE_KEY eKey)
{
	return (m_aKeyStateRelease.rgbButtons[eKey] & 0x80) ? true : false;
}

//=============================================================================
// �S�L�[�v���X�̏��̎擾
// Author : KOZUNA HIROHITO
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CInputMouse::GetPressAll()
{
	for (int nCnt = 0; nCnt < MAX_MOUSE_KEY; nCnt++)
	{
		if (GetPress((MOUSE_KEY)nCnt))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// �S�L�[�v���X�̏��̎擾
// Author : KOZUNA HIROHITO
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CInputMouse::GetTriggerAll()
{
	for (int nCnt = 0; nCnt < MAX_MOUSE_KEY; nCnt++)
	{
		if (GetTrigger((MOUSE_KEY)nCnt))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// �S�L�[�v���X�̏��̎擾
// Author : KOZUNA HIROHITO
// �T�v : �����̃L�[�̏���Ԃ�
//=============================================================================
bool CInputMouse::GetReleaseAll()
{
	for (int nCnt = 0; nCnt < MAX_MOUSE_KEY; nCnt++)
	{
		if (GetRelease((MOUSE_KEY)nCnt))
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// �}�E�X�J�[�\���̈ʒu�̎擾
// Author1 : �������l
// Author2 : KOZUNA HIROHITO
// �T�v : �}�E�X�J�[�\���̈ʒu���擾���A���l��Ԃ�
//=============================================================================
D3DXVECTOR3 CInputMouse::GetMouseCursor(void)
{
	// �X�N���[�����W��̃}�E�X�J�[�\���̈ʒu�̎擾
	GetCursorPos(&m_Pos);

	// �E�B���h�E��̃}�E�X�J�[�\���̈ʒu�̎擾
	ScreenToClient(m_hWnd, &m_Pos);

	return D3DXVECTOR3((float)m_Pos.x, (float)m_Pos.y, 0.0f);
}

//=============================================================================
// �}�E�X�z�C�[���̈ړ��ʎ擾
// Author : �������l
// �T�v : �}�E�X�z�C�[���̈ړ��ʂ̐��l��Ԃ�
//=============================================================================
int CInputMouse::GetMouseWheel(void)
{
	return (int)m_aKeyState.lZ;
}

//=============================================================================
// �}�E�X�̈ړ��ʎ擾
// Author : �������l
// �T�v : �}�E�X�̈ړ��ʂ̐��l��Ԃ�
//=============================================================================
D3DXVECTOR3 CInputMouse::GetMouseMove(void)
{
	return D3DXVECTOR3((float)(m_aKeyState.lX), (float)(m_aKeyState.lY), (float)(m_aKeyState.lZ));
}