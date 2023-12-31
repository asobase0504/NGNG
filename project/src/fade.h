//**************************************************************
//
// フェード
// Author : Hamada Ryuuga
//
//**************************************************************
#ifndef _FADE_H_
#define _FADE_H_

//==============================================================
// include
//==============================================================
#include "application.h"
#include "renderer.h"
#include "object2d.h"

//==============================================================
// 前方宣言
//==============================================================
class  CMotion;

//==============================================================
// フェードクラス
//==============================================================
class CFade : public CObject2d
{
public:
	CFade();
	~CFade();

	//画面(モード)の種類
	enum FADE
	{
		FADEIN = 0,
		FADEOUT,
		FADENON,
		FADEMAX
	};

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	FADE* GetFade() { return& m_fade; }

private:
	virtual void Change() = 0;
protected:
	FADE m_fade;
private:
	float m_fadeSp;
	float m_fadeSet;
	bool m_bake;
	CApplication::MODE m_nextMode;
};
#endif