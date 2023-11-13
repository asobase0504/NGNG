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
	}

	return S_OK;
}

void CCollisionBox::Uninit()
{
	CCollision::Uninit();

	for (int i = 0; i < 12; i++)
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

	m_line[0]->SetLine(pos, rot, posLine[0], posLine[1], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[1]->SetLine(pos, rot, posLine[1], posLine[2], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[2]->SetLine(pos, rot, posLine[2], posLine[3], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[3]->SetLine(pos, rot, posLine[3], posLine[0], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_line[4]->SetLine(pos, rot, posLine[4], posLine[5], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[5]->SetLine(pos, rot, posLine[5], posLine[6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[6]->SetLine(pos, rot, posLine[6], posLine[7], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[7]->SetLine(pos, rot, posLine[7], posLine[4], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_line[8]->SetLine(pos, rot, posLine[0], posLine[4], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[9]->SetLine(pos, rot, posLine[1], posLine[5], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[10]->SetLine(pos, rot, posLine[2], posLine[6], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_line[11]->SetLine(pos, rot, posLine[3], posLine[7], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

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

	return collision;
}
