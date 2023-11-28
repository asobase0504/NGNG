//=============================================================================
//
// ���͏��� [input_touch_panel.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUT_TOUCH_PANEL_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_TOUCH_PANEL_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "inputkeydata.h"
#include "DirectInput.h"

static const int MAX_TOUCH_PANEL = 5;		//�^�b�`�p�l���̓������m�\��

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputTouchPanel
{
private:
	struct TouchPanel
	{
		TOUCHINPUT TouchData;
		D3DXVECTOR3 Pos;
		D3DXVECTOR3 OldPos;
		D3DXVECTOR3 Vec;
		bool bTrigger;
		bool bFirstTrigger;
		bool bUse;
	};

public:
	CInputTouchPanel();
	~CInputTouchPanel();

	void Update();
	
	bool GetPress(int nNum = 0);					//�v���X����
	bool GetTrigger(int nNum = 0);					//�g���K�[����
	D3DXVECTOR3 GetTouchPos(int nNum = 0);			//�^�b�`Pos��Get
	D3DXVECTOR3 GetTouchVec(int nNum = 0);			//�^�b�`Vec��Get
	void SetTouchData(TOUCHINPUT *pTouchData,int nCntData);		//�f�[�^�̐ݒ�
	float RateCalculation(float fMax,float fWnMax, int nbet);		//�����v�Z
	void SetScreenSize(D3DXVECTOR2 ScreenSize) { m_ScreenSize = ScreenSize; }

private:
	TouchPanel m_TouchPanel[MAX_TOUCH_PANEL];		//�^�b�`�p�l���̂ЂƂɕK�v�ȏ��̍\����
	D3DXVECTOR2 m_ScreenSize;
};
#endif