//**************************************************************
//
// NUMBER
// Author:hamada ryuuga
//
//**************************************************************
#ifndef _NUMBER_3D_H_
#define _NUMBER_3D_H_

//==============================================================
// include
//==============================================================
#include "object_polygon3d.h"

//==============================================================
// クラス
//==============================================================
class CNumber3D : public CObjectPolygon3D
{
public:
	enum EIconType
	{
		NUMBER,		// 数字
		MINUS,		// マイナスマーク
		MONEY,		// お金マーク
		RECOVERY,	// 回復マーク
		PERCENT,	// パーセント
	};
public:
	CNumber3D(CTaskGroup::EPriority list = CTaskGroup::EPriority::LEVEL_3D_1);
	~CNumber3D();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	static CNumber3D* Create();

	void SetSpeed(float Speed) { m_speed = Speed; }
	void SetNumber(int Number) { m_myNumber = Number; }
	void SetMove(bool Move) { m_isMove = Move; }

	void ReleaseTimer(int nTimar);

	void AttachIcon(EIconType icon);

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