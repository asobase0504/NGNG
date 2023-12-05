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
HRESULT CProcedure::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, const int inNumber)
{
	m_number = inNumber;

	m_size = size;

	// 桁数を数える
	CalDigit();

	m_pos = pos;
	SetPos(m_pos);

	return S_OK;
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

	int cnt = 0;
	for (CNumber* displayNumber : m_pNumber)
	{
		displayNumber->SetPos(D3DXVECTOR3(displayNumber->GetSize().x * 1.75f * ((float)cnt - (m_digit - 1) * 0.5f) + inPos.x, inPos.y, 0.0f));
		cnt++;
	}
}

void CProcedure::SetColor(const D3DXCOLOR & inColor)
{
	for (CNumber* displayNumber : m_pNumber)
	{
		displayNumber->SetColor(inColor);
	}
}

void CProcedure::AddColor(const D3DXCOLOR & inColor)
{
	for (CNumber* displayNumber : m_pNumber)
	{
		displayNumber->SetColor(inColor + displayNumber->GetColor());
	}
}

void CProcedure::SetSize(const D3DXVECTOR3 & inSize)
{
	for (CNumber* displayNumber : m_pNumber)
	{
		displayNumber->SetSize(inSize);
	}
	SetPos(m_pos);
}

void CProcedure::AddSize(const D3DXVECTOR3 & inSize)
{
	for (CNumber* displayNumber : m_pNumber)
	{
		displayNumber->AddSize(inSize);
	}
}

void CProcedure::SetNumber(int inNumber)
{
	m_number = inNumber;
	CalDigit();

	std::vector<int> aPosTexU;		//各桁の数字を格納
	aPosTexU.resize(m_digit);

	{
		int number = inNumber;
		for (int i = m_digit - 1; i >= 0; --i)
		{
			aPosTexU[i] = number % 10;
			number /= 10;
		}
	}

	// テクスチャ座標の設定
	int cnt = 0;
	for (CNumber* displayNumber : m_pNumber)
	{
		displayNumber->SetNumber(aPosTexU[cnt]);
		displayNumber->SetTexPos(10.0f, (float)aPosTexU[cnt]);
		cnt++;
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CProcedure *CProcedure::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int number)
{
	CProcedure *pProcedure;
	pProcedure = new CProcedure;

	assert(pProcedure != nullptr);

	pProcedure->Init(pos, size, number);

	return pProcedure;
}

//--------------------------------------------------
// 桁数を数える
//--------------------------------------------------
void CProcedure::CalDigit()
{
	m_digit = 0;
	int number = m_number;
	do
	{
		m_digit++;
		number *= 0.1f;
	} while (number != 0);

	int diff = m_digit - m_pNumber.size();
	while (diff != 0)
	{
		if (diff < 0)
		{ // 桁が過剰時
			m_pNumber.back()->Uninit();
			m_pNumber.pop_back();	// 削除
			diff++;
		}
		else
		{ // 桁が足りない時
			CNumber* number = CNumber::Create();
			m_pNumber.push_back(number);	// 追加
			number->SetSize(m_size);
			SetEndChildren(number);
			diff--;
		}
	}
	SetPos(m_pos);
}