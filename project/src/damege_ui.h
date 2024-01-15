//==================================================
// procedure.h
// Author: Yuda Kaito
//==================================================
#ifndef _DAEEGE_UI_H_
#define _DAEEGE_UI_H_

//**************************************************
// インクルード
//**************************************************
#include "procedure3D.h"

//**************************************************
// クラス
//**************************************************
class CDamegeUI : public CProcedure3D
{
private:
	static const int DELETE_TIME;
public:
	explicit CDamegeUI();
	~CDamegeUI() override;

	HRESULT Init() override;
	void Update() override;

	static CDamegeUI* Create(D3DXVECTOR3 pos, D3DXCOLOR color, const int inNumber);

private:
	int m_time;
};

#endif // _TIMER_H_

