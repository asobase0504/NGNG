//**************************************************************
//
// デバック表示クラス(debug_proc.cpp)
// Author : 唐�ｱ結斗
// 概要 : デバック表示生成を行う
//
//**************************************************************

//==============================================================
// インクルード
//==============================================================
#include "debug_proc.h"
#include "application.h"
#include "renderer.h"

//==============================================================
// 静的メンバ変数の定義
//==============================================================
LPD3DXFONT CDebugProc::m_font = nullptr;	// フォント情報
std::string CDebugProc::m_str;				// 登録文字列
bool CDebugProc::m_use = false;	// フォント情報

//--------------------------------------------------------------
// 文字列の登録
// Author : 唐�ｱ結斗
// 概要 : 引数に設定された文字列を登録する
//--------------------------------------------------------------
void CDebugProc::Print(const char *pFormat, ...)
{
	if (!m_use)
	{
		return;
	}

	// 変数
	char aStrCpy[0xfff] = {};

	// リストの作成
	va_list args;
	va_start(args, pFormat);
	vsprintf(&aStrCpy[0], pFormat, args);
	va_end(args);

	m_str += aStrCpy;
}

//--------------------------------------------------------------
// 文字列の描画
// Author : 唐�ｱ結斗
// 概要 : 登録された文字列を描画する
//--------------------------------------------------------------
void CDebugProc::Draw(void)
{
	if (!m_use)
	{
		return;
	}

	RECT rect = { 0, 0, 1280, 720 };

	// テキスト描画
	m_font->DrawText(NULL, m_str.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x00));
	m_str.clear();
}

//--------------------------------------------------------------
// コンストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス生成時に行う処理
//--------------------------------------------------------------
CDebugProc::CDebugProc()
{
}

//--------------------------------------------------------------
// デストラクタ
// Author : 唐�ｱ結斗
// 概要 : インスタンス終了時に行う処理
//--------------------------------------------------------------
CDebugProc::~CDebugProc()
{
}

//--------------------------------------------------------------
// 初期化
// Author : 唐�ｱ結斗
// 概要 : メンバ変数の初期値を設定
//--------------------------------------------------------------
void CDebugProc::Init()
{// デバイスへのポインタの取得
#ifdef _DEBUG
	m_use = true;
#endif // _DEBUG

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("HGRSGU.TTC"), &m_font);
}

//--------------------------------------------------------------
// 終了
// Author : 唐�ｱ結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//--------------------------------------------------------------
void CDebugProc::Uninit()
{
	if (!m_use)
	{
		return;
	}

	// デバッグ情報表示用フォントの破棄
	if (m_font != nullptr)
	{
		m_font->Release();
		m_font = nullptr;
	}
}