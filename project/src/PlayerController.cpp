//=========================================
// 
// プレイヤーからの入力命令クラス
// Author YudaKaito
// 
//=========================================
//=========================================
// include
//=========================================
#include "PlayerController.h"
#include "application.h"
#include "input.h"

//-----------------------------------------
// コンストラクタ
//-----------------------------------------
CPlayerController::CPlayerController(int inInputIndex)
{
	m_nInputIdx = inInputIndex;
}

//-----------------------------------------
// デストラクタ
//-----------------------------------------
CPlayerController::~CPlayerController()
{
}

//-----------------------------------------
// 初期化
//-----------------------------------------
HRESULT CPlayerController::Init()
{
	return S_OK;
}

//-----------------------------------------
// 終了
//-----------------------------------------
void CPlayerController::Uninit()
{
}

//-----------------------------------------
// 更新
//-----------------------------------------
void CPlayerController::Update()
{
}

//-----------------------------------------
// 移動
//-----------------------------------------
D3DXVECTOR3 CPlayerController::Move()
{
	CInput* input = CInput::GetKey();

	D3DXVECTOR3 moveInput = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (input == nullptr)
	{
		return moveInput;
	}

	//padの移動
	if (input->Press(KEY_UP, m_nInputIdx))
	{
		moveInput.z += 1.0f;
	}
	if (input->Press(KEY_LEFT, m_nInputIdx))
	{
		moveInput.x -= 1.0f;
	}
	if (input->Press(KEY_DOWN, m_nInputIdx))
	{
		moveInput.z -= 1.0f;
	}
	if (input->Press(KEY_RIGHT, m_nInputIdx))
	{
		moveInput.x += 1.0f;
	}

	//キーボードの移動
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

//-----------------------------------------
// 移動
//-----------------------------------------
float CPlayerController::Jump()
{
	CInput* input = CInput::GetKey();

	float junpInput = 0.0f;

	if (input == nullptr)
	{
		return junpInput;
	}

	//キーボードの移動
	if (input->Press(KEY_SHOT, -1))
	{
		junpInput += 8.0f;
	}

	return junpInput;
}