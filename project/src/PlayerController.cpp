//**************************************************************
// 
// �v���C���[����̓��͖��߃N���X
// Author YudaKaito
// 
//**************************************************************
//==============================================================
// include
//==============================================================
#include "PlayerController.h"
#include "application.h"
#include "input.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CPlayerController::CPlayerController(int inInputIndex)
{
	m_nInputIdx = inInputIndex;
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CPlayerController::~CPlayerController()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CPlayerController::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CPlayerController::Uninit()
{
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CPlayerController::Update()
{
}

//--------------------------------------------------------------
// �ړ�
//--------------------------------------------------------------
D3DXVECTOR3 CPlayerController::Move()
{
	CInput* input = CInput::GetKey();

	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (input == nullptr)
	{
		return moveInput;
	}

	// �ړ�
	if (input->Press(KEY_UP, -1))
	{
		moveInput.z += 1.0f;
	}
	if (input->Press(KEY_LEFT, -1))
	{
		moveInput.x -= 1.0f;
	}
	if (input->Press(KEY_DOWN, -1))
	{
		moveInput.z -= 1.0f;
	}
	if (input->Press(KEY_RIGHT, -1))
	{
		moveInput.x += 1.0f;
	}

	if (moveInput.x != 0.0f || moveInput.y != 0.0f)
	{
		D3DXVec3Normalize(&moveInput, &moveInput);
	}

	return moveInput;
}

//--------------------------------------------------------------
// �W�����v
//--------------------------------------------------------------
bool CPlayerController::Jump()
{
	CInput* input = CInput::GetKey();

	bool m_isjump = false;

	if (input == nullptr)
	{
		return m_isjump;
	}

	// �W�����v
	if (input->Trigger(KEY_SPACE, -1))
	{
		m_isjump = true;
	}

	return m_isjump;
}

//--------------------------------------------------------------
// �_�b�V��
//--------------------------------------------------------------
bool CPlayerController::Dash()
{
	CInput* input = CInput::GetKey();

	bool isDash = false;

	if (input == nullptr)
	{
		return isDash;
	}

	// �_�b�V��
	if (input->Press(DIK_LCONTROL, -1))
	{
		isDash = true;
	}

	return isDash;
}

//--------------------------------------------------------------
// �X�L��1
//--------------------------------------------------------------
bool CPlayerController::Skill_1()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// �X�L���̎g�p
	if (input->Trigger(MOUSE_INPUT_LEFT))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// �X�L��2
//--------------------------------------------------------------
bool CPlayerController::Skill_2()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// �X�L���̎g�p
	if (input->Trigger(MOUSE_INPUT_RIGHT, -1))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// �X�L��3
//--------------------------------------------------------------
bool CPlayerController::Skill_3()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// �X�L���̎g�p
	if (input->Trigger(KEY_SHIFT, -1))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// �X�L��4
//--------------------------------------------------------------
bool CPlayerController::Skill_4()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// �X�L���̎g�p
	if (input->Trigger(DIK_R, -1))
	{
		isSkill = true;
	}

	return isSkill;
}
