//**************************************************************
//
// 難易度システム
// Author : Tomidokoro Tomoki
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "difficult.h"
#include "object2d.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CDifficult::CDifficult() :
	CObject(CTaskGroup::LEVEL_3D_1)
{
	m_time = 0;
	m_gameLevel = 0;
	m_enemyLevel = 0;
	m_isCount = true;
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CDifficult::~CDifficult()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CDifficult::Init()
{
	m_bar = CObject2d::Create(CTaskGroup::EPriority::LEVEL_2D_UI);
	m_bar->SetAnchor(CObject2d::EAnchor::ANCHOR_LEFT);
	m_bar->SetSize(D3DXVECTOR3(50.0f, 10.0f, 0.0f));
	m_bar->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f));
	m_bar->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_bar->SetTexture("DIFFICULT");
	m_bar->SetTex(PositionVec4(0.0f,0.2f,0.0f,1.0f));

	CObject::Init();

	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CDifficult::Update()
{
	if (m_isCount)
	{// 時間を経過させる
		m_time++;
	}

	float size = 0.2f;
	float gage1 = 0.0f;

	if (m_time >= 3000)
	{
		m_gameLevel++;
		m_enemyLevel = m_gameLevel * 10;
		m_time = 0;
	}

	if (m_gameLevel >= 3.0f)
	{
		gage1 = 3.0f * size;
	}
	else
	{
		gage1 = m_gameLevel * size;
	}

	float gage2 = m_time * 0.00002f;

	m_bar->SetTex(PositionVec4(gage1 + gage2, size + gage1 + gage2, 0.0f, 1.0f));

	CObject::Update();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CDifficult* CDifficult::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	CDifficult* pDifficult = nullptr;
	pDifficult = new CDifficult;

	if (pDifficult != nullptr)
	{
		pDifficult->Init();
		pDifficult->SetPos(inPos);
		pDifficult->SetRot(inRot);
		pDifficult->SetSize(inSize);
	}

	return pDifficult;
}
