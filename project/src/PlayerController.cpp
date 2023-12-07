//**************************************************************
// 
// プレイヤーからの入力命令クラス
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
// コンストラクタ
//--------------------------------------------------------------
CPlayerController::CPlayerController(int inInputIndex)
{
	m_nInputIdx = inInputIndex;
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CPlayerController::~CPlayerController()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CPlayerController::Init()
{
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CPlayerController::Uninit()
{
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CPlayerController::Update()
{
}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
D3DXVECTOR3 CPlayerController::Move()
{
	CInput* input = CInput::GetKey();

	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (input == nullptr)
	{
		return moveInput;
	}

	// 移動
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
// ジャンプ
//--------------------------------------------------------------
bool CPlayerController::Jump()
{
	CInput* input = CInput::GetKey();

	bool m_isjump = false;

	if (input == nullptr)
	{
		return m_isjump;
	}

	// ジャンプ
	if (input->Trigger(KEY_SPACE, -1))
	{
		m_isjump = true;
	}

	return m_isjump;
}

//--------------------------------------------------------------
// ダッシュ
//--------------------------------------------------------------
bool CPlayerController::Dash(bool dash)
{
	CInput* input = CInput::GetKey();

	if (input == nullptr)
	{
		return dash;
	}

	// ダッシュ
	if (input->Trigger(DIK_LCONTROL, -1))
	{
		dash = !dash;
	}

	return dash;
}

//--------------------------------------------------------------
// スキル1
//--------------------------------------------------------------
bool CPlayerController::Skill_1()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// スキルの使用
	if (input->Press(MOUSE_INPUT_LEFT))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// スキル2
//--------------------------------------------------------------
bool CPlayerController::Skill_2()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// スキルの使用
	if (input->Press(MOUSE_INPUT_RIGHT))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// スキル3
//--------------------------------------------------------------
bool CPlayerController::Skill_3()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// スキルの使用
	if (input->Press(KEY_SHIFT))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// スキル4
//--------------------------------------------------------------
bool CPlayerController::Skill_4()
{
	CInput* input = CInput::GetKey();

	bool isSkill = false;

	if (input == nullptr)
	{
		return isSkill;
	}

	// スキルの使用
	if (input->Press(DIK_R, -1))
	{
		isSkill = true;
	}

	return isSkill;
}

//--------------------------------------------------------------
// アイテムを取得する処理
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

			itemModel->Uninit();	// 消去
			item.erase(it);

			return itemModel->GetID();
		}
	}

	return -1;
}