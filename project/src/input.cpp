//=============================================================================
//
// ���͏��� [input.cpp]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "input.h"
#include "input\DirectInput.h"
#include "input\inputkeyboard.h"
#include "input\inputjoypad.h"
#include "input\inputmouse.h"
#include <assert.h>

//-----------------------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------
CInput *CInput::m_pInput = nullptr;//���̃N���X�̏��

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInput::CInput()
{
	m_pKeyboard = nullptr;		//�L�[�{�[�h�̏��
	m_pJoyPad = nullptr;		//�W���C�p�b�h�̏��
	m_pMouse = nullptr;			//�}�E�X�̏��
	m_nOldInputType = INPUT_TYPE_KEYBOARD;
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInput::~CInput()
{
}

//*************************************************************************************
//������
//*************************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(CDirectInput::Create(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̐���
	m_pKeyboard = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h�̐���
	m_pJoyPad = new CInputJoyPad;

	//�W���C�p�b�h�̏���������
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�}�E�X�̐���
	m_pMouse = new CInputMouse;

	//�}�E�X�̏���������
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInput::Uninit()
{
	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//�W���C�p�b�h�̔j��
	if (m_pJoyPad != nullptr)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}

	//�}�E�X�̔j��
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	CDirectInput::Break();

	//���Ȕj��
	if (m_pInput != nullptr)
	{
		delete m_pInput;
		m_pInput = nullptr;
	}
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInput::Update()
{
	//�L�[�{�[�h�̍X�V
	m_pKeyboard->Update();
	//�W���C�p�b�h�̍X�V
	m_pJoyPad->Update();
	//�}�E�X�̍X�V
	m_pMouse->Update();

	//�Ō�ɐG�����f�o�C�X
	if (m_pJoyPad->GetPressAll())
	{
		m_nOldInputType = INPUT_TYPE_JOYPAD;
	}
	else if (m_pKeyboard->GetKeyboardAllPress())
	{
		m_nOldInputType = INPUT_TYPE_KEYBOARD;
	}
	else if (m_pMouse->GetPressAll())
	{
		m_nOldInputType = INPUT_TYPE_MOUSE;
	}
}

//*************************************************************************************
//�C���v�b�g�̐���
//*************************************************************************************
CInput *CInput::Create()
{
	//Input�̎��Ȑ���
	m_pInput = new CInput;
	return m_pInput;
}

//*************************************************************************************
// ���͂����f�o�C�X�̔ԍ����擾 (Press)
//*************************************************************************************
std::vector<int> CInput::PressDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// �L�[�{�[�h���͂̒���
	if (Release(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad���͂̒���
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Release(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
// ���͂����f�o�C�X�̔ԍ����擾 (Trigger)
//*************************************************************************************
std::vector<int> CInput::TriggerDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// �L�[�{�[�h���͂̒���
	if (Trigger(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad���͂̒���
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Trigger(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
// ���͂����f�o�C�X�̔ԍ����擾 (Release)
//*************************************************************************************
std::vector<int> CInput::ReleaseDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// �L�[�{�[�h���͂̒���
	if (Release(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad���͂̒���
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Release(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
//�v���X����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Press(int nKey,int)
{
	return m_pKeyboard->GetKeyboardPress(nKey);
}

//*************************************************************************************
//�g���K�[����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Trigger(int nkey, int)
{
	return m_pKeyboard->GetKeyboardTrigger(nkey);
}

//*************************************************************************************
//�����[�X����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Release(int nkey, int)
{
	return m_pKeyboard->GetKeyboardRelease(nkey);
}

//*************************************************************************************
//�v���X����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Press(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetPress(key, nNum);
}

//*************************************************************************************
//�g���K�[����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Trigger(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetTrigger(key, nNum);
}

//*************************************************************************************
//�����[�X����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Release(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetRelease(key, nNum);
}

//*************************************************************************************
//�v���X����(�}�E�X)
//*************************************************************************************
bool CInput::Press(MOUSE_KEY Key)
{
	return m_pMouse->GetPress(Key);
}

//*************************************************************************************
//�g���K�[����(�}�E�X)
//*************************************************************************************
bool CInput::Trigger(MOUSE_KEY Key)
{
	return m_pMouse->GetTrigger(Key);
}

//*************************************************************************************
//�����[�X����(�}�E�X)
//*************************************************************************************
bool CInput::Release(MOUSE_KEY Key)
{
	return m_pMouse->GetRelease(Key);
}

//*************************************************************************************
//�\���L�[�̃x�N�g��
//*************************************************************************************
D3DXVECTOR3 CInput::VectorMoveKey(int nNum)
{
	D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_pJoyPad->GetJoyPadNumMax() == 0)
	{
		return VectorMove;
	}

	if (m_pJoyPad->GetJoyPadNumMax() <= nNum)
	{
		return VectorMove;
	}

	int nCheck = m_pJoyPad->GetCross(nNum);

	if (nCheck > 360 || nCheck < 0)
	{//�\���L�[�̊p�x���w��O��������O��Ԃ�
		return VectorMove;
	}

	float fRot = D3DXToRadian(nCheck);

	VectorMove.x = sinf(fRot);
	VectorMove.y = -cosf(fRot);

	//�����P�̃x�N�g���ϊ�
	D3DXVec3Normalize(&VectorMove, &VectorMove);

	return VectorMove;
}

D3DXVECTOR3 CInput::VectorMoveKeyAll()
{
	D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nJoyPad = m_pJoyPad->GetJoyPadNumMax();
	if (m_pJoyPad->GetJoyPadNumMax() == 0)
	{
		return VectorMove;
	}

	for (int nCnt = 0; nCnt < nJoyPad; nCnt++)
	{
		int nCheck = m_pJoyPad->GetCross(nCnt);

		if (nCheck > 360 || nCheck < 0)
		{//�\���L�[�̊p�x���w��O��������O��Ԃ�
			return VectorMove;
		}

		float fRot = D3DXToRadian(nCheck);

		VectorMove.x = sinf(fRot);
		VectorMove.y = -cosf(fRot);

		//�����P�̃x�N�g���ϊ�
		D3DXVec3Normalize(&VectorMove, &VectorMove);

		if (VectorMove != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			return VectorMove;
		}

	}
	return VectorMove;
}

//*************************************************************************************
//�W���C�X�e�B�b�N�̃x�N�g��
//*************************************************************************************
D3DXVECTOR3 CInput::VectorMoveJoyStick(int nNum, bool bleftandright)
{
	D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_pJoyPad->GetJoyPadNumMax() == 0)
	{
		return VectorMove;
	}

	VectorMove = m_pJoyPad->GetJoyStickData(nNum, bleftandright);
	//�����P�̃x�N�g���ϊ�
	D3DXVec3Normalize(&VectorMove, &VectorMove);
	return VectorMove;
}

//*************************************************************************************
//�W���C�X�e�B�b�N�̃x�N�g��
//*************************************************************************************
D3DXVECTOR3 CInput::VectorMoveJoyStickAll(bool bleftandright)
{
	D3DXVECTOR3 VectorNull = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VectorMove = m_pJoyPad->GetJoyStickData(nCnt, bleftandright);
		//�����P�̃x�N�g���ϊ�
		D3DXVec3Normalize(&VectorMove, &VectorMove);
		if (VectorNull != VectorMove)
		{
			return  VectorMove;
		}
	}

	return VectorNull;
}

//*************************************************************************************
// �}�E�X�J�[�\���̃X�N���[�����W�̎擾
//*************************************************************************************
D3DXVECTOR3 CInput::GetMouseCursor(void)
{
	return m_pMouse->GetMouseCursor();
}

//*************************************************************************************
// �}�E�X�̃z�C�[���̓�������
//*************************************************************************************
int CInput::GetMouseWheel(void)
{
	return m_pMouse->GetMouseWheel();
}

//*************************************************************************************
// �}�E�X�̈ړ��ʂ��o�͏���
//*************************************************************************************
D3DXVECTOR3 CInput::GetMouseMove(void)
{
	return m_pMouse->GetMouseMove();
}

//*************************************************************************************
// ��ʓ��̃J�[�\�����������ǂ���
//*************************************************************************************
void CInput::SetCursorErase(bool bUse)
{
	// ��ʓ��̃J�[�\�����������ǂ���
	m_pMouse->SetCursorErase(bUse);
}

//*************************************************************************************
//�L�[�̓���ւ�
//*************************************************************************************
void CInput::SetJoypadKeyConfig(int nPlayerNum, DirectJoypad OldKey, DirectJoypad NewKey)
{
	//�ύX�����L�[���ύX�\�ԍ��ȏゾ������G���[
	if (OldKey > JOYPAD_HOME || NewKey > JOYPAD_HOME)
	{
		return;
	}
	//�W���C�p�b�h�̃L�[����ւ��֐����Ă�
	m_pJoyPad->SetKeyConfig(nPlayerNum, OldKey, NewKey);
}

//*************************************************************************************
//�W���C�p�b�h���ڑ�����Ă��邩�ǂ���
//*************************************************************************************
bool CInput::IsConnected(int nNum)
{
	//�f�o�C�X�f�[�^�����݂��邩�ǂ���
	if (m_pJoyPad->GetInputDevice(nNum) != nullptr)
	{
		return true;
	}
	return false;
}

//*************************************************************************************
//�W���C�p�b�h�̐ڑ���
//*************************************************************************************
int CInput::GetIsConnectedNumMax()
{
	return m_pJoyPad->GetJoyPadNumMax();
}

//*************************************************************************************
//�f�o�C�X�̓r�����m�̃I���I�t
//*************************************************************************************
void CInput::IntermediateReception(bool bIR)
{
	m_pJoyPad->IntermediateReception(bIR);
}

//*************************************************************************************
//���݃f�o�C�X�̓r�����m���s���Ă��邩�ǂ���
//*************************************************************************************
bool CInput::GetIntermediateReception()
{
	return m_pJoyPad->GetIntermediateReception();
}

//*************************************************************************************
// �S�f�o�C�X�̓��͂��m�F
//*************************************************************************************
bool CInput::KeyChackAll(STAN_DART_INPUT_KEY key, int type)
{
	auto lambda = [this, type](auto a)
	{
		if (a == KEY_ALL)
		{
			switch (type)
			{
			case 1:
				return m_pKeyboard->GetKeyboardAllPress() || m_pJoyPad->GetPressAll() || m_pMouse->GetPressAll();
				break;
			case 2:
				return m_pKeyboard->GetKeyboardAllTrigger() || m_pJoyPad->GetTriggerAll() || m_pMouse->GetTriggerAll();
				break;
			case 3:
				return m_pKeyboard->GetKeyboardAllRelease() || m_pJoyPad->GetReleaseAll() || m_pMouse->GetReleaseAll();
				break;
			default:
				break;
			}
		}

		switch (type)
		{
		case 1:
			return Press(a);
			break;
		case 2:
			return Trigger(a);
			break;
		case 3:
			return Release(a);
			break;
		default:
			break;
		}
		return false;
	};

	switch (key)
	{
	case KEY_UP:
		return (lambda(DIK_W) || lambda(DIK_UP) || lambda(JOYPAD_UP));
		break;
	case KEY_UP_LEFT:
		return ((lambda(DIK_W) && lambda(DIK_A)) || (lambda(DIK_UP) && lambda(DIK_LEFT)) || lambda(JOYPAD_UP_LEFT));
		break;
	case KEY_UP_RIGHT:
		return ((lambda(DIK_W) && lambda(DIK_D)) || (lambda(DIK_UP) && lambda(DIK_RIGHT)) || lambda(JOYPAD_UP_RIGHT));
		break;
	case KEY_DOWN:
		return (lambda(DIK_S) || lambda(DIK_DOWN) || lambda(JOYPAD_DOWN));
		break;
	case KEY_DOWN_LEFT:
		return ((lambda(DIK_S) && lambda(DIK_A)) || (lambda(DIK_DOWN) && lambda(DIK_LEFT)) || lambda(JOYPAD_DOWN_LEFT));
		break;
	case KEY_DOWN_RIGHT:
		return (lambda(DIK_S) && lambda(DIK_D)) || (lambda(DIK_DOWN) && lambda(DIK_RIGHT)) || lambda(JOYPAD_DOWN_RIGHT);
		break;
	case KEY_LEFT:
		return lambda(DIK_A) || lambda(DIK_LEFT) || lambda(JOYPAD_LEFT);
		break;
	case KEY_RIGHT:
		return lambda(DIK_D) || lambda(DIK_RIGHT) || lambda(JOYPAD_RIGHT);
		break;
	case KEY_DECISION:
		return lambda(DIK_RETURN) || lambda(JOYPAD_A);
		break;
	case KEY_SHOT:
		return lambda(DIK_SPACE) || lambda(JOYPAD_R1);
		break;
	case KEY_BACK:
		return lambda(DIK_BACKSPACE) || lambda(DIK_B) || lambda(JOYPAD_BACK) || lambda(JOYPAD_B);
		break;
	case KEY_SHIFT:
		return lambda(DIK_RSHIFT) || lambda(DIK_LSHIFT) || lambda(JOYPAD_A);
		break;
	case KEY_MOVE:
		return Trigger(KEY_UP) || Trigger(KEY_DOWN) || Trigger(KEY_LEFT) || Trigger(KEY_RIGHT);
		break;
	case KEY_PAUSE:
		return lambda(DIK_P) || lambda(JOYPAD_START) || lambda(JOYPAD_HOME);
		break;
	case KEY_ALL:
		return lambda(key);
		break;
	default:
		break;
	}

	// �\�肳��ĂȂ��L�[���Ă΂ꂽ
	assert(false);
	return false;
}

//*************************************************************************************
// �w�肵���f�o�C�X�̓��͂��m�F
//*************************************************************************************
bool CInput::KeyChackNum(STAN_DART_INPUT_KEY key, int type, int nNum)
{
	auto lambda = [this, nNum, type](auto a)
	{
		switch (type)
		{
		case 1:
			return Press(a, nNum);
			break;
		case 2:
			return Trigger(a, nNum);
			break;
		case 3:
			return Release(a, nNum);
			break;
		default:
			break;
		}
		return false;
	};

	switch (key)
	{
	case KEY_UP:
		return (lambda(DIK_W) || lambda(DIK_UP) || lambda(JOYPAD_UP));
		break;
	case KEY_UP_LEFT:
		return ((lambda(DIK_W) && lambda(DIK_A)) || (lambda(DIK_UP) && lambda(DIK_LEFT)) || lambda(JOYPAD_UP_LEFT));
		break;
	case KEY_UP_RIGHT:
		return ((lambda(DIK_W) && lambda(DIK_D)) || (lambda(DIK_UP) && lambda(DIK_RIGHT)) || lambda(JOYPAD_UP_RIGHT));
		break;
	case KEY_DOWN:
		return (lambda(DIK_S) || lambda(DIK_DOWN) || lambda(JOYPAD_DOWN));
		break;
	case KEY_DOWN_LEFT:
		return ((lambda(DIK_S) && lambda(DIK_A)) || (lambda(DIK_DOWN) && lambda(DIK_LEFT)) || lambda(JOYPAD_DOWN_LEFT));
		break;
	case KEY_DOWN_RIGHT:
		return (lambda(DIK_S) && lambda(DIK_D)) || (lambda(DIK_DOWN) && lambda(DIK_RIGHT)) || lambda(JOYPAD_DOWN_RIGHT);
		break;
	case KEY_LEFT:
		return lambda(DIK_A) || lambda(DIK_LEFT) || lambda(JOYPAD_LEFT);
		break;
	case KEY_RIGHT:
		return lambda(DIK_D) || lambda(DIK_RIGHT) || lambda(JOYPAD_RIGHT);
		break;
	case KEY_DECISION:
		return lambda(DIK_RETURN) || lambda(JOYPAD_A);
		break;
	case KEY_SHOT:
		return lambda(DIK_SPACE) || lambda(JOYPAD_R1);
		break;
	case KEY_BACK:
		return lambda(DIK_BACKSPACE) || lambda(DIK_B) || lambda(JOYPAD_BACK) || lambda(JOYPAD_B);
		break;
	case KEY_SHIFT:
		return lambda(DIK_RSHIFT) || lambda(DIK_LSHIFT) || lambda(JOYPAD_A);
		break;
	case KEY_MOVE:
		return Trigger(KEY_UP) || Trigger(KEY_DOWN) || Trigger(KEY_LEFT) || Trigger(KEY_RIGHT);
		break;
	case KEY_PAUSE:
		return lambda(DIK_P) || lambda(JOYPAD_START) || lambda(JOYPAD_HOME);
		break;
	case KEY_ALL:
		return lambda(-2);
		break;
	default:
		break;

	}

	// �\�肳��ĂȂ��L�[���Ă΂ꂽ
	assert(false);
	return false;
}
