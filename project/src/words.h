//============================
//
//  もじ設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _WORDS_H_
#define _WORDS_H_

#include "object2d.h"
#include "font.h"

class CWords : public CObject2d
{
public:
	CWords(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_BG);
	~CWords() override;

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;		// 描画
	static CWords *CWords::Create(const char * Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type);

	void SetSize(D3DXVECTOR3 Size) { m_size = Size; };
	D3DXVECTOR3 GetSize() { return m_size; };

private:
	void Setwords(const char*Text, CFont::FONT Type);

	int  m_nTimer;
	float m_nScale;
	D3DXVECTOR3 m_size;
	const char *m_words;
	LPD3DXFONT m_pFont = nullptr;
	HFONT  m_hFont;
	std::string m_Text;
	std::string m_ALLText;
	LPDIRECT3DTEXTURE9 m_pTex;
};
#endif
