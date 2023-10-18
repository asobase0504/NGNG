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
// コンストラクタ
//--------------------------------------------------------------
CItemModel::CItemModel(CTaskGroup::EPriority list) :
	m_modelData{
	"BOX", }
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CItemModel::~CItemModel()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CItemModel::Init()
{
	CObjectX::Init();

	return S_OK;
}

//--------------------------------------------------------------
// 初期化(オーバーロード)
//--------------------------------------------------------------
HRESULT CItemModel::Init(int inId)
{
	CObjectX::Init();

	LoadModel(m_modelData[inId]);
	m_ID = inId;
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CItemModel::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CItemModel::Update()
{
	CObjectX::Update();
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CItemModel::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------------------
// 生成
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
