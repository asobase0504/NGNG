#include "collision_cylinder.h"
#include "collision_sphere.h"
#include "collision_box.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "utility.h"

CCollisionCyinder::CCollisionCyinder() : m_extrusion(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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
	bool isLanding = false;

	D3DXVECTOR3 boxPos = inBox->GetPos();
	D3DXVECTOR3 boxSize = inBox->GetSize();
	D3DXVECTOR3 cylinderPos = GetPos();
	D3DXVECTOR3 cylinderPosOld = GetPosOld();
	float radius = GetLength();

	float left = boxPos.x - boxSize.x * 0.5f;	// x1
	float right = boxPos.x + boxSize.x * 0.5f;	// x2
	float back = boxPos.z + boxSize.z * 0.5f;	// z1
	float front = boxPos.z - boxSize.z * 0.5f;	// z2

	// ４つの頂点
	D3DXVECTOR3 pos[4];
	pos[0] = D3DXVECTOR3(left, 0.0f, back);
	pos[1] = D3DXVECTOR3(right, 0.0f, back);
	pos[2] = D3DXVECTOR3(right, 0.0f, front);
	pos[3] = D3DXVECTOR3(left, 0.0f, front);

	D3DXVECTOR3 vecLine(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);

	float triangleBase1 = left - cylinderPos.x;
	float triangleBase2 = right - cylinderPos.x;
	float triangleHeight1 = back - cylinderPos.z;
	float triangleHeight2 = front - cylinderPos.z;

	if ((cylinderPos.x > left) && (cylinderPos.x < right) &&
		(cylinderPos.z > front - radius) && (cylinderPos.z < back + radius))
	{// 手前　奥
		if (boxPos.z < cylinderPos.z)
		{// 奥
			m_extrusion = D3DXVECTOR3(cylinderPos.x, cylinderPos.y, back + radius);
		}
		else if (boxPos.z > cylinderPos.z)
		{// 手前
			m_extrusion = D3DXVECTOR3(cylinderPos.x, cylinderPos.y, front - radius);
		}

		return true;
	}
	else if ((cylinderPos.x > left - radius) && (cylinderPos.x < right + radius) &&
		(cylinderPos.z > front) && (cylinderPos.z < back))
	{// 左右
		if (boxPos.x < cylinderPos.x)
		{// 右
			//vecLine = 
			//m_extrusion = D3DXVECTOR3(right + radius, cylinderPos.y, cylinderPos.z);
		}
		else if (boxPos.x > cylinderPos.x)
		{// 左
			m_extrusion = D3DXVECTOR3(left - radius, cylinderPos.y, cylinderPos.z);
		}

		return true;
	}
	//else if ((triangleBase1 * triangleBase1) + (triangleHeight1 * triangleHeight1) < radius * radius)
	//{// 左上
	//	return true;
	//}
	//else if ((triangleBase2 * triangleBase2) + (triangleHeight1 * triangleHeight1) < radius * radius)
	//{// 右上
	//	return true;
	//}
	//else if ((triangleBase2 * triangleBase2) + (triangleHeight2 * triangleHeight2) < radius * radius)
	//{// 右下
	//	return true;
	//}
	//else if ((triangleBase1 * triangleBase1) + (triangleHeight2 * triangleHeight2) < radius * radius)
	//{// 左下
	//	return true;
	//}

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
			{// 左の当たり判定
				return true;
			}

			if (GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength())
			{// 右の当たり判定
 				return true;
			}
		}

		if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
			&& GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength()
			&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y - inSphere->GetLength()
			&& GetPos().y - (m_height * 0.5f) < inSphere->GetPos().y + inSphere->GetLength())
		{
			if (GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
			{// 前の当たり判定
				return true;
			}

			if (GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength())
			{// 奥の当たり判定
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
			{// 上の当たり判定
				return true;
			}

			if (GetPos().y - (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength())
			{// 下の当たり判定
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
