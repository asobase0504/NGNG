#include "collision_cylinder.h"
#include "collision_sphere.h"

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

	// “–‚½‚è”»’è
	if (differenceLengthX <= addLength
		&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength()
		&& GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
	{// x‚Ì“–‚½‚è”»’è
		return true;
	}	


	//--------------------------------------------------------------
	// Ÿ‰ñ : z‚Ì“–‚½‚è”»’è
	//--------------------------------------------------------------


	if (differenceLengthZ <= addLength
		&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength())
	{// z‚Ì“–‚½‚è”»’è
		//return true;
	}

	if (differenceLengthY < addHeight
		&& GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
		&& GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
	{// y‚Ì“–‚½‚è”»’è
		return true;
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
