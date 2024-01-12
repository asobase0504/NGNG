//**************************************************************
//
// NUMBER
// Author:hamada ryuuga
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "number.h"
#include "application.h"

//--------------------------------------------------------------
// コンストラクト関数
//--------------------------------------------------------------
CNumber::CNumber(CTaskGroup::EPriority list) : CObject2d(list)
{
}

//--------------------------------------------------------------
// デストラクト関数
//--------------------------------------------------------------
CNumber::~CNumber()
{
}

//--------------------------------------------------------------
// 初期化関数
//--------------------------------------------------------------
HRESULT CNumber::Init()
{
	m_myNumber = 0;
	m_speed = 0.0f;
	CObject2d::Init();
	CObject2d::SetTexture("NUMBER");
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	SetTex(PositionVec4(
		0.0f, 0.1f, 0.0f, 1.0f));
	m_isRelease = false;
	m_deathTimar = 0;
	m_isMove = true;
	return S_OK;
}

//--------------------------------------------------------------
// 破棄関数
//--------------------------------------------------------------
void CNumber::Uninit()
{
	CObject2d::Uninit();
}


//--------------------------------------------------------------
// 更新関数
//--------------------------------------------------------------
void CNumber::Update()
{
	CObject2d::Update();

	if (m_isRelease)
	{
		m_deathTimar--;

		m_col.a -= 1.0f / m_deathTimarMax;

		m_pos.y -= 1.0f;

		CObject2d::SetColor(m_col);

		if (m_deathTimar <= 0)
		{
			Uninit();
			return;
		}
	}
	if (m_isMove)
	{
		m_speed += (0.0f - m_speed)* 0.5f;//（目的の値-現在の値）＊減衰係数

		SetTex(PositionVec4(
			0.1f*m_myNumber, 0.1f*m_myNumber + 0.1f, 0.0f + m_speed, 1.0f + m_speed));
	}
}

//--------------------------------------------------------------
// 描画関数
//--------------------------------------------------------------
void CNumber::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();

	// 新規深度値 <= Zバッファ深度値 (初期設定)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//--------------------------------------------------------------
// 生成関数
//--------------------------------------------------------------
CNumber *CNumber::Create()
{
	CNumber * pObject = nullptr;
	pObject = new CNumber();

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//--------------------------------------------------------------
// けすまでの時間設定関数
//--------------------------------------------------------------
void CNumber::ReleaseTimer(int nTimar)
{
	m_deathTimar = nTimar;
	m_deathTimarMax = m_deathTimar;
	m_isRelease = true;
}
