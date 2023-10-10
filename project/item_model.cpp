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
	return S_OK;
}

//--------------------------------------------------------------
// ������(�I�[�o�[���[�h)
//--------------------------------------------------------------
HRESULT CItemModel::Init(int inId)
{
#define ARRAY_LENGTH(a) (sizeof(a)/sizeof((a)[0])) 
	static_assert(ARRAY_LENGTH(m_modelData) == MODEL_MAX, "aho");

	//LoadModel(m_modelData[inId]);

	return S_OK;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CItemModel* CItemModel::Create(int inId)
{
	CItemModel* pItemModel = nullptr;
	pItemModel = new CItemModel;

	if (pItemModel != nullptr)
	{
		pItemModel->Init(inId);
	}

	return pItemModel;
}