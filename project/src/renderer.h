//**************************************************************
//
// レンダラー
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _RENDERER_H_			// このマクロ定義がされてなかったら
#define _RENDERER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// 定数定義
//==============================================================
namespace
{
	// ウインドウのクラス名
	LPCTSTR CLASS_NAME = _T("AppClass");
	// ウインドウのキャプション名
	LPCTSTR WINDOW_NAME = _T("Last Samurai");
}

const int SCREEN_WIDTH = 1280;	// スクリーンの幅
const int SCREEN_HEIGHT = 720;	// スクリーンの高さ

#ifdef _DEBUG
int GetTime(void);
#endif // _DEBUG
//==============================================================
// 前方宣言
//==============================================================
class CLight;
class CCamera;

//==============================================================
// 描画のクラス
//==============================================================
class CRenderer
{
public:	// シングルトン用のインスタンス
	static CRenderer* GetInstance();
private:
	CRenderer();
	static CRenderer* m_renderer;
public:
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	// Getter
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }

private:	// メンバー変数
	LPDIRECT3D9 m_pD3D;				// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト

	CDebugProc* m_debugProc;
};
#endif