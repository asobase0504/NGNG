#include "collision_cylinder.h"
#include "collision_sphere.h"
#include "collision_box.h"
#include "enemy_manager.h"
#include "player_manager.h"

CCollisionCyinder::CCollisionCyinder()
{
}

CCollisionCyinder::~CCollisionCyinder()
{
}

HRESULT CCollisionCyinder::Init()
{
	return E_NOTIMPL;
}

void CCollisionCyinder::Uninit()
{
}

bool CCollisionCyinder::ToCylinder(CCollisionCyinder * inCyinder)
{
	float addLength = m_length + inCyinder->GetLength();

	D3DXVECTOR2 difference;
	difference.x = GetPos().x - inCyinder->GetPos().x;
	difference.y = GetPos().y - inCyinder->GetPos().y;

	float differenceLength =  D3DXVec2Length(&difference);

	if (addLength <= differenceLength)
	{
		return true;
	}

	return false;
}

bool CCollisionCyinder::ToBox(CCollisionBox* inBox, bool isExtrusion)
{
	//// ‰~’Œ‚Ìpos‚Æposold‚ğ‚Á‚Ä‚­‚é
	//D3DXVECTOR3 CylinderPos = GetPos();
	//D3DXVECTOR3 CylnderPosOld = GetPosOld();
	//D3DXVECTOR3 BoxPos = inBox->GetPos();

	//// ‰~’Œ‚Ì”¼Œa‚Æ” ‚Ì”¼Œa‚ğ‘«‚µ‚½‹——£
	//float addLength = m_length + inBox->GetLength();
	//float addHeight = m_height + inBox->GetLength();

	//// ‰~’Œ‚Ì’†S’l‚©‚ç” ‚Ì’†S’l‚Ü‚Å‚Ì‹——£
	//D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//differenceX.x = CylinderPos.x - BoxPos.x;

	//D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//differenceY.y = CylinderPos.y - BoxPos.y;

	//D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//differenceZ.z = CylinderPos.z - BoxPos.z;

	////x,y,z‚Ìâ‘Î’l‚ÌŒvZ
	//float differenceLengthX = D3DXVec3Length(&differenceX);
	//float differenceLengthY = D3DXVec3Length(&differenceY);
	//float differenceLengthZ = D3DXVec3Length(&differenceZ);

	//if (differenceLengthX <= addLength
	//	&& differenceLengthY < addHeight
	//	&& differenceLengthZ <= addLength)
	//{
	//	if (CylinderPos.z + (m_length * 0.5f) > BoxPos.z - inBox->GetLength()
	//		&& CylinderPos.z - (m_length * 0.5f) < BoxPos.z + inBox->GetLength()
	//		&& CylinderPos.y + (m_height * 0.5f) > BoxPos.y - inBox->GetLength()
	//		&& CylinderPos.y - (m_height * 0.5f) < BoxPos.y + inBox->GetLength())
	//	{
	//		if (CylinderPos.x + (m_length * 0.5f) > BoxPos.x - inBox->GetLength())
	//		{// ¶‚Ì“–‚½‚è”»’è
	//			if (isExtrusion)
	//			{
	//				CylinderPos.x += differenceLengthX * 0.5f;
	//				m_extrusion.x = CylinderPos.x;
	//				SetPos(CylinderPos);
	//			}
	//			return true;
	//		}

	//		if (CylinderPos.x - (m_length * 0.5f) < BoxPos.x + inBox->GetLength())
	//		{// ‰E‚Ì“–‚½‚è”»’è
	//			if (isExtrusion)
	//			{
	//				CylinderPos.x -= differenceLengthX * 0.5;
	//				m_extrusion.x = CylinderPos.x;
	//				SetPos(CylinderPos);
	//			}
	//			return true;
	//		}
	//	}

	//	if (CylinderPos.x + (m_length * 0.5f) > BoxPos.x - inBox->GetLength()
	//		&& CylinderPos.x - (m_length * 0.5f) < BoxPos.x + inBox->GetLength()
	//		&& CylinderPos.y + (m_height * 0.5f) > BoxPos.y - inBox->GetLength()
	//		&& CylinderPos.y - (m_height * 0.5f) < BoxPos.y + inBox->GetLength())
	//	{
	//		if (CylinderPos.z + (m_length * 0.5f) > BoxPos.z - inBox->GetLength())
	//		{// ‘O‚Ì“–‚½‚è”»’è
	//			//if (isExtrusion)
	//			//{
	//			//	CylinderPos.z += differenceLengthZ;
	//			//	m_extrusion.z = CylinderPos.z;
	//			//	SetPos(CylinderPos);
	//			//}
	//			return true;
	//		}

	//		if (CylinderPos.z - (m_length * 0.5f) < BoxPos.z + inBox->GetLength())
	//		{// ‰œ‚Ì“–‚½‚è”»’è
	//			//if (isExtrusion)
	//			//{
	//			//	CylinderPos.z -= differenceLengthZ;
	//			//	m_extrusion.z = CylinderPos.z;
	//			//	SetPos(CylinderPos);
	//			//}
	//			return true;
	//		}
	//	}

	//	if (CylinderPos.x + (m_length * 0.5f) > BoxPos.x - inBox->GetLength()
	//		&& CylinderPos.x - (m_length * 0.5f) < BoxPos.x + inBox->GetLength()
	//		&& CylinderPos.z + (m_length * 0.5f) > BoxPos.z - inBox->GetLength()
	//		&& CylinderPos.z - (m_length * 0.5f) < BoxPos.z + inBox->GetLength())
	//	{
	//		if (CylinderPos.y + (m_height * 0.5f) < BoxPos.y - inBox->GetLength())
	//		{// ã‚Ì“–‚½‚è”»’è
	//			//if (isExtrusion)
	//			//{
	//			//	CylinderPos.y -= differenceLengthY;
	//			//	m_extrusion.y = CylinderPos.y;
	//			//	SetPos(CylinderPos);
	//			//}
	//			return true;
	//		}

	//		if (CylinderPos.y - (m_height * 0.5f) > BoxPos.y + inBox->GetLength())
	//		{// ‰º‚Ì“–‚½‚è”»’è
	//			//if (isExtrusion)
	//			//{
	//			//	CylinderPos.y += differenceLengthY;
	//			//	m_extrusion.y = CylinderPos.y;
	//			//	SetPos(CylinderPos);
	//			//}
	//			return true;
	//		}
	//	}
	//}

	//return false;

	D3DXVECTOR3 boxPos = inBox->GetPos();
	D3DXVECTOR3 boxSize = inBox->GetSize();
	D3DXVECTOR3 cylinderPos = GetPos();
	float radius = GetLength();

	float left = boxPos.x - boxSize.x * 0.5f;
	float right = boxPos.x + boxSize.x * 0.5f;
	float front = boxPos.z - boxSize.z * 0.5f;
	float back = boxPos.z + boxSize.z * 0.5f;

	int a = 0;

	if ((cylinderPos.x > left) &&
		(cylinderPos.x < right) &&
		(cylinderPos.z < back) &&
		(cylinderPos.z > front))
	{
		// ¶
		if (cylinderPos.x - radius < right)
		{
			return true;
		}
		else if (cylinderPos.x + radius > left)
		{
			return true;
		}











		return true;
	}





	//else if ((cylinderPos.x > left - radius) &&
	//	(cylinderPos.x < right + radius) &&
	//	(cylinderPos.z > back) &&
	//	(cylinderPos.z < front))
	//{
	//	return true;
	//}
	//else if (((left - cylinderPos.x) * (left - cylinderPos.x) + (back - cylinderPos.x) * (back - cylinderPos.x)) < radius * radius)
	//{
	//	return true;
	//}
	//else if (((right - cylinderPos.x) * (right - cylinderPos.x) + (back - cylinderPos.x) * (back - cylinderPos.x)) < radius * radius)
	//{
	//	return true;
	//}
	//else if (((right - cylinderPos.x) * (right - cylinderPos.x) + (front - cylinderPos.x) * (front - cylinderPos.x)) < radius * radius)
	//{
	//	return true;
	//}
	//else if (((left - cylinderPos.x) * (left - cylinderPos.x) + (front - cylinderPos.x) * (front - cylinderPos.x)) < radius * radius)
	//{
	//	return true;
	//}

	return false;
}

bool CCollisionCyinder::ToSphere(CCollisionSphere * inSphere)
{
	// ‰~’Œ‚Ì”¼Œa‚Æ‹…‚Ì”¼Œa‚ğ‘«‚µ‚½‹——£
	float addLength = m_length + inSphere->GetLength();
	float addHeight = m_height + inSphere->GetLength();

	// ‰~’Œ‚Ì’†S’l‚©‚ç‹…‚Ì’†S’l‚Ü‚Å‚Ì‹——£
	D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f,0.0f,0.0f);
	differenceX.x = GetPos().x - inSphere->GetPos().x;

	D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceY.y = GetPos().y - inSphere->GetPos().y;

	D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceZ.z = GetPos().z - inSphere->GetPos().z;

	//x,y,z‚Ìâ‘Î’l‚ÌŒvZ
	float differenceLengthX = D3DXVec3Length(&differenceX);
	float differenceLengthY = D3DXVec3Length(&differenceY);
	float differenceLengthZ = D3DXVec3Length(&differenceZ);

	if (differenceLengthX <= addLength
		&& differenceLengthY < addHeight
		&& differenceLengthZ <= addLength)
	{
		if (GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength()
			&& GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength()
			&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y - inSphere->GetLength()
			&& GetPos().y - (m_height * 0.5f) < inSphere->GetPos().y + inSphere->GetLength())
		{
			if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength())
			{// ¶‚Ì“–‚½‚è”»’è
				return true;
			}

			if (GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength())
			{// ‰E‚Ì“–‚½‚è”»’è
 				return true;
			}
		}

		if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
			&& GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength()
			&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y - inSphere->GetLength()
			&& GetPos().y - (m_height * 0.5f) < inSphere->GetPos().y + inSphere->GetLength())
		{
			if (GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
			{// ‘O‚Ì“–‚½‚è”»’è
				return true;
			}

			if (GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength())
			{// ‰œ‚Ì“–‚½‚è”»’è
				return true;
			}
		}

		if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
			&& GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength()
			&& GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength()
			&& GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength())
		{
			if (GetPos().y + (m_height * 0.5f) < inSphere->GetPos().y - inSphere->GetLength()
				)
			{// ã‚Ì“–‚½‚è”»’è
				return true;
			}

			if (GetPos().y - (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength())
			{// ‰º‚Ì“–‚½‚è”»’è
				return true;
			}
		}
	}

	return false;
}

CCollisionCyinder * CCollisionCyinder::Create(const D3DXVECTOR3 & pos, const float length, const float height)
{
	CCollisionCyinder* collision = new CCollisionCyinder;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_length = length;
	collision->m_height = height;

	return collision;
}
