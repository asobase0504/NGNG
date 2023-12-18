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
	CObject::Init();

	return S_OK;
}

//--------------------------------------------------------------
// 初期化(オーバーロード)
//--------------------------------------------------------------
HRESULT CDifficult::Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	CObject::Init();

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CDifficult::Uninit()
{
	CObject::Uninit();
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

	if (m_time >= 300)
	{
		m_gameLevel++;
		m_enemyLevel = m_gameLevel * 10;
		m_time = 0;
	}

	CObject::Update();
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CDifficult::Draw()
{
	CObject::Draw();
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
		pDifficult->Init(inPos, inRot, inSize);
		pDifficult->SetPos(inPos);
		pDifficult->SetRot(inRot);
		pDifficult->SetSize(inSize);
	}

	return pDifficult;
}
