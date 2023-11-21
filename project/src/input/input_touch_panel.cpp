//=============================================================================
//
// ���͏��� [input_touch_panel.cpp]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "input_touch_panel.h"

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInputTouchPanel::CInputTouchPanel()
{
	ZeroMemory(m_TouchPanel,sizeof(m_TouchPanel));
	m_ScreenSize = {};
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInputTouchPanel::~CInputTouchPanel()
{
}

//*************************************************************************************
//�X�V
//*************************************************************************************
void CInputTouchPanel::Update()
{
	for (int i = 0; i < MAX_TOUCH_PANEL; i++)
	{//�S�X�V
		if (!m_TouchPanel[i].bUse)
		{//�g�p��ԂɂȂ�����
			continue;
		}


		if (!m_TouchPanel[i].bFirstTrigger && m_TouchPanel[i].bTrigger)
		{//��i�K�ڃg���K�[�̑r��
			m_TouchPanel[i].bTrigger = false;
		}

		if (m_TouchPanel[i].bFirstTrigger && !m_TouchPanel[i].bTrigger)
		{//��i�K�ڃg���K�[�̑r��
			m_TouchPanel[i].bFirstTrigger = false;
			m_TouchPanel[i].bTrigger = true;
		}
	}
}

//*************************************************************************************
//�v���X����
//*************************************************************************************
bool CInputTouchPanel::GetPress(int nNum)
{
	return m_TouchPanel[nNum].bUse;
}

//*************************************************************************************
//�g���K�[����
//*************************************************************************************
bool CInputTouchPanel::GetTrigger(int nNum)
{
	//NULL�`�F�b�N
	if (!m_TouchPanel[nNum].bUse)
	{
		return false;
	}

	//�g���K�[�`�F�b�N
	if (m_TouchPanel[nNum].bTrigger)
	{
		return true;
	}
	return false;
}

//*************************************************************************************
//�^�b�`Pos��Get
//*************************************************************************************
D3DXVECTOR3 CInputTouchPanel::GetTouchPos(int nNum)
{
	return m_TouchPanel[nNum].Pos;
}

//*************************************************************************************
//�^�b�`Vec��Get
//*************************************************************************************
D3DXVECTOR3 CInputTouchPanel::GetTouchVec(int nNum)
{
	return m_TouchPanel[nNum].Vec;
}

//*************************************************************************************
//�f�[�^�̐ݒ�
//*************************************************************************************
void CInputTouchPanel::SetTouchData(TOUCHINPUT *pTouchData, int nCntData)
{
	//�f�[�^�̌�
	int nCntMax = nCntData;

	//�ۑ��\���𒴂��Ă��Ȃ���
	if (nCntMax >= MAX_TOUCH_PANEL)
	{
		nCntMax = MAX_TOUCH_PANEL - 1;
	}

	//�f�[�^�̕ۑ��͂Ȃ�
	if (nCntMax < 0)
	{
		return;
	}

	//�V�K�o�^�̗L��
	bool bNewRegistration = false;

	//�f�[�^�̍X�V
	for (int i = 0; i < MAX_TOUCH_PANEL; i++)
	{
		//Use�`�F�b�N
		if (m_TouchPanel[i].bUse == false)
		{
			continue;
		}

		//�^�b�`ID�̌��m
		if (m_TouchPanel[i].TouchData.dwID != pTouchData[nCntMax].dwID)
		{
			continue;
		}

		//�^�b�`�t���O���m
		if (pTouchData[nCntMax].dwFlags & TOUCHEVENTF_UP)
		{//�^�b�`���̃��X�g
			m_TouchPanel[i].bUse = false;
			//�V�K�o�^�͕K�v�Ȃ�
			bNewRegistration = true;
			break;
		}
		else if (pTouchData[nCntMax].dwFlags & TOUCHEVENTF_MOVE)
		{//�t���b�v���̐ݒ�

			//��O�̈ʒu�̕ۑ�
			m_TouchPanel[i].OldPos = m_TouchPanel[i].Pos;

			//���݂̈ʒu��ۑ�
			m_TouchPanel[i].Pos.x = RateCalculation((float)pTouchData[nCntMax].x / 100.0f, m_ScreenSize.x, SM_CXSCREEN);
			m_TouchPanel[i].Pos.y = RateCalculation((float)pTouchData[nCntMax].y / 100.0f, m_ScreenSize.y, SM_CYSCREEN);

			//2�̃x�N�g���𑫂��č����x�N�g�����쐬���܂�
			D3DXVECTOR3 combinedVector = m_TouchPanel[i].OldPos + m_TouchPanel[i].Pos;

			//�����x�N�g���𐳋K�����܂�
			D3DXVec3Normalize(&combinedVector, &combinedVector);

			//�����x�N�g���̕ۑ�
			m_TouchPanel[i].Vec = combinedVector;

			//�V�K�o�^�͕K�v�Ȃ�
			bNewRegistration = true;
			break;
		}
		//�t���O�̃��X�g
		m_TouchPanel[i].bUse = false;
	}

	//�f�[�^�̐V�K�ۑ�
	for (int i = 0; i < MAX_TOUCH_PANEL; i++)
	{
		//�V�K�o�^�̗L��
		if (bNewRegistration)
		{
			break;
		}

		//�^�b�`�n���h����null�`�F�b�N
		if (m_TouchPanel[i].bUse == true)
		{
			continue;
		}

		//�g�p��Ԃɂ���
		m_TouchPanel[i].bUse = true;
		//�g���K�[�̋N��
		m_TouchPanel[i].bTrigger = false;
		m_TouchPanel[i].bFirstTrigger = true;
		//�f�[�^�̕ۑ�
		m_TouchPanel[i].TouchData = pTouchData[nCntMax];
		//���݂̈ʒu��ۑ�
		m_TouchPanel[i].Pos.x = RateCalculation((float)pTouchData[nCntMax].x / 100.0f, m_ScreenSize.x, SM_CXSCREEN);
		m_TouchPanel[i].Pos.y = RateCalculation((float)pTouchData[nCntMax].y / 100.0f, m_ScreenSize.y, SM_CYSCREEN);
		//��O�̈ʒu�̓o�^
		m_TouchPanel[i].OldPos = m_TouchPanel[i].Pos;
		//�x�N�g���ۑ�
		m_TouchPanel[i].Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//�o�^����
		break;
	}

	//���̃f�[�^�̕ۑ�
	SetTouchData(pTouchData, nCntMax -1);
}

//*************************************************************************************
//�����v�Z
//*************************************************************************************
float CInputTouchPanel::RateCalculation(float fMax, float fWnMax, int nbet)
{
	//��ʃT�C�Y
	int nScreenMax = GetSystemMetrics(nbet);

	//�����v�Z
	float fRate = (float)(fMax / nScreenMax);

	//����
	float fResult = fWnMax * fRate;

	return fResult;
}
