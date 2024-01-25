#include "mouse_object.h"

CMouseObject::CMouseObject() : CObject2d(CTaskGroup::EPriority::LEVEL_3D_UI)
{
}

CMouseObject::~CMouseObject()
{
}

HRESULT CMouseObject::Init()
{
	CObject2d::Init();
	CInput::GetKey()->LockCursorPos(false);
	SetSize(D3DXVECTOR3(5.0f, 5.0f, 0.0f));
	SetColor(D3DXCOLOR(0.8f,0.8f,1.0f,1.0f));
	return S_OK;
}

void CMouseObject::Uninit()
{
	CInput::GetKey()->LockCursorPos(true);
	CObject2d::Uninit();
}

void CMouseObject::Update()
{
	CObject2d::Update();
	SetPos(CInput::GetKey()->GetMouseCursor());
	AddRot(D3DXVECTOR3(0.0f,0.0f,0.1f));

	CObject2d* obj = CObject2d::Create(CTaskGroup::EPriority::LEVEL_3D_UI);
	obj->SetPos(m_pos);
	obj->SetRot(m_rot);
	obj->SetSize(m_size);
	obj->SetColor(m_color);
	obj->SetColorAlpha(0.5f);
	obj->SetPouseUpdate(true);
	obj->SetLife(8);
}
