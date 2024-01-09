//=============================================================================
//
// ���͏��� [directjoypad.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUTJOYPAD_H_		//���̃}�N����`������Ȃ�������
#define _INPUTJOYPAD_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "DirectInput.h"
#include "inputkeydata.h"

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputJoyPad : public CDirectInput
{

private:
	static const int MAX_JOY_KEY = 32;		//�W���C�p�b�h�̎g���ĂȂ��L�[���܂߂��ő吔
	static const int JOYPAD_DATA_MAX = 4;	//�����ڑ��\�ő吔
	static const int KEY_CONFIG_SUPPORTED_KEY_NUMBER = 13; //�L�[�R���t�B�O�Ή��̃L�[��
	static const int LINE_MAX_READING_LENGTH = 256; //�ǂݍ��ݍۂ�1�s������̍ő啶����
	static const int DEVICE_ADDITIONAL_INTERVAL_EXECUTING_APP = 120; //�A�v�����s���̃f�o�C�X�ǉ��Ԋu
	static const int DIRECTION_COUNT_OF_STICK_AND_CROSS = 8;//�X�e�B�b�N�Ə\���L�[�̕�����

	//�W���C�p�b�h�̂ЂƂɕK�v�ȏ��̍\����
	struct SJoyPad
	{
		LPDIRECTINPUTDEVICE8 pInputDevice;							//���̓f�o�C�X�ւ̃|�C���^
		DIJOYSTATE aKeyState;										//�W���C�p�b�h�̃v���X���
		DIJOYSTATE aKeyStateTrigger;								//�W���C�p�b�h�̃g���K�[���
		DIJOYSTATE aKeyStateRelease;								//�W���C�p�b�h�̃����[�X���
		bool bOldKeyTrigger[DIRECTION_COUNT_OF_STICK_AND_CROSS];	//�e�X�e�B�b�N�Ə\���L�[�̕����������ꂽ���ǂ����g���K�[			
		bool bOldKeyRelease[DIRECTION_COUNT_OF_STICK_AND_CROSS];	//�e�X�e�B�b�N�Ə\���L�[�̕����������ꂽ���ǂ��������[�X
		DirectJoypad aOldKeyTrigger;								//�O�񉟂��ꂽ�g���K�[�L�[�̎��
		DirectJoypad aOldKeyRelease;								//�O�񉟂��ꂽ�����[�X�L�[�̎��
		int nCrossPressRot;											//�W���C�p�b�h�̏\���L�[�̉�����Ă������
	};

public:
	CInputJoyPad();
	~CInputJoyPad()override;
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;		//�W���C�p�b�h�̏�����
	void Uninit(void)override;									//�W���C�p�b�h�̏I������
	void Update(void)override;									//�W���C�p�b�h�̍X�V����

	//���̓f�o�C�X�̓o�^�֐�
	HRESULT JoyPadDeviceRegistration(HWND hWnd);

	//���̓f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECTINPUTDEVICE8 GetInputDevice(int nNum) { return m_JoyPadData[nNum].pInputDevice; }

	//���̓f�o�C�X�ւ̃|�C���^�̐ݒ� (�Ԃ�l�͓o�^�����ۂ̔z��ԍ�)
	int SetInputDevice(LPDIRECTINPUTDEVICE8 pInputDeviceint);

	//���ݐڑ�����Ă���W���C�p�b�h�̐��̎擾
	int GetJoyPadNumMax() { return m_nJoyNumCnt; }

	//*�ڑ����m�F���ɍs���R�[���o�b�N�֐�
	//�f�o�C�X���m�F�ł�������𐶐�����R�[���o�b�N�֐�
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	//�m�F���o�����W���C�p�b�h�̃X�e�B�b�N�̌X���̒l�̕��ݒ�
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	//*

	bool GetPress(DirectJoypad eKey, int nNum);				//�v���X����
	bool GetTrigger(DirectJoypad eKey, int nNum);			//�g���K�[����
	bool GetRelease(DirectJoypad eKey, int nNum);			//�����[�X����
	bool GetCrossPress(DirectJoypad eKey, int nNum);		//�\���L�[�v���X����
	bool GetCrossTrigger(DirectJoypad eKey, int nNum);	    //�\���L�[�g���K�[����
	bool GetCrossRelease(DirectJoypad eKey, int nNum);	    //�\���L�[�����[�X����
	bool GetPressAll(DirectJoypad eKey);			//�I�[���v���X����	�i�L�[�w�肠��A�v���C���[�w��Ȃ��j
	bool GetTriggerAll(DirectJoypad eKey);			//�I�[���g���K�[�����i�L�[�w�肠��A�v���C���[�w��Ȃ��j
	bool GetReleaseAll(DirectJoypad eKey);			//�I�[�������[�X�����i�L�[�w�肠��A�v���C���[�w��Ȃ��j
	bool GetPressAll(int nNum);						//�I�[���v���X����	�i�L�[�w��Ȃ��A�v���C���[�w�肠��j
	bool GetTriggerAll(int nNum);					//�I�[���g���K�[�����i�L�[�w��Ȃ��A�v���C���[�w�肠��j
	bool GetReleaseAll(int nNum);					//�I�[�������[�X�����i�L�[�w��Ȃ��A�v���C���[�w�肠��j
	bool GetPressAll();								//�I�[���v���X����	�i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
	bool GetTriggerAll();							//�I�[���g���K�[�����i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
	bool GetReleaseAll();							//�I�[�������[�X�����i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
	D3DXVECTOR3 GetJoyStickData(int nNum, bool bleftandright = false);			//�W���C�X�e�B�b�N�̌X���l��Ԃ�(true  = �E�Afalse = ��)
	int GetCross(int nNum = 0) { return m_JoyPadData[nNum].nCrossPressRot; }	//�W���C�p�b�h�̏\���L�[�̉�����Ă������(��@45���Ȃ�)

	void SetKeyConfig(int nPlayerNum, DirectJoypad OldKey, DirectJoypad NewKey); //�L�[�̓���ւ�
	void KeyConfigLoading();			//�L�[�R���t�B�O�̓ǂݍ���
	void KeyConfigSave();				//�L�[�R���t�B�O�̕ۑ�

	//�A�v���̎��s��Ƀf�o�C�X��o�^����ۂɐڑ�����Ă���f�o�C�X���̈ꎞ�ۑ���Set,Get,Add
	void SetAfterAppExecutionJoyNumCnt(int nCnt) { m_nAfterAppExecutionJoyNumCnt = nCnt; }
	int GetAfterAppExecutionJoyNumCnt() { return m_nAfterAppExecutionJoyNumCnt; }
	void AddAfterAppExecutionJoyNumCnt() { m_nAfterAppExecutionJoyNumCnt++; }

	//�ꎞ�ۑ��p�f�o�C�X�|�C���^�̔z��ASet
	void SetDevicePointer(LPDIRECTINPUTDEVICE8 pDevice) { m_apDevice[m_nAfterAppExecutionJoyNumCnt] = pDevice; m_nAfterAppExecutionJoyNumCnt++; }

	void IntermediateReception(bool bIR = false) { m_bIntermediateReception = bIR; }	//�f�o�C�X�̓r�����m�̃I���I�t
	bool GetIntermediateReception() { return m_bIntermediateReception; }		//���݃f�o�C�X�̓r�����m���s���Ă��邩�ǂ���

private:
	SJoyPad m_JoyPadData[JOYPAD_DATA_MAX];		//�W���C�p�b�h�̂ЂƂɕK�v�ȏ��̍\����
	DirectJoypad m_AllOldKeyTrigger;			//�S�W���C�p�b�h���ʂ̑O�񂳂ꂽ�g���K�[�L�[
	DirectJoypad m_AllOldKeyRelease;			//�S�W���C�p�b�h���ʂ̑O�񂳂ꂽ�����[�X�L�[
	int m_nJoyNumCnt;							//���ݐڑ��̐ڑ���
	int m_nAfterAppExecutionJoyNumCnt;			//�A�v���̎��s��Ƀf�o�C�X��o�^����ۂɐڑ�����Ă���f�o�C�X���̈ꎞ�ۑ�
	DirectJoypad m_KeyConfig[JOYPAD_DATA_MAX][KEY_CONFIG_SUPPORTED_KEY_NUMBER]; //�L�[�R���t�B�O�̑Ή��p�i���̕ϐ����̐��l�ɂ���ĔF������L�[���ς��j
	HWND m_hWnd;								//�E�B���h�E�n���h���̕ۑ�
	int m_nDeviceAdditionalIntervalExecutingApp;//�A�v�����s���̃f�o�C�X�ǉ��Ԋu
	LPDIRECTINPUTDEVICE8 m_apDevice[JOYPAD_DATA_MAX]; //�f�o�C�X�|�C���^�̈ꎞ�ۑ��ꏊ
	bool m_bIntermediateReception;	//�r���f�o�C�X��t
};
#endif