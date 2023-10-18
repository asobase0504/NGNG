#include "collision_box.h"

CCollisionBox::CCollisionBox()
{
}

CCollisionBox::~CCollisionBox()
{
}

HRESULT CCollisionBox::Init()
{
	return E_NOTIMPL;
}

void CCollisionBox::Uninit()
{
}

CCollisionBox * CCollisionBox::Create(const D3DXVECTOR3 & pos, const D3DXVECTOR3& size)
{
	CCollisionBox* collision = new CCollisionBox;

	assert(collision != nullptr);

	collision->Init();
	collision->SetPos(pos);
	collision->m_size = size;

	return collision;
}
