//**************************************************
// 
// フォント
// Author  : HamadaRyuuga
// Author  : Yuda Kaito
// 
//**************************************************
#ifndef _FONT_H_	//このマクロ定義がされてなかったら
#define _FONT_H_	//２重インクルード防止のマクロ定義

//==================================================
// 定義
//==================================================
class CFont
{
public: /* 定義 */
	enum FONT
	{
		FONT_MYOUTYOU = 0,
		FONT_SOUEIKAKU,
		FONT_MAX,
		FONT_NONE,	// 使用しない
	};

	static const char* s_FileName[];	// ファイルパス

	static const char* s_FontName[];	// ファイルパス
public:
	CFont();		// デフォルトコンストラクタ
	~CFont();	// デストラクタ

public: /* メンバ関数 */
	static void Load(FONT inTexture);		// 指定の読み込み
	static void ReleaseAll();				// 全ての破棄
	static void Release(FONT inTexture);	// 指定の破棄
	static LPDIRECT3DTEXTURE9 GetFont(std::string words,FONT inTexture);	// 情報の取得

private: /* メンバ関数 */
	static void LoadWords(std::string inWords, FONT inTexture);
private: /* メンバ変数 */

	static std::array<HFONT, FONT_MAX>  m_hFont;
	static std::array<LOGFONT, FONT_MAX> m_lf;
	static std::array<LPDIRECT3DTEXTURE9, FONT_MAX> m_texFont;	// テクスチャの情報
};

#endif // !_FONT_H_

