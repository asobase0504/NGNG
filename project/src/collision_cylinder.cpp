#include "collision_cylinder.h"
#include "collision_sphere.h"
#include "collision_box.h"
#include "enemy_manager.h"
#include "player_manager.h"
#include "utility.h"

CCollisionCylinder::CCollisionCylinder() : m_extrusion(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

CCollisionCylinder::~CCollisionCylinder()
{
}

HRESULT CCollisionCylinder::Init()
{
	return E_NOTIMPL;
}

void CCollisionCylinder::Uninit()
{
}

bool CCollisionCylinder::ToCylinder(CCollisionCylinder * inCyinder)
{
	D3DXVECTOR3 pos = GetPos();
	float radius = GetLength();

	D3DXVECTOR3 pos2 = inCyinder->GetPos();
	float radius2 = inCyinder->GetLength();

	float pos3 = pos.x - pos2.x;
	float pos4 = pos.z - pos2.z;

	float radius3 = radius + radius2;

	if ((pos3 * pos3) + (pos4 * pos4) <= (radius3 * radius3))
	{
		return true;
	}

	return false;
}

bool CCollisionCylinder::ToBox(CCollisionBox* inBox, bool isExtrusion)
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

	// �S�̒��_
	D3DXVECTOR3 pos[4];
	pos[0] = D3DXVECTOR3(left, 0.0f, back);
	pos[1] = D3DXVECTOR3(right, 0.0f, back);
	pos[2] = D3DXVECTOR3(right, 0.0f, front);
	pos[3] = D3DXVECTOR3(left, 0.0f, front);

	D3DXVECTOR3 v2(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 v(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 startPos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 endPos(0.0f, 0.0f, 0.0f);

	float triangleBase1 = left - cylinderPos.x;
	float triangleBase2 = right - cylinderPos.x;
	float triangleHeight1 = back - cylinderPos.z;
	float triangleHeight2 = front - cylinderPos.z;

	// �P�ʃx�N�g��
	D3DXVECTOR3 unitVec(0.0f, 0.0f, 0.0f);

	if ((cylinderPos.x > left) && (cylinderPos.x < right) &&
		(cylinderPos.z > front - radius) && (cylinderPos.z < back + radius))
	{// ��O�@��
		if (boxPos.z < cylinderPos.z)
		{// ��
			startPos = pos[0];
			endPos = pos[1];
			v2 = endPos - startPos;
			v = startPos - cylinderPosOld;
		}
		else
		{// ��O
			startPos = pos[2];
			endPos = pos[3];
			v2 = endPos - startPos;
			v = startPos - cylinderPosOld;
		}

		isLanding = true;
	}
	else if ((cylinderPos.x > left - radius) && (cylinderPos.x < right + radius) &&
		(cylinderPos.z > front) && (cylinderPos.z < back))
	{// ���E
		if (boxPos.x < cylinderPos.x)
		{// �E
			startPos = pos[1];
			endPos = pos[2];
			v2 = endPos - startPos;
			v = startPos - cylinderPosOld;
		}
		else
		{// ��
			startPos = pos[3];
			endPos = pos[0];
			v2 = endPos - startPos;
			v = startPos - cylinderPosOld;
		}

		isLanding = true;
	}
	else if ((triangleBase1 * triangleBase1) + (triangleHeight1 * triangleHeight1) < radius * radius)
	{// ����
		unitVec = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&unitVec, &unitVec);
		m_extrusion = pos[0] + unitVec * radius;
		return true;
	}
	else if ((triangleBase2 * triangleBase2) + (triangleHeight1 * triangleHeight1) < radius * radius)
	{// �E��
		unitVec = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
		D3DXVec3Normalize(&unitVec, &unitVec);
		m_extrusion = pos[1];
		return true;
	}
	else if ((triangleBase2 * triangleBase2) + (triangleHeight2 * triangleHeight2) < radius * radius)
	{// �E��
		unitVec = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
		D3DXVec3Normalize(&unitVec, &unitVec);
		m_extrusion = pos[2];
		return true;
	}
	else if ((triangleBase1 * triangleBase1) + (triangleHeight2 * triangleHeight2) < radius * radius)
	{// ����
		unitVec = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
		D3DXVec3Normalize(&unitVec, &unitVec);
		m_extrusion = pos[3];
		return true;
	}
	else
	{
		return isLanding;
	}

	if (isExtrusion && isLanding)
	{// http://marupeke296.com/COL_2D_No10_SegmentAndSegment.html
		D3DXVECTOR3 v1 = cylinderPos - cylinderPosOld;
		float t2 = Vec2Cross(&v, &v1) / Vec2Cross(&v1, &v2);

		D3DXVECTOR3 vecLineNormalize(0.0f, 0.0f, 0.0f);

		// intersection�@��_
		D3DXVECTOR3 intersection = startPos + v2 * t2;

		// �����ȃx�N�g��������
		D3DXVECTOR3 vertical(-v2.z, 0.0f, v2.x);
		// �傫���𐳋K��
		D3DXVec3Normalize(&vertical, &vertical);
		// ���o�̈ʒu
		m_extrusion = intersection + vertical * radius;
	}

	return isLanding;
}

bool CCollisionCylinder::ToSphere(CCollisionSphere * inSphere)
{
	// �~���̔��a�Ƌ��̔��a�𑫂�������
	float addLength = m_length + inSphere->GetLength();
	float addHeight = m_height + inSphere->GetLength();

	// �~���̒��S�l���狅�̒��S�l�܂ł̋���
	D3DXVECTOR3 differenceX = D3DXVECTOR3(0.0f,0.0f,0.0f);
	differenceX.x = GetPos().x - inSphere->GetPos().x;

	D3DXVECTOR3 differenceY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceY.y = GetPos().y - inSphere->GetPos().y;

	D3DXVECTOR3 differenceZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	differenceZ.z = GetPos().z - inSphere->GetPos().z;

	//x,y,z�̐�Βl�̌v�Z
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
			{// ���̓����蔻��
				return true;
			}

			if (GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength())
			{// �E�̓����蔻��
 				return true;
			}
		}

		if (GetPos().x + (m_length * 0.5f) > inSphere->GetPos().x - inSphere->GetLength()
			&& GetPos().x - (m_length * 0.5f) < inSphere->GetPos().x + inSphere->GetLength()
			&& GetPos().y + (m_height * 0.5f) > inSphere->GetPos().y - inSphere->GetLength()
			&& GetPos().y - (m_height * 0.5f) < inSphere->GetPos().y + inSphere->GetLength())
		{
			if (GetPos().z + (m_length * 0.5f) > inSphere->GetPos().z - inSphere->GetLength())
			{// �O�̓����蔻��
				return true;
			}

			if (GetPos().z - (m_length * 0.5f) < inSphere->GetPos().z + inSphere->GetLength())
			{// ���̓����蔻��
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
			{// ��̓����蔻��
				return true;
			}

			if (GetPos().y - (m_height * 0.5f) > inSphere->GetPos().y + inSphere->GetLength())
			{// ���̓����蔻��
				return true;
			}
		}
	}

	return false;
}

CCollisionCylinder * CCollisionCylinder::Create(const D3DXVECTOR3 & pos, const float length, const float height)
{
	CCollisionCylinder* collision = new CCollisionCylinder;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_length = length;
	collision->m_height = height;

	return collision;
}
