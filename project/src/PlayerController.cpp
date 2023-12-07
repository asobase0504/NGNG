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
#include "player.h"
#include "application.h"
#include "input.h"

#include "item_manager.h"
#include "item_model.h"
#include "collision.h"

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
bool CPlayerController::Dash(bool dash)
{
	CInput* input = CInput::GetKey();

	if (input == nullptr)
	{
		return dash;
	}

	// �_�b�V��
	if (input->Trigger(DIK_LCONTROL, -1))
	{
		dash = !dash;
	}

	return dash;
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
	if (input->Press(MOUSE_INPUT_LEFT))
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
	if (input->Press(MOUSE_INPUT_RIGHT))
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
	if (input->Press(KEY_SHIFT))
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
	if (input->Press(DIK_R, -1))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// �A�C�e�����擾���鏈��
//--------------------------------------------------------------
int CPlayerController::TakeItem()
{
	CInput* input = CInput::GetKey();

	if (input->Trigger(DIK_F, -1))
	{
		std::list<CItemModel*>& item = CItemManager::GetInstance()->GetPopItemModel();
		int size = item.size();

		for (auto it = item.begin(); it != item.end();)
		{
			CItemModel* itemModel = *it;
			if (!((CCollisionCylinder*)(m_toOrder->GetCollision())->ToSphere(itemModel->GetCollision())))
			{
				it++;
				continue;
			}

			itemModel->Uninit();	// ����
			item.erase(it);

			return itemModel->GetID();
		}
	}

	return -1;
}