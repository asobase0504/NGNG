#include "collision_sphere.h"

CCollisionSphere::CCollisionSphere()
{
}

CCollisionSphere::~CCollisionSphere()
{
}

HRESULT CCollisionSphere::Init()
{
	return E_NOTIMPL;
}

void CCollisionSphere::Uninit()
{
}

bool CCollisionSphere::ToBox(CCollisionBox * inBox)
{
	return false;
}

bool CCollisionSphere::ToSphere(CCollisionSphere * inSphere)
{
	float addLength = m_length + inSphere->GetLength();

	D3DXVECTOR3 difference = m_pos - inSphere->m_pos;

	float differenceLength = D3DXVec3Length(&difference);

	if (addLength >= differenceLength)
	{
		return true;
	}

	return false;
}

CCollisionSphere * CCollisionSphere::Create(const D3DXVECTOR3 & pos, const float length)
{
	CCollisionSphere* collision = new CCollisionSphere;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_length = length;

	return collision;
}
