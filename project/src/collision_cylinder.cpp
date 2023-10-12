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
	// 円柱の半径と球の半径を足した距離
	float addLength = m_length + inSphere->GetLength();
	float addHeight = m_height + inSphere->GetLength();

	// 円柱の中心値から球の中心値までの距離
	D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f,0.0f,0.0f);
	differenceX.x = GetPos().x - inSphere->GetPos().x;

	D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceY.y = GetPos().y - inSphere->GetPos().y;

	D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceZ.z = GetPos().z - inSphere->GetPos().z;

	//x,y,zの絶対値の計算
	float differenceLengthX = D3DXVec3Length(&differenceX);
	float differenceLengthY = D3DXVec3Length(&differenceY);
	float differenceLengthZ = D3DXVec3Length(&differenceZ);

	// 当たり判定
	if (differenceLengthX <= addLength
		&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength()
		&& GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
	{// xの当たり判定
		return true;
	}	


	//--------------------------------------------------------------
	// 次回 : zの当たり判定
	//--------------------------------------------------------------


	if (differenceLengthZ <= addLength
		&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength())
	{// zの当たり判定
		//return true;
	}

	if (differenceLengthY < addHeight
		&& GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
		&& GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
	{// yの当たり判定
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
