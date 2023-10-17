//**************************************************************
//
// item_model
// Author: Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "item_model.h"
#include "item_manager.h"
#include "collision_sphere.h"

const float CItemModel::TAKE_RANGE(10.0f);

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CItemModel::CItemModel(CTaskGroup::EPriority list) :
	m_modelData{
	"BOX", }
{
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CItemModel::~CItemModel()
{
}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CItemModel::Init()
{
	CObjectX::Init();

	return S_OK;
}

//--------------------------------------------------------------
// ������(�I�[�o�[���[�h)
//--------------------------------------------------------------
HRESULT CItemModel::Init(int inId)
{
	CObjectX::Init();

	LoadModel(m_modelData[inId]);
	m_ID = inId;
	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CItemModel::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CItemModel::Update()
{
	CObjectX::Update();
}

//--------------------------------------------------------------
// �`��
//--------------------------------------------------------------
void CItemModel::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CItemModel* CItemModel::Create(const D3DXVECTOR3& inPos, int inId)
{
	CItemModel* pItemModel = nullptr;
	pItemModel = new CItemModel;

	if (pItemModel != nullptr)
	{
		pItemModel->Init(inId);
		pItemModel->SetPos(inPos);
		pItemModel->m_collision = CCollisionSphere::Create(inPos, TAKE_RANGE);

	}

	return pItemModel;
}
