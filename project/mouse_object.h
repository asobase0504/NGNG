//**************************************************************
//
// 難易度システム
// Author: Tomidokoro Tomoki
//
//**************************************************************
#ifndef _MOUSE_OBJECT_H_
#define _MOUSE_OBJECT_H_

#include "object2d.h"

class CMouseObject : public CObject2d
{
public:
	CMouseObject();
	~CMouseObject();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
private:
};
#endif
