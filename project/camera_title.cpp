//**************************************************************
//
// ゲーム中のカメラ
// Author : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "camera_title.h"
#include "input.h"

//==============================================================
// 定数
//==============================================================
const float CTitleCamera::DISTANCE = 195.0f;

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CTitleCamera::CTitleCamera()
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CTitleCamera::~CTitleCamera()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CTitleCamera::Init()
{
	CCamera::Init();
	m_rot = D3DXVECTOR3(0.45f, 0.0f, 0.0f);
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CTitleCamera::Update()
{
	CCamera::Update();

	m_posR = D3DXVECTOR3(0.0f, 100.0f, DISTANCE);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -DISTANCE);

	D3DXVECTOR3 mouseMove = CInput::GetKey()->GetMouseMove();

	m_rot.x += mouseMove.y * 0.0025f;
	m_rot.y += mouseMove.x * 0.0025f;

	if (m_rot.x >= (D3DX_PI * 0.5f))
	{
		m_rot.x = (D3DX_PI * 0.5f) * 0.9f;
	}
	if (m_rot.x <= (-D3DX_PI * 0.5f))
	{
		m_rot.x = -(D3DX_PI * 0.5f) * 0.9f;
	}

	// 計算用マトリックス
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot, mtxTrans;

	D3DXMatrixIdentity(&mtxWorld);	// 行列初期化関数

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);		// 行列回転関数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);						// 行列掛け算関数 
	
	// D3DXVECTOR3に反映
	D3DXVec3TransformCoord(&m_posV, &m_posV, &mtxWorld);
	// D3DXVECTOR3に反映
	D3DXVec3TransformCoord(&m_posR, &m_posR, &mtxWorld);
}
