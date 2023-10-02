//**************************************************************
//
// NUMBER
// Author:hamada ryuuga
//
//**************************************************************
#ifndef _NUMBER_H_
#define _NUMBER_H_

//==============================================================
// include
//==============================================================
#include "object2d.h"

//==============================================================
// ƒNƒ‰ƒX
//==============================================================
class CNumber : public CObject2d
{
public:
	CNumber(CTaskGroup::EPriority list = CTaskGroup::LEVEL_2D_UI);
	~CNumber();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CNumber* Create();
	
	void SetSpeed(float Speed) { m_speed = Speed; }
	void SetNumber(int Number) { m_myNumber = Number; }
	void SetMove(bool Move) { m_isMove = Move; }
	
	void ReleaseTimer(int nTimar);

private:
	D3DXCOLOR m_col;
	float m_speed;
	int m_deathTimarMax;
	int m_deathTimar;
	int m_myNumber;
	bool m_isRelease;
	bool m_isMove;
	
};
#endif