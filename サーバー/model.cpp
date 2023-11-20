//============================
//
// ���W�����郂�f��
// Author:hamada ryuuga
//
//============================

#include "model.h"

//--------------------------------------------------
// ������
//--------------------------------------------------
void CModel::Init()
{
	m_cpmmand = COMMAND_TYPE_NONE;
	m_moveId = MOVE_TYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_motion = 0;
	m_id = 4560;
	m_isUse = false;
	m_isMove = false;
	m_isUp = false;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CModel::Uninit()
{

}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CModel::Update()
{
	D3DXVECTOR3 Pos = GetPos();
	if (m_isMove)
	{
		
		if (m_isUp)
		{
			Pos.x += HomingFunction(Pos.x, m_posLocate.x, 0.01f);
			if (m_posLocate.x+10.0f >= Pos.x&&m_posLocate.x - 10.0f <= Pos.x)
			{
				m_isUp = false;
			}
		}
		else
		{
			Pos.x += HomingFunction(Pos.x, m_posOrigin.x, 0.01f);
			if (m_posOrigin.x + 10.0f >= Pos.x&&m_posOrigin.x - 10.0f <= Pos.x)
			{
				m_isUp = true;
			}
		}
		SetPos(Pos);
	}
	else
	{
		D3DXVECTOR3 Pos = GetPos();
		SetPos(Pos + m_move);
	}
}

//--------------------------------------------------
// �R�}���h
//--------------------------------------------------
D3DXVECTOR3 CModel::SetKer(MOVE_TYPE moveId,int pow)
{
	m_moveId = moveId;
	D3DXVECTOR3 pos = m_pos;
	float move = SPEED*pow;
	switch (m_moveId)
	{
	case MOVE_TYPE_NONE:
		std::cout << "No movement" << std::endl;

		break;

	case MOVE_TYPE_MOVEUP:
		std::cout << "Move up" << std::endl;
		pos.y -= move;
		printf("Pos:X = %f,Y = %f", pos.x, pos.y);
		break;

	case MOVE_TYPE_MOVEDOWN:
		std::cout << "Move down" << std::endl;
		pos.y += move;
		printf("Pos:X = %f,Y = %f", pos.x, pos.y);
		break;

	case MOVE_TYPE_MOVELEFT:
		std::cout << "Move left" << std::endl;
		pos.x -= move;
		printf("Pos:X = %f,Y = %f", pos.x, pos.y);
		break;

	case MOVE_TYPE_MOVERIGHT:
		std::cout << "Move right" << std::endl;
		pos.x += move;
		printf("Pos:X = %f,Y = %f", pos.x, pos.y);
		break;

	default:
		std::cout << "Unknown movement" << std::endl;
		break;
	}
	SetPos(pos);
	return pos;
}

float  CModel::HomingFunction(float currentPosition, float target, float Kp)
{
	float error = target - currentPosition; // �덷���v�Z
	float controlSignal = Kp * error;       // ����M�����v�Z
	return controlSignal;                    // ����M����Ԃ�
}