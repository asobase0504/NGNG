//**************************************************************
//
// NUMBER
// Author:hamada ryuuga
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "number3D.h"
#include "application.h"

//--------------------------------------------------------------
// コンストラクト関数
//--------------------------------------------------------------
CNumber3D::CNumber3D(CTaskGroup::EPriority list) : CObjectPolygon3D(list)
{
}

//--------------------------------------------------------------
// デストラクト関数
//--------------------------------------------------------------
CNumber3D::~CNumber3D()
{
}

//--------------------------------------------------------------
// 初期化関数
//--------------------------------------------------------------
HRESULT CNumber3D::Init()
{
	m_myNumber = 0;
	m_speed = 0.0f;
	CObjectPolygon3D::Init();
	CObjectPolygon3D::SetTexture("NUMBER");
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	SetTex(PositionVec4(0.0f, 0.1f, 0.0f, 1.0f));
	m_isRelease = false;
	m_deathTimar = 0;
	m_isMove = true;
	return S_OK;
}

//--------------------------------------------------------------
// 破棄関数
//--------------------------------------------------------------
void CNumber3D::Uninit()
{
	CObjectPolygon3D::Uninit();
}

//--------------------------------------------------------------
// 更新関数
//--------------------------------------------------------------
void CNumber3D::Update()
{
	CObjectPolygon3D::Update();

	if (m_isRelease)
	{
		m_deathTimar--;

		m_col.a -= 1.0f / m_deathTimarMax;

		m_pos.y -= 1.0f;

		CObjectPolygon3D::SetColor(m_col);

		if (m_deathTimar <= 0)
		{
			Uninit();
			return;
		}
	}
	if (m_isMove)
	{
		m_speed += (0.0f - m_speed) * 0.5f;	//（目的の値-現在の値）＊減衰係数

		SetTex(PositionVec4(0.1f * m_myNumber, 0.1f * m_myNumber + 0.1f, 0.0f + m_speed, 1.0f + m_speed));
	}
}

//--------------------------------------------------------------
// 生成関数
//--------------------------------------------------------------
CNumber3D *CNumber3D::Create()
{
	CNumber3D * pObject = nullptr;
	pObject = new CNumber3D;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//--------------------------------------------------------------
// けすまでの時間設定関数
//--------------------------------------------------------------
void CNumber3D::ReleaseTimer(int nTimar)
{
	m_deathTimar = nTimar;
	m_deathTimarMax = m_deathTimar;
	m_isRelease = true;
}
