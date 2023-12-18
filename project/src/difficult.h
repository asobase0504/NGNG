//**************************************************************
//
// 難易度システム
// Author: Tomidokoro Tomoki
//
//**************************************************************
#ifndef _DIFFICULT_H_
#define _DIFFICULT_H_

//==============================================================
// include
//==============================================================
#include "objectX.h"

//==============================================================
// クラス
//==============================================================

class CObject2d;
class CDifficult : public CObject
{
public:
	CDifficult();
	~CDifficult();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CDifficult* Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize);

	void SetCounter(bool is) { m_isCount = is; }
	int GetLevel() { return m_gameLevel; }
	int GetEnemyLevel() { return m_enemyLevel; }
private:
	int m_time;
	int m_enemyLevel;
	float m_gameLevel;
	bool m_isCount;

	CObject2d* m_ground;
	CObject2d* m_bar;
};
#endif	// _MAP_MODEL_H_
