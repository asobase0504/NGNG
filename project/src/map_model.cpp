//**************************************************************
//
// マップのモデル
// Author : Buriya Kota
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "map_model.h"
#include "collision_box.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CMapModel::CMapModel(CTaskGroup::EPriority list) :
	m_collisionBox(nullptr)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CMapModel::~CMapModel()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CMapModel::Init()
{
	CObjectX::Init();

	return S_OK;
}

//--------------------------------------------------------------
// 初期化(オーバーロード)
//--------------------------------------------------------------
HRESULT CMapModel::Init(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot, const D3DXVECTOR3& inSize)
{
	CObjectX::Init();

	D3DXMATRIX mtx = GetMtxWorld();
	m_collisionBox = CCollisionBox::Create(inPos, inRot, inSize, mtx);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CMapModel::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CMapModel::Update()
{
	CObjectX::Update();

	D3DXMATRIX mtx = GetMtxWorld();
	m_collisionBox->SetMtxWorld(mtx);
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CMapModel::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------------------
// 生成
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
