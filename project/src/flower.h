//**************************************************************
//
// flower
// Author: Buriya Kota
//
//**************************************************************
#ifndef _FLOWER_H_
#define _FLOWER_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// 前方宣言
//==============================================================
class CCollisionSphere;

//==============================================================
// クラス
//==============================================================
class CFlower : public CObjectX
{
public:
	static const int INTERVAL;
public:
	CFlower(CTaskGroup::EPriority list = CTaskGroup::LEVEL_3D_1);
	~CFlower();

	HRESULT Init() override;
	HRESULT Init(const D3DXVECTOR3& inPos, const float& inHeight);

	void Uninit() override;
	void Update() override;

	static CFlower* Create(const D3DXVECTOR3& inPos, const float& inHeight);

private:
	void HealingArea_();

private:
	CCollisionSphere* m_collision;

	// 回復する間隔
	int m_healingCount;
};
#endif	// _FLOWER_H_