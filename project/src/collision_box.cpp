#include "collision_box.h"
#include "collision_cylinder.h"
#include "line.h"

CCollisionBox::CCollisionBox()
{
	for (int i = 0; i < 4; i++)
	{
		m_line[i] = nullptr; 
	}
}

CCollisionBox::~CCollisionBox()
{
}

HRESULT CCollisionBox::Init()
{
	for (int i = 0; i < 4; i++)
	{
		m_line[i] = CLine::Create();
	}

	return S_OK;
}

void CCollisionBox::Uninit()
{
	CCollision::Uninit();

	for (int i = 0; i < 4; i++)
	{
		m_line[i]->Uninit();
	}
}

void CCollisionBox::Update()
{
	CCollision::Update();

	D3DXVECTOR3 pos = GetPosWorld();
	D3DXVECTOR3 size = GetSize();
	D3DXVECTOR3 rot = GetRot();

	float left = -size.x * 0.5f;	// x1
	float right = size.x * 0.5f;	// x2
	float back = size.z * 0.5f;		// z1
	float front = -size.z * 0.5f;	// z2

	// ‚S‚Â‚Ì’¸“_
	D3DXVECTOR3 posLine[4];
	posLine[0] = D3DXVECTOR3(left - 10.0f, 0.0f, back + 10.0f);
	posLine[1] = D3DXVECTOR3(right + 10.0f, 0.0f, back + 10.0f);
	posLine[2] = D3DXVECTOR3(right + 10.0f, 0.0f, front - 10.0f);
	posLine[3] = D3DXVECTOR3(left - 10.0f, 0.0f, front - 10.0f);

	m_line[0]->SetLine(pos, rot, posLine[0], posLine[1], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[1]->SetLine(pos, rot, posLine[1], posLine[2], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[2]->SetLine(pos, rot, posLine[2], posLine[3], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[3]->SetLine(pos, rot, posLine[3], posLine[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

CCollisionBox* CCollisionBox::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXMATRIX& mtx)
{
	CCollisionBox* collision = new CCollisionBox;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->SetRot(rot);
	collision->SetMtxWorld(mtx);
	collision->m_size = size;

	return collision;
}
