//**************************************************************
//
// �I���ł������
// Author : ���c�喲
//
//**************************************************************

// include
#include "select_entity.h"
#include "collision_cylinder.h"
#include "map.h"
#include "select_ui.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CSelectEntity::CSelectEntity() :
	m_collisionCylinder(nullptr),
	m_collisionBox(nullptr),
	m_ui(nullptr)
{
	CMap* map = CMap::GetMap();
	map->InSelectEntityList(this);
	map->SetEndChildren(this);
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CSelectEntity::~CSelectEntity()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CSelectEntity::Init()
{
	CObjectX::Init();
	m_collisionCylinder = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	m_collisionCylinder->SetParent(&m_pos);
	SetEndChildren(m_collisionCylinder);
	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CSelectEntity::Update()
{
	CObjectX::Update();
	if (!m_isNearCharacter && m_ui != nullptr)
	{
		m_ui->Uninit();
		m_ui = nullptr;
	}
}

//--------------------------------------------------------------
// UI�̕\��
//--------------------------------------------------------------
void CSelectEntity::DisplayUI()
{
	if (m_ui == nullptr)
	{
		m_ui = new CSelectUI;
		m_ui->Init();
		m_ui->SetText(m_uiText);
		SetEndChildren(m_ui);
	}

	m_isNearCharacter = true;

}
