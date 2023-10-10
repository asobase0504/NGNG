//**************************************************************
//
// �J����
// Author : Hamada Ryuuga
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _CAMERA_GAME_H_
#define _CAMERA_GAME_H_

//==============================================================
// include
//==============================================================
#include "camera.h"

//==============================================================
// �J�����N���X
//==============================================================
class CCameraGame : public CCamera
{
private:
	static const float DISTANCE;	// �J�����ԋ���
public:
	CCameraGame();
	~CCameraGame() override;

	HRESULT Init() override;
	void Update() override;

	void SetTargetPos(const D3DXVECTOR3& pos) { m_targetPos = &pos; }
private:
	const D3DXVECTOR3* m_targetPos;
};

#endif		// _CAMERA_H_
