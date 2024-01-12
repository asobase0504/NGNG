//**************************************************************
//
// �}�b�v�̃��f��
// Author : Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "map_model.h"
#include "collision_box.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CMapModel::CMapModel() :
	CObjectX(CTaskGroup::LEVEL_3D_1),
	m_collisionBox(nullptr)
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CMapModel::~CMapModel()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CMapModel::Init()
{
	CObjectX::Init();

	return S_OK;
}

//--------------------------------------------------------------
// ������(�I�[�o�[���[�h)
//--------------------------------------------------------------
HRESULT CMapModel::Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	CObjectX::Init();

	m_collisionBox = CCollisionBox::Create(inPos, inRot, inSize);
	m_collisionBox->SetMtxWorld(GetMtxWorld());
	SetEndChildren(m_collisionBox);

	return S_OK;
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CMapModel::Update()
{
	CObjectX::Update();

	D3DXMATRIX mtx = GetMtxWorld();
	m_collisionBox->SetMtxWorld(mtx);
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CMapModel::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CMapModel* CMapModel::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	CMapModel* pMapModel = nullptr;
	pMapModel = new CMapModel;

	if (pMapModel != nullptr)
	{
		pMapModel->Init(inPos, inRot, inSize);
		pMapModel->SetPos(inPos);
		pMapModel->SetRot(inRot);
		pMapModel->SetSize(inSize);
	}

	return pMapModel;
}
