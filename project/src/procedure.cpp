//==================================================
// score
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "application.h"

#include "procedure.h"
#include "number.h"

//**************************************************
// 静的メンバ変数
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CProcedure::CProcedure() : CObject(CTaskGroup::LEVEL_SYSTEM)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CProcedure::~CProcedure()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CProcedure::Init()
{
	return S_OK;
}

//--------------------------------------------------
// 初期化　オーバーロード
//--------------------------------------------------
HRESULT CProcedure::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int digit)
{
	m_digit = digit;
	m_pNumber.resize(m_digit);

	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		m_pNumber[nCnt] = CNumber::Create();
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(size.x * nCnt + pos.x, pos.y, 0.0f));
		m_pNumber[nCnt]->SetSize(size);
	}

	SetPos(pos);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CProcedure::Uninit()
{
	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		if (m_pNumber[nCnt] == nullptr)
		{
			continue;
		}

		m_pNumber[nCnt]->Release();
		m_pNumber[nCnt] = nullptr;
	}

	CObject::Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CProcedure::Update()
{
}

//--------------------------------------------------
// 位置の設定と大きさの設定
//--------------------------------------------------
void CProcedure::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);

	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(m_pNumber[nCnt]->GetSize().x * 1.75f * ((float)nCnt - (m_digit - 1) * 0.5f) + inPos.x, inPos.y, 0.0f));
	}
}

void CProcedure::SetColor(const D3DXCOLOR & inColor)
{
	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		m_pNumber[nCnt]->SetColor(inColor);
	}
}

void CProcedure::AddColor(const D3DXCOLOR & inColor)
{
	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		m_pNumber[nCnt]->SetColor(inColor + m_pNumber[nCnt]->GetColor());
	}
}

void CProcedure::SetSize(const D3DXVECTOR3 & inSize)
{
	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		m_pNumber[nCnt]->SetSize(inSize);
	}
	SetPos(m_pos);
}

void CProcedure::AddSize(const D3DXVECTOR3 & inSize)
{
	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		m_pNumber[nCnt]->AddSize(inSize);
	}
}

void CProcedure::SetNumber(int inNumber)
{
	m_number = inNumber;

	std::vector<int> aPosTexU;		//各桁の数字を格納
	aPosTexU.resize(m_digit);

	{
		int timer = inNumber;
		for (int i = m_digit - 1; i >= 0; --i)
		{
			aPosTexU[i] = timer % 10;
			timer /= 10;
		}
	}

	// テクスチャ座標の設定
	for (int nCnt = 0; nCnt < m_digit; nCnt++)
	{
		m_pNumber[nCnt]->SetNumber(aPosTexU[nCnt]);
		m_pNumber[nCnt]->SetTexPos(10.0f, (float)aPosTexU[nCnt]);
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CProcedure *CProcedure::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int digit)
{
	CProcedure *pTimer;
	pTimer = new CProcedure;

	assert(pTimer != nullptr);

	pTimer->Init(pos, size, digit);

	return pTimer;
}
