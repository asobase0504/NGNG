#include "collision_box.h"
#include "collision_cylinder.h"
#include "line.h"

CCollisionBox::CCollisionBox()
{
	for (int i = 0; i < 12; i++)
	{
		m_line[i] = nullptr; 
	}
}

CCollisionBox::~CCollisionBox()
{
}

HRESULT CCollisionBox::Init()
{
	for (int i = 0; i < 12; i++)
	{
		m_line[i] = CLine::Create();
		SetEndChildren(m_line[i]);
		m_line[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		m_line[i]->SetPosTarget(&GetPosWorld());
		m_line[i]->SetRotTarget(&GetRot());
	}

	return S_OK;
}

void CCollisionBox::Update()
{
	CCollision::Update();

}

CCollisionBox* CCollisionBox::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXMATRIX& mtx)
{
	CCollisionBox* collision = new CCollisionBox;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->SetRot(rot);
	collision->SetMtxWorld(mtx);
	collision->SetSize(size);
	collision->SetLine();

	return collision;
}

void CCollisionBox::SetLine()
{

	D3DXVECTOR3 size = GetSize();

	float left = -size.x;	// x1
	float right = size.x;	// x2
	float back = size.z;		// z1
	float front = -size.z;	// z2
	float top = size.y;		// y2
	float bot = -size.y;		// y2

	// ‚S‚Â‚Ì’¸“_
	D3DXVECTOR3 posLine[8];
	posLine[0] = D3DXVECTOR3(left, top, back);
	posLine[1] = D3DXVECTOR3(right, top, back);
	posLine[2] = D3DXVECTOR3(right, top, front);
	posLine[3] = D3DXVECTOR3(left, top, front);
	posLine[4] = D3DXVECTOR3(left, bot, back);
	posLine[5] = D3DXVECTOR3(right, bot, back);
	posLine[6] = D3DXVECTOR3(right, bot, front);
	posLine[7] = D3DXVECTOR3(left, bot, front);

	m_line[0]->SetLine(posLine[0], posLine[1]);
	m_line[1]->SetLine(posLine[1], posLine[2]);
	m_line[2]->SetLine(posLine[2], posLine[3]);
	m_line[3]->SetLine(posLine[3], posLine[0]);

	m_line[4]->SetLine(posLine[4], posLine[5]);
	m_line[5]->SetLine(posLine[5], posLine[6]);
	m_line[6]->SetLine(posLine[6], posLine[7]);
	m_line[7]->SetLine(posLine[7], posLine[4]);

	m_line[8]->SetLine(posLine[0], posLine[4]);
	m_line[9]->SetLine(posLine[1], posLine[5]);
	m_line[10]->SetLine(posLine[2], posLine[6]);
	m_line[11]->SetLine(posLine[3], posLine[7]);
}
