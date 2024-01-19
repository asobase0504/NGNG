//**************************************************************
//
// カメラ
// Author : Hamada Ryuuga
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _CAMERA_TITLE_H_
#define _CAMERA_TITLE_H_

//==============================================================
// include
//==============================================================
#include "camera.h"

//==============================================================
// カメラクラス
//==============================================================
class CTitleCamera : public CCamera
{
private:
	static const float DISTANCE;	// カメラ間距離
public:
	CTitleCamera();
	~CTitleCamera() override;

	HRESULT Init() override;
	void Update() override;

	void SetPosR(D3DXVECTOR3 &pos) { m_posR = pos; }
};

#endif		// _CAMERA_H_
