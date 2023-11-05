#include "collision.h"

CCollision::CCollision() : 
	m_posLocal(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posWorld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posParent(nullptr),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_isTop(false),
	m_isUnder(false)
{
	D3DXMatrixIdentity(&m_mtx);
}

CCollision::~CCollision()
{
}

void CCollision::Update()
{
	m_posWorld = m_posLocal;
	if (m_posParent != nullptr)
	{
		m_posWorld += *m_posParent;
	}

	m_posOld = m_posWorld;
}
