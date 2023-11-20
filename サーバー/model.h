//============================
//
// ç¿ïWÇ™Ç†ÇÈÉÇÉfÉã
// Author:hamada ryuuga
//
//============================

#ifndef _MODEL_H_
#define _MODEL_H_

#include "protocol.h"

class CModel
{

public:
	const float SPEED = 1.0f;
	void Init();
	void Uninit();
	void Update();

	float HomingFunction(float currentPosition, float target, float Kp);

	COMMAND_TYPE m_cpmmand;
	MOVE_TYPE m_moveId;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_posLocate;
	D3DXVECTOR3 m_posOrigin;
	int m_id;
	int m_motion;
	bool m_isUse;
	bool m_isMove;
	bool m_isUp;
	void SetSeve(D3DXVECTOR3 Pos) { m_pos = Pos; m_posOrigin = m_pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetPos(D3DXVECTOR3 Pos) { m_pos = Pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	
	void SetMotion(int id) { m_motion = id; }
	void SetPosLocate(D3DXVECTOR3 Pos) { m_posLocate = Pos; m_isMove = true; }
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	int GetMotion() { return m_motion; }
	D3DXVECTOR3 SetKer(MOVE_TYPE moveId,int Pow = 5);
	void SetId(int id) { m_id = id; }
	int GetId() { return m_id; }

};

#endif