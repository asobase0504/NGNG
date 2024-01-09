//=============================================================================
//
// ���͏��� [inputjoypad.cpp]
// Author1 : KOZUNA HIROHITO
// input.h���Q�Ƃ𐄏�
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "inputjoypad.h"
#include <stdio.h>
#include <assert.h>

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInputJoyPad::CInputJoyPad()
{
	ZeroMemory(&m_apDevice, sizeof(m_apDevice));
	ZeroMemory(&m_JoyPadData, sizeof(m_JoyPadData));
	m_AllOldKeyTrigger = JOYPAD_MAX;
	m_AllOldKeyRelease = JOYPAD_MAX;
	m_hWnd = nullptr;
	m_nAfterAppExecutionJoyNumCnt = 0;
	m_nDeviceAdditionalIntervalExecutingApp = 0;
	m_nJoyNumCnt = 0;
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInputJoyPad::~CInputJoyPad()
{
}

//*************************************************************************************
//�f�o�C�X��񋓂��ăf�o�C�X���쐬���Ă����R�[���o�b�N�֐�
//*************************************************************************************
BOOL CALLBACK CInputJoyPad::EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

	//This�|�C���^�̎擾
	CInputJoyPad *pThis = (CInputJoyPad*)pContext;

	//�f�o�C�X�|�C���^
	LPDIRECTINPUTDEVICE8 pInputDevice = nullptr;

	//�f�o�C�X�̎擾
	hr = m_pInput->CreateDevice(pdidInstance->guidInstance, &pInputDevice, NULL);

	//��L�̃G���[���m
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�ւ̃|�C���^�̐ݒ�
	pThis->SetDevicePointer(pInputDevice);

	//���̃f�o�C�X�𒲂ׂ�Ƃ���DIENUM_CONTINUE�ŏ��̈��݂̂̏ꍇ��DIENUM_STOP
	return DIENUM_CONTINUE;
}

//�f�o�C�X�ɑ΂��ăX�e�B�b�N�͈͓̔����w��
BOOL CALLBACK CInputJoyPad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	LPDIRECTINPUTDEVICE8 pInputDevice = (LPDIRECTINPUTDEVICE8)pContext;
	// ���͔͈͂̃Z�b�g
	DIPROPRANGE diprg;
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMax = 1000;
	diprg.lMin = -1000;

	// X��
	diprg.diph.dwObj = DIJOFS_X;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// Y��
	diprg.diph.dwObj = DIJOFS_Y;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// Z��
	diprg.diph.dwObj = DIJOFS_Z;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RX��
	diprg.diph.dwObj = DIJOFS_RX;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RY��
	diprg.diph.dwObj = DIJOFS_RY;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RZ��
	diprg.diph.dwObj = DIJOFS_RZ;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	return DIENUM_CONTINUE;
}

//*************************************************************************************
//������
//*************************************************************************************
HRESULT CInputJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�E�B���h�E�n���h���̕ۑ�
	m_hWnd = hWnd;

	//���̓f�o�C�X�̓o�^�֐�
	if (FAILED(JoyPadDeviceRegistration(m_hWnd)))
	{
		return E_FAIL;
	}

	//�L�[�R���t�B�O�̓ǂݍ���
	KeyConfigLoading();

	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInputJoyPad::Uninit(void)
{
	//�L�[�R���t�B�O�̕ۑ�
	KeyConfigSave();

	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		//���̓f�o�C�X�̕���
		if (m_JoyPadData[nCnt].pInputDevice != nullptr)
		{
			m_JoyPadData[nCnt].pInputDevice->Unacquire();
			m_JoyPadData[nCnt].pInputDevice->Release();
			m_JoyPadData[nCnt].pInputDevice = nullptr;
		}
	}
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInputJoyPad::Update(void)
{
	//�f�o�C�X�̓r���擾�̗L��
	//if (m_bIntermediateReception)
	//{
	//	//�A�v�����s���̃f�o�C�X�ǉ��Ԋu
	//	if (DEVICE_ADDITIONAL_INTERVAL_EXECUTING_APP < m_nDeviceAdditionalIntervalExecutingApp)
	//	{
	//		//�J�E���^�̏�����
	//		m_nDeviceAdditionalIntervalExecutingApp = 0;
	//		//���̓f�o�C�X�̓o�^�֐�
	//		if (FAILED(JoyPadDeviceRegistration(m_hWnd)))
	//		{
	//			assert(false);
	//		}
	//	}
	//	else
	//	{
	//		//�J�E���^�̉��Z
	//		m_nDeviceAdditionalIntervalExecutingApp++;
	//	}
	//}

	//�f�o�C�X���X�g���m�p
	bool bLost = false;

	//���͏����̍X�V
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			continue;
		}
		HRESULT hr;
		//�f�o�C�X����f�[�^���擾�ł��邱�Ƃ��m�F���A�m�F�ł��Ȃ������ꍇ�ɂ̓A�N�Z�X�����擾
		hr = m_JoyPadData[nCnt].pInputDevice->Poll();
		if (FAILED(hr))
		{
			
			hr = m_JoyPadData[nCnt].pInputDevice->Acquire();

			//�f�o�C�X�����X�g�����ꍇ
			if (hr == DIERR_UNPLUGGED)
			{
				bLost = true;
				continue;
			}
		}

		DIJOYSTATE JoyKey;
		//�R���g���[���[�̏�Ԃ��擾
		if (SUCCEEDED(m_JoyPadData[nCnt].pInputDevice->GetDeviceState(sizeof(DIJOYSTATE), &JoyKey)))
		{
			for (int nButtons = 0; nButtons < MAX_JOY_KEY; nButtons++)
			{
				//�g���K�[����ۑ�
				m_JoyPadData[nCnt].aKeyStateTrigger.rgbButtons[nButtons] = ~m_JoyPadData[nCnt].aKeyState.rgbButtons[nButtons] & JoyKey.rgbButtons[nButtons];

				//�����[�X����ۑ�
				m_JoyPadData[nCnt].aKeyStateRelease.rgbButtons[nButtons] = m_JoyPadData[nCnt].aKeyState.rgbButtons[nButtons] & ~JoyKey.rgbButtons[nButtons];


			}
			m_JoyPadData[nCnt].aKeyState = JoyKey;//�v���X�����̕ۊ�
			m_JoyPadData[nCnt].nCrossPressRot = (int)(m_JoyPadData[nCnt].aKeyState.rgdwPOV[0] / 100.0f);//�W���C�p�b�h�̏\���L�[�̉�����Ă������
		}
		
	}

	//�f�o�C�X���X�g�ɂ��f�o�C�X�̓���ւ�
	if (bLost)
	{
		//���̓f�o�C�X�̓o�^�֐�
		if (FAILED(JoyPadDeviceRegistration(m_hWnd)))
		{
			assert(false);
		}
	}
}

//*************************************************************************************
//���̓f�o�C�X�̓o�^�֐�
//*************************************************************************************
HRESULT CInputJoyPad::JoyPadDeviceRegistration(HWND hWnd)
{
	//�o�^�̂��߂̃J�E���^�[�̏�����
	m_nAfterAppExecutionJoyNumCnt = 0;

	// �f�o�C�X�̗�
	if (FAILED(m_pInput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		this,
		DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	//�f�[�^�̌�
	m_nJoyNumCnt = 0;

	//�f�[�^�̌��̃`�F�b�N
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice != nullptr)
		{
			m_nJoyNumCnt++;
		}
	}

	//�O��̓o�^���ƌ��݂̐ڑ����̔�r
	if (m_nJoyNumCnt == m_nAfterAppExecutionJoyNumCnt)
	{
		ZeroMemory(&m_apDevice, sizeof(m_apDevice));
		return S_OK;
	}

	//�ꎞ�f�[�^�̏�����
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		//���̓f�o�C�X�̕���
		if (m_JoyPadData[nCnt].pInputDevice != nullptr)
		{
			m_JoyPadData[nCnt].pInputDevice->Unacquire();
			m_JoyPadData[nCnt].pInputDevice->Release();
			m_JoyPadData[nCnt].pInputDevice = nullptr;
		}
	}
	ZeroMemory(&m_JoyPadData, sizeof(m_JoyPadData));

	//�f�[�^�̑}���Ɣ��̃`�F�b�N
	for (int nCnt = 0; nCnt < m_nAfterAppExecutionJoyNumCnt; nCnt++)
	{
		//�f�o�C�X�|�C���^�̑}��
		m_JoyPadData[nCnt].pInputDevice = m_apDevice[nCnt];

		//�f�o�C�X��NULL�`�F�b�N
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			continue;
		}

		// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
		HRESULT hr = m_JoyPadData[nCnt].pInputDevice->SetDataFormat(&c_dfDIJoystick);

		if (FAILED(hr))
		{
			return E_FAIL;
		}

		// �������[�h�̐ݒ�
		if (FAILED(m_JoyPadData[nCnt].pInputDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return E_FAIL;
		}

		//�f�o�C�X�ɑ΂��ď\���L�[�͈͓̔����w��
		if (FAILED(m_JoyPadData[nCnt].pInputDevice->EnumObjects(EnumAxesCallback,
			m_JoyPadData[nCnt].pInputDevice,
			DIDFT_AXIS)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//���̓f�o�C�X�ւ̃|�C���^�̐ݒ�
int CInputJoyPad::SetInputDevice(LPDIRECTINPUTDEVICE8 pInputDeviceint)
{
	//�󂢂Ă���ۑ���Ɍ���
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		//�ۑ��悪�󂢂Ă��邩�̊m�F
		if(m_JoyPadData[nCnt].pInputDevice != nullptr)
		{
			continue;
		}

		//�ۑ�
		m_JoyPadData[nCnt].pInputDevice = pInputDeviceint;

		//�����̏I���
		return nCnt;

	}
	
	return -1;
}

//�v���X����
bool CInputJoyPad::GetPress(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (eKey > JOYPAD_HOME)
	{
		return GetCrossPress(eKey, nNum);
	}
	return (m_JoyPadData[nNum].aKeyState.rgbButtons[m_KeyConfig[nNum][eKey]] & 0x80) ? true : false;
}

//�g���K�[����
bool CInputJoyPad::GetTrigger(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (eKey > JOYPAD_HOME)
	{
		return GetCrossTrigger(eKey, nNum);
	}
	return (m_JoyPadData[nNum].aKeyStateTrigger.rgbButtons[m_KeyConfig[nNum][eKey]] & 0x80) ? true : false;
}

//�����[�X����
bool CInputJoyPad::GetRelease(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (eKey > JOYPAD_HOME)
	{
		return GetCrossRelease(eKey, nNum);
	}
	return (m_JoyPadData[nNum].aKeyStateRelease.rgbButtons[m_KeyConfig[nNum][eKey]] & 0x80) ? true : false;
}

//�\���L�[�v���X����
bool CInputJoyPad::GetCrossPress(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	switch (eKey)
	{
	case JOYPAD_UP:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_UP
			|| m_JoyPadData[nNum].aKeyState.lY <= -700
			|| m_JoyPadData[nNum].aKeyState.lRz <= -700)
		{
			return true;
		}
		break;
	case JOYPAD_UP_LEFT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_UP_LEFT
			|| (m_JoyPadData[nNum].aKeyState.lY <= -700 && m_JoyPadData[nNum].aKeyState.lX <= -700)
			|| (m_JoyPadData[nNum].aKeyState.lRz <= -700 && m_JoyPadData[nNum].aKeyState.lZ <= -700))
		{
			return true;
		}
		break;
	case JOYPAD_UP_RIGHT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_UP_RIGHT
			|| (m_JoyPadData[nNum].aKeyState.lY <= -700 && m_JoyPadData[nNum].aKeyState.lX >= 700)
			|| (m_JoyPadData[nNum].aKeyState.lRz <= -700 && m_JoyPadData[nNum].aKeyState.lZ >= 700))
		{
			return true;
		}
		break;
	case JOYPAD_DOWN:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_DOWN
			|| m_JoyPadData[nNum].aKeyState.lY >= 700
			|| m_JoyPadData[nNum].aKeyState.lRz >= 700)
		{
			return true;
		}
		break;
	case JOYPAD_DOWN_LEFT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_DOWN_LEFT
			|| (m_JoyPadData[nNum].aKeyState.lY >= 700 && m_JoyPadData[nNum].aKeyState.lX <= -700)
			|| (m_JoyPadData[nNum].aKeyState.lRz >= 700 && m_JoyPadData[nNum].aKeyState.lZ <= -700))
		{
			return true;
		}
		break;
	case JOYPAD_DOWN_RIGHT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_DOWN_RIGHT
			|| (m_JoyPadData[nNum].aKeyState.lY >= 700 && m_JoyPadData[nNum].aKeyState.lX >= 700)
			|| (m_JoyPadData[nNum].aKeyState.lRz >= 700 && m_JoyPadData[nNum].aKeyState.lZ >= 700))
		{
			return true;
		}
		break;
	case JOYPAD_LEFT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_LEFT
			|| m_JoyPadData[nNum].aKeyState.lX <= -700
			|| m_JoyPadData[nNum].aKeyState.lZ <= -700)
		{
			return true;
		}
		break;
	case JOYPAD_RIGHT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_RIGHT
			|| m_JoyPadData[nNum].aKeyState.lX >= 700
			|| m_JoyPadData[nNum].aKeyState.lZ >= 700)
		{
			return true;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

//�\���L�[�g���K�[����
bool CInputJoyPad::GetCrossTrigger(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (!m_JoyPadData[nNum].bOldKeyTrigger[eKey - JOYPAD_UP]
		&& GetCrossPress(eKey, nNum))
	{
		m_JoyPadData[nNum].bOldKeyTrigger[eKey - JOYPAD_UP] = true;
		return true;
	}
	else if (m_JoyPadData[nNum].bOldKeyTrigger[eKey - JOYPAD_UP]
		&& GetCrossPress(eKey, nNum))
	{
		return false;
	}

	m_JoyPadData[nNum].bOldKeyTrigger[eKey - JOYPAD_UP] = false;
	return false;
}

//�\���L�[�����[�X����
bool CInputJoyPad::GetCrossRelease(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (GetPress(eKey, nNum))
	{
		m_JoyPadData[nNum].bOldKeyRelease[eKey - JOYPAD_UP] = true;
		return false;
	}
	else if(m_JoyPadData[nNum].bOldKeyRelease[eKey - JOYPAD_UP]
		&& !GetPress(eKey, nNum)
		)
	{
		m_JoyPadData[nNum].bOldKeyRelease[eKey - JOYPAD_UP] = false;
		return true;
	}
	
	return false;
}

//�I�[���v���X����	�i�L�[�w�肠��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetPressAll(DirectJoypad eKey)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (GetPress(eKey, nCnt))
		{
			return true;
		}
	}
	return false;
}

//�I�[���g���K�[�����i�L�[�w�肠��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetTriggerAll(DirectJoypad eKey)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (GetPress(eKey, nCnt) && m_AllOldKeyTrigger == JOYPAD_MAX)
		{
			m_AllOldKeyTrigger = eKey;
			return true;
		}
	}

	if (GetPressAll())
	{//�N�����L�[�������Ă�����
		return false;
	}

	m_AllOldKeyTrigger = JOYPAD_MAX;
	return false;
}

//�I�[�������[�X�����i�L�[�w�肠��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetReleaseAll(DirectJoypad eKey)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (GetPress(eKey, nCnt))
		{
			m_AllOldKeyRelease = eKey;
			return false;
		}

		if (!GetPressAll() 
			&& m_AllOldKeyRelease == eKey
			&& m_AllOldKeyRelease != JOYPAD_MAX)
		{
			m_AllOldKeyRelease = JOYPAD_MAX;
			return true;
		}
	}

	if (GetPressAll())
	{//�N�����L�[�������Ă�����
		return false;
	}

	m_AllOldKeyRelease = JOYPAD_MAX;
	return false;
}

//�I�[���v���X����	�i�L�[�w��Ȃ��A�v���C���[�w�肠��j
bool CInputJoyPad::GetPressAll(int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
	{
		if (GetPress((DirectJoypad)nCntKey, nNum))
		{
			return true;
		}
	}
	return false;
}

//�I�[���g���K�[�����i�L�[�w��Ȃ��A�v���C���[�w�肠��j
bool CInputJoyPad::GetTriggerAll(int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
	{
		if (GetPress((DirectJoypad)nCntKey, nNum) && m_JoyPadData[nNum].aOldKeyTrigger != nCntKey)
		{
			m_JoyPadData[nNum].aOldKeyTrigger = (DirectJoypad)nCntKey;
			return true;
		}
		else if (GetPress((DirectJoypad)nCntKey, nNum) && m_JoyPadData[nNum].aOldKeyTrigger == nCntKey)
		{
			return false;
		}
	}

	m_JoyPadData[nNum].aOldKeyTrigger = JOYPAD_MAX;
	return false;
}

//�I�[�������[�X�����i�L�[�w��Ȃ��A�v���C���[�w�肠��j
bool CInputJoyPad::GetReleaseAll(int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
	{
		if (!GetPressAll() && m_JoyPadData[nNum].aOldKeyRelease == nCntKey)
		{
			m_JoyPadData[nNum].aOldKeyRelease = JOYPAD_MAX;
			return true;
		}
		else if (GetPress((DirectJoypad)nCntKey, nNum))
		{
			m_JoyPadData[nNum].aOldKeyRelease = (DirectJoypad)nCntKey;
			return false;
		}
	}

	m_JoyPadData[nNum].aOldKeyRelease = JOYPAD_MAX;
	return false;
}

//�I�[���v���X����	�i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetPressAll()
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			return false;
		}

		if (GetPressAll(nCnt))
		{
			return true;
		}
	}
	return false;
}

//�I�[���g���K�[�����i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetTriggerAll()
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			continue;
		}

		for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
		{
			if (GetPress((DirectJoypad)nCntKey, nCnt))
			{
				if (m_AllOldKeyTrigger != nCntKey)
				{
					m_AllOldKeyTrigger = (DirectJoypad)nCntKey;
					return true;
				}
				else if (m_AllOldKeyTrigger == nCntKey)
				{
					return false;
				}
			}
		}
	}

	m_AllOldKeyTrigger =JOYPAD_MAX;
	return false;
}

//�I�[�������[�X�����i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetReleaseAll()
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		for (int nKey = 0; nKey < MAX_JOY_KEY; nKey++)
		{
			if (GetPress((DirectJoypad)nKey, nCnt))
			{
				m_AllOldKeyRelease = (DirectJoypad)nKey;
				return false;
			}

			if (!GetPressAll()
				&& m_AllOldKeyRelease == (DirectJoypad)nKey
				&& m_AllOldKeyRelease != JOYPAD_MAX)
			{
				m_AllOldKeyRelease = JOYPAD_MAX;
				return true;
			}
		}
	}

	if (GetPressAll())
	{//�N�����L�[�������Ă�����
		return false;
	}

	m_AllOldKeyRelease = JOYPAD_MAX;
	return false;
}

//�W���C�X�e�B�b�N�̒l��Ԃ�
D3DXVECTOR3 CInputJoyPad::GetJoyStickData(int nNum, bool bleftandright)
{
	if (bleftandright)
	{//�X�e�B�b�N�̉E��(true  = �E�Afalse = ��)
		if (m_JoyPadData[nNum].aKeyState.lRz != 0
			|| m_JoyPadData[nNum].aKeyState.lZ != 0)
		{
			return D3DXVECTOR3((float)m_JoyPadData[nNum].aKeyState.lZ, (float)m_JoyPadData[nNum].aKeyState.lRz, 0.0f);
		}

		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	if (m_JoyPadData[nNum].aKeyState.lY != 0
		|| m_JoyPadData[nNum].aKeyState.lX != 0)
	{
		return D3DXVECTOR3((float)m_JoyPadData[nNum].aKeyState.lX, (float)m_JoyPadData[nNum].aKeyState.lY, 0.0f);
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*************************************************************************************
//�L�[�̓���ւ�
//*************************************************************************************
void CInputJoyPad::SetKeyConfig(int nPlayerNum, DirectJoypad OldKey, DirectJoypad NewKey)
{
	//�ύX����O�̃L�[�̕ۑ�
	DirectJoypad KeySave = m_KeyConfig[nPlayerNum][OldKey];

	//�ύX�Ώۂ̃L�[��ύX��̃L�[�ɕύX
	m_KeyConfig[nPlayerNum][OldKey] = m_KeyConfig[nPlayerNum][NewKey];

	//�ꎞ�ۑ������ύX�O�̃L�[��ύX��L�[�ɓ���ւ�
	m_KeyConfig[nPlayerNum][NewKey] = KeySave;
}

//�L�[�R���t�B�O�̓ǂݍ���
void CInputJoyPad::KeyConfigLoading()
{
	FILE *pFile = NULL;			//�t�@�C���|�C���^�[�錾

	char cBff[LINE_MAX_READING_LENGTH];		//��s���ǂݎ�邽�߂̕ϐ�
	char cBffHead[LINE_MAX_READING_LENGTH];	//���̕�����ǂݎ�邽�߂̕ϐ�

	//�t�@�C�����J��
	pFile = fopen("data\\FILE\\KeyConfigData.txt", "r");

	if (pFile == nullptr)
	{//�J���Ȃ��������p
		assert(false);
	}

	//�ǂݍ��ރR���g���[���[�̃J�E���^�[
	int nCntJoypad = 0;

	//������̓ǂݎ�胋�[�v����
	while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
	{
		//������̕���
		sscanf(cBff, "%s", &cBffHead);

		if (strcmp(&cBffHead[0], "ONE_MINUTES_LOADING") == 0)
		{//�R���g���[���[�@����̃L�[�R���t�B�O�̓ǂݍ���

			//�ǂݍ��񂾃R���g���[���[�̐����K�萔�ȏゾ������
			if (nCntJoypad >= JOYPAD_DATA_MAX)
			{
				assert(false);
			}

			//�ǂݍ���Key�̃J�E���^�[
			int nCntKey = 0; 

			//�L�[�R���t�B�O�f�[�^�̈ꎞ�ۑ�
			DirectJoypad KeyConfig[KEY_CONFIG_SUPPORTED_KEY_NUMBER];

			//������̓ǂݎ�胋�[�v����
			while (fgets(cBff, LINE_MAX_READING_LENGTH, pFile) != nullptr)
			{
				//������̕���
				sscanf(cBff, "%s", &cBffHead);
				
				if (strcmp(&cBffHead[0], "KEY") == 0)
				{//�{�^������̃L�[�R���t�B�O�̓ǂݍ���

					//�J�E���^�[���K�萔�ȏゾ������
					if (nCntKey >= KEY_CONFIG_SUPPORTED_KEY_NUMBER)
					{
						//�ȉ��̏����𖳎�����
						continue;
					}

					//������̕���
					sscanf(cBff, "%s = %d", &cBffHead, &KeyConfig[nCntKey]);

					//�K��͈̔͂𒴂��Ă����ꍇ�̓G���[�h�~�̂��߂O��������
					if (KeyConfig[nCntKey] >= KEY_CONFIG_SUPPORTED_KEY_NUMBER || KeyConfig[nCntKey] < 0)
					{
						KeyConfig[nCntKey] = (DirectJoypad)0;
					}

					//�ǂݍ��݃J�E���^�[��i�߂�
					nCntKey++;
				}
				else if (strcmp(&cBffHead[0], "ONE_MINUTES_LOADING_END") == 0)
				{//�R���g���[���[�@����̃L�[�R���t�B�O�̓ǂݍ��݂̏I���

					//�ǂݍ��񂾏��̕ۑ�
					for (int nCnt = 0; nCnt < KEY_CONFIG_SUPPORTED_KEY_NUMBER; nCnt++)
					{
						m_KeyConfig[nCntJoypad][nCnt] = KeyConfig[nCnt];
					}

					//�ǂݍ��񂾃R���g���[���[�J�E���^�[��i�߂�
					nCntJoypad++;

					break;
				}

				//�ۑ����̕�����̏�����
				ZeroMemory(&cBff, sizeof(cBff));
				ZeroMemory(&cBffHead, sizeof(cBffHead));
			}
		}
		else if (strcmp(&cBffHead[0], "END_SCRIPT") == 0)
		{//�X�N���v�g�̏I���
			break;
		}

		//�ۑ����̕�����̏�����
		ZeroMemory(&cBff, sizeof(cBff));
		ZeroMemory(&cBffHead, sizeof(cBffHead));
	}

	//�t�@�C�������
	fclose(pFile);
}

//�L�[�R���t�B�O�̕ۑ�
void CInputJoyPad::KeyConfigSave()
{
	FILE *pFile = NULL;			//�t�@�C���|�C���^�[�錾

	//�t�@�C�����J��
	pFile = fopen("data\\FILE\\KeyConfigData.txt", "w");

	if (pFile == nullptr)
	{//�J���Ȃ��������p
		assert(false);
	}

	//�O���̏o��
	fprintf(pFile, "#==============================================================================\n");
	fprintf(pFile, "#\n");
	fprintf(pFile, "# �wKeyConfigData�x�X�N���v�g�t�@�C�� [KeyConfigData.txt]\n");
	fprintf(pFile, "# Author : ���j�[�m\n");
	fprintf(pFile, "#\n");
	fprintf(pFile, "#==============================================================================\n\n");

	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# �L�[�R���t�B�O�̏��(4�R���g���[���[��)\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n\n");

	//�ۑ�����R���g���[���[��For��
	for (int nCntJoypad = 0; nCntJoypad < JOYPAD_DATA_MAX; nCntJoypad++)
	{
		//�e�L�X�g�ɃR���g���[���[�̃L�[�R���t�B�O����̏o�͂̎n�܂�
		fprintf(pFile, "ONE_MINUTES_LOADING\n\n");

		//�ۑ�����Key��For��
		for (int nCntKey = 0; nCntKey < KEY_CONFIG_SUPPORTED_KEY_NUMBER; nCntKey++)
		{
			//Key����̏o��
			fprintf(pFile, "KEY = %d\n",(int)m_KeyConfig[nCntJoypad][nCntKey]);
		}

		//�e�L�X�g�ɃR���g���[���[�̃L�[�R���t�B�O����̏o�͂̏I���
		fprintf(pFile, "\nONE_MINUTES_LOADING_END\n\n");
	}

	//�I���e�L�X�g�̏o��
	fprintf(pFile, "END_SCRIPT		# ���̍s�͐�Ώ����Ȃ����ƁI\n");

	//�t�@�C�������
	fclose(pFile);
}
