//==================================================
// score
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "application.h"

#include "procedure3D.h"
#include "number3D.h"
#include "renderer.h"

//**************************************************
// 静的メンバ変数
//**************************************************

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CProcedure3D::CProcedure3D() :
	CObject(CTaskGroup::LEVEL_SYSTEM),
	m_number(0),
	m_digit(0),
	m_align(CENTER)
{
	m_numberObj.clear();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CProcedure3D::~CProcedure3D()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CProcedure3D::Init()
{
	CObject::Init();
	D3DXMatrixIdentity(&m_mtxTrans);
	Update();			// 初回更新
	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CProcedure3D::Uninit()
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetMtxWorldParent(nullptr);
	}
	CObject::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CProcedure3D::Update()
{
	CObject::Update();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxView;				// 計算用マトリックス
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	//位置を反映
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTrans);

	if (m_mtxWorldParent != nullptr)
	{
		//位置を反映
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_mtxWorldParent);
	}
}

//--------------------------------------------------
// 位置の設定と大きさの設定
//--------------------------------------------------
void CProcedure3D::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);
	D3DXMatrixTranslation(&m_mtxTrans, inPos.x, inPos.y, inPos.z);

	int cnt = 0;
	for (CNumber3D* displayNumber : m_numberObj)
	{
		float posX = 0.0f;
		switch (m_align)
		{
		case CProcedure3D::LEFT:
			posX = displayNumber->GetSize().x * 1.75f * cnt;
			break;
		case CProcedure3D::RIGHT:
			posX = displayNumber->GetSize().x * 1.75f * (cnt - m_digit);
			break;
		case CProcedure3D::CENTER:
			posX = displayNumber->GetSize().x * 1.75f * ((float)cnt - (m_digit - 1) * 0.5f);
			break;
		default:
			assert(false);
			break;
		}

		displayNumber->SetPos(D3DXVECTOR3(posX, 0.0f, 0.0f));
		cnt++;
	}
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void CProcedure3D::SetColor(const D3DXCOLOR & inColor)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetColor(inColor);
	}
}

//--------------------------------------------------
// 色の加算
//--------------------------------------------------
void CProcedure3D::AddColor(const D3DXCOLOR & inColor)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetColor(inColor + displayNumber->GetColor());
	}
}

//--------------------------------------------------
// 大きさの設定
//--------------------------------------------------
void CProcedure3D::SetSize(const D3DXVECTOR3 & inSize)
{
	CObject::SetSize(inSize);
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetSize(inSize);
	}
	SetPos(m_pos);
}

//--------------------------------------------------
// 大きさの加算
//--------------------------------------------------
void CProcedure3D::AddSize(const D3DXVECTOR3 & inSize)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->AddSize(inSize);
	}
}

//--------------------------------------------------
// 値の設定
//--------------------------------------------------
void CProcedure3D::SetNumber(int inNumber)
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
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetNumber(aPosTexU[cnt]);
		displayNumber->SetTexPos(10.0f, (float)aPosTexU[cnt]);
		cnt++;
	}
}

//--------------------------------------------------
// 描画しないを選択する
//--------------------------------------------------
void CProcedure3D::SetDisplay(bool isDisplay)
{
	for (CNumber3D* displayNumber : m_numberObj)
	{
		displayNumber->SetDisplay(isDisplay);
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CProcedure3D *CProcedure3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int number)
{
	CProcedure3D *pProcedure;
	pProcedure = new CProcedure3D;

	assert(pProcedure != nullptr);

	pProcedure->Init();
	pProcedure->SetSize(size);
	pProcedure->SetNumber(number);
	pProcedure->SetPos(pos);

	return pProcedure;
}

//--------------------------------------------------
// 桁数を数える
//--------------------------------------------------
void CProcedure3D::CalDigit()
{
	m_digit = 0;
	int number = m_number;
	do
	{
		m_digit++;
		number *= 0.1f;
	} while (number != 0);

	int diff = m_digit - m_numberObj.size();
	while (diff != 0)
	{
		if (diff < 0)
		{ // 桁が過剰時
			m_numberObj.back()->Uninit();
			m_numberObj.pop_back();	// 削除
			diff++;
		}
		else
		{ // 桁が足りない時
			CNumber3D* number = CNumber3D::Create();
			m_numberObj.push_back(number);	// 追加
			number->SetSize(m_size);
			SetEndChildren(number);
			number->SetMtxWorldParent(&m_mtxWorld);
			diff--;
		}
	}
	SetPos(m_pos);
}