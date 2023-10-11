#include "collision_cylinder.h"

bool CCollisionCyinder::ToCylinder(CCollisionCyinder * inCyinder)
{
	float addLength = m_length + inCyinder->GetLength();

	D3DXVECTOR2 difference;
	difference.x = GetPos().x - inCyinder->GetPos().x;
	difference.y = GetPos().y - inCyinder->GetPos().y;

	float differenceLength =  D3DXVec2Length(&difference);

	if (addLength <= differenceLength)
	{

	}
	return false;
}
