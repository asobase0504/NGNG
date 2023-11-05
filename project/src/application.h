//**************************************************************
//
// マネジャー
// Author : 浜田琉雅
// AUthor : Yuda Kaito
//
//**************************************************************
#ifndef _MANEAGER_H_			// このマクロ定義がされてなかったら
#define _MANEAGER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "renderer.h"

//==============================================================
// 前方宣言
//==============================================================
class CRenderer;
class CInput;
class CTexture;
class CMode;
class CFade;
class CSound;
class CTaskGroup;
class CObjectXGroup;
class CColor;

//==============================================================
// マネジャークラス
//==============================================================
class CApplication
{
public:

	static const D3DXVECTOR3 CENTER_POS;	// 中央位置

	//画面(モード)の種類
	enum MODE
	{
		MODE_TITLE = 0,		// タイトル画面
		MODE_GAME,			// ゲーム画面
		MODE_EDIT,			// エディタ画面
		MODE_FADE,			// フェード画面
		MODE_TUTORIAL,		// チュートリアル画面
		MODE_MAX
	};

/* シングルトン */
private: // 静的メンバー変数
	static CApplication* m_pApplication;
public: // 静的関数
	static CApplication* GetInstance();
private:
	CApplication();

public:	// メンバー関数
	~CApplication();

	HRESULT Init(HWND hWnd, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	void SetWcex(WNDCLASSEX inWcex) { m_wcex = inWcex; }
	WNDCLASSEX GetWcex() { return m_wcex; }

	HWND GetWindow() { return m_window; }

	CRenderer* GetRenderer() { return m_renderer; }
	CTexture* GetTexture() { return m_texture; }
	CTaskGroup* GetTaskGroup() { return m_taskGroup; }
	CObjectXGroup* GetObjectXGroup() { return m_objectXGroup; }
	CFade* GetFade() { return m_fade; }

	void SetMode(CApplication::MODE inMode);
	MODE* GetMode() { return &m_modeType; }


	CMode* GetModeClass() { return m_mode; }
	CSound* GetSound() { return m_sound; }
	CColor* GetColor() { return m_color; }

private:
	CTexture* m_texture;
	CRenderer* m_renderer;
	CTaskGroup* m_taskGroup;
	CFade* m_fade;
	CMode* m_mode;
	CSound* m_sound;
	CColor* m_color;
	CObjectXGroup* m_objectXGroup;
	MODE m_modeType;

	HWND m_window;
	WNDCLASSEX m_wcex;
};
#endif
