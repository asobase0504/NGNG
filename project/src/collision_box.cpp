#include "collision_box.h"
#include "collision_cylinder.h"
#include "line.h"
#include "utility.h"

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

bool CCollisionBox::ToCylinder(CCollisionCylinder * inCyinder)
{
	bool isLanding = false;

	D3DXVECTOR3 boxPos = GetPosWorld();
	D3DXVECTOR3 boxRot = GetRot();
	D3DXVECTOR3 boxSize = GetSize();
	D3DXMATRIX boxMtxWorld, mtxTrans, mtxRot;

	D3DXMatrixIdentity(&boxMtxWorld);

	// å¸Ç´ÇîΩâf
	D3DXMatrixRotationYawPitchRoll(&mtxRot, boxRot.y, boxRot.x, boxRot.z);
	D3DXMatrixMultiply(&boxMtxWorld, &boxMtxWorld, &mtxRot);
	// à íuÇîΩâf
	D3DXMatrixTranslation(&mtxTrans, boxPos.x, boxPos.y, boxPos.z);
	D3DXMatrixMultiply(&boxMtxWorld, &boxMtxWorld, &mtxTrans);

	D3DXVECTOR3 cylinderPos = inCyinder->GetPosWorld();
	D3DXVECTOR3 cylinderPosOld = inCyinder->GetPosOld();
	float radius = inCyinder->GetLength();

	float left = -boxSize.x;		// ç∂
	float right = boxSize.x;		// âE
	float top = boxSize.y;		// è„
	float bottum = -boxSize.y;	// â∫
	float back = boxSize.z;		// âú
	float front = -boxSize.z;	// ëO

								// ÇSÇ¬ÇÃí∏ì_
	D3DXVECTOR3 pos[4];
	pos[0] = D3DXVECTOR3(left - radius, 0.0f, back + radius);
	pos[1] = D3DXVECTOR3(right + radius, 0.0f, back + radius);
	pos[2] = D3DXVECTOR3(right + radius, 0.0f, front - radius);
	pos[3] = D3DXVECTOR3(left - radius, 0.0f, front - radius);

	D3DXVECTOR3 worldPos[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVec3TransformCoord(&worldPos[nCnt], &pos[nCnt], &boxMtxWorld);
	}

	D3DXVECTOR3 vecLine[4];
	vecLine[0] = worldPos[1] - worldPos[0];
	vecLine[1] = worldPos[2] - worldPos[1];
	vecLine[2] = worldPos[3] - worldPos[2];
	vecLine[3] = worldPos[0] - worldPos[3];

	D3DXVECTOR3 vec[4];
	vec[0] = cylinderPos - worldPos[0];
	vec[1] = cylinderPos - worldPos[1];
	vec[2] = cylinderPos - worldPos[2];
	vec[3] = cylinderPos - worldPos[3];

	float InOut[4];
	InOut[0] = Vec2Cross(&vecLine[0], &vec[0]);
	InOut[1] = Vec2Cross(&vecLine[1], &vec[1]);
	InOut[2] = Vec2Cross(&vecLine[2], &vec[2]);
	InOut[3] = Vec2Cross(&vecLine[3], &vec[3]);

	// âüèoà íu
	D3DXVECTOR3 extrusion(0.0f, 0.0f, 0.0f);

	SetIsTop(false);
	SetIsUnder(false);

	if (InOut[0] < 0.0f && InOut[1] < 0.0f && InOut[2] < 0.0f && InOut[3] < 0.0f)
	{
		return true;
	}
	return false;
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

	// ÇSÇ¬ÇÃí∏ì_
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
