//==================================================
//
// 所持しているアイテムUI群
// Author: YudaKaito
//
//==================================================
#ifndef _EFFECT_DAMAGE_CAMERA_H_
#define _EFFECT_DAMAGE_CAMERA_H_

//**************************************************
// インクルード
//**************************************************
#include "object2d.h"

//**************************************************
// クラス
//**************************************************
class CEffectDamageCamera : public CObject2d
{
public:
	CEffectDamageCamera();
	~CEffectDamageCamera();

	HRESULT Init() override;
	void Update() override;

	static CEffectDamageCamera* Create();

private:
	int m_time;
	int m_maxTime;
};

#endif // _TIMER_H_