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
	MapChangeRelese();
	CObjectX::Init();

	return S_OK;
}

//--------------------------------------------------------------
// ������(�I�[�o�[���[�h)
//--------------------------------------------------------------
HRESULT CMapModel::Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	MapChangeRelese();
	CObjectX::Init();

	D3DXMATRIX mtx = GetMtxWorld();
	m_collisionBox = CCollisionBox::Create(inPos, inRot, inSize, mtx);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CMapModel::Uninit()
{
	if (m_collisionBox != nullptr)
	{
		m_collisionBox->Uninit();
		m_collisionBox = nullptr;
	}

	CObjectX::Uninit();
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
