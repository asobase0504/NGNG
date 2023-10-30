#include "collision.h"

CCollision::CCollision() : m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_isTop(false)
{
	D3DXMatrixIdentity(&m_mtx);
}

CCollision::~CCollision()
{
}

void CCollision::Update()
{
	m_posOld = m_pos;
}
