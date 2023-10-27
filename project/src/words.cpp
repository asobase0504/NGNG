//============================
//
// もじ設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "words.h"

#include "application.h"
#
#include "object2D.h"
#include "font.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CWords::CWords(CTaskGroup::EPriority list) :CObject2d(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CWords::~CWords()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CWords::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	CObject2d::Init();

	return S_OK;
}

//------------------------------------
// 描画
//------------------------------------
void CWords::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();		//デバイスへのポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, GetVtx(), 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの取得
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTex);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//プリミティブ(ポリゴン)数
	pDevice->SetTexture(0, NULL);
}

//------------------------------------
// create
//------------------------------------
CWords *CWords::Create(const char*Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type)
{
	CWords * pObject = nullptr;
	pObject = new CWords();

	if (pObject != nullptr)
	{
		pObject->SetPos(pos);
		pObject->SetSize(Size);
		pObject->Init();
		pObject->Setwords(Text, Type);

	}
	return pObject;
}

//=============================================================================
// GetPos関数
//=============================================================================
void CWords::Setwords(const char*Text, CFont::FONT Type)
{
	std::string Txt = Text;
	if (Txt != "")
	{
		m_pTex = CFont::GetFont(Text, Type);
	}
	else
	{
		m_pTex = nullptr;
		SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}
