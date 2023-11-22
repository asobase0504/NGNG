//============================
//
//  Ç‡Ç∂ê›íËÉwÉbÉ^Å[
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
	CWords(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CWords() override;

	HRESULT Init()override;	// èâä˙âª
	void Draw()override;		// ï`âÊ
	static CWords *CWords::Create(const char * Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type);

private:
	void SetWords(const char*Text, CFont::FONT Type);

private:
	float m_nScale;
	LPDIRECT3DTEXTURE9 m_pTex;
};
#endif
