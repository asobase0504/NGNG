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
#include "collision_cylinder.h"
#include "map.h"
#include "map_model.h"
#include "collision_mesh.h"
#include "object_mesh.h"
#include "item_data_base.h"
#include "item.h"

const float CItemModel::TAKE_RANGE(10.0f);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CItemModel::CItemModel(CTaskGroup::EPriority list)
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
	
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	D3DXVec3TransformCoord(&move, &move, &m_mtx);

	SetMove(D3DXVECTOR3(move.x,move.y,-move.z));

	CItem *item = CItemDataBase::GetInstance()->GetItemData((CItemDataBase::EItemType)inId);

	LoadModel(item->GetModel());

	m_collisionTake = CCollisionSphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f);
	m_collisionTake->SetParent(&m_pos);
	m_collisionHit = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f,20.0f);
	m_collisionHit->SetParent(&m_pos);

	m_ID = inId;
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CItemModel::Uninit()
{
	m_collisionTake->Uninit();

	CObjectX::Uninit();

	m_collision->Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CItemModel::Update()
{
	bool isGround = false;

	CMap* map = CMap::GetMap();
	D3DXVECTOR3 pos = GetPos();

	for (int i = 0; i < map->GetNumMesh(); i++)
	{
		if (m_collisionHit->ToMesh(map->GetMapMesh(i)->GetCollisionMesh()))
		{// 押し出した位置
			D3DXVECTOR3 extrusion = m_collisionHit->GetPosWorld();
			SetPos(extrusion);
			isGround = true;
		}
	}

	D3DXVECTOR3 move = GetMove();

	if (!isGround)
	{
		move.y -= 0.1f;
	}
	else
	{
		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	SetMove(move);

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
CItemModel* CItemModel::Create(const D3DXVECTOR3& inPos, const D3DXMATRIX& boxmtx, int inId)
{
	CItemModel* pItemModel = nullptr;
	pItemModel = new CItemModel;

	if (pItemModel != nullptr)
	{
		pItemModel->SetVec(boxmtx);
		pItemModel->Init(inId);
		pItemModel->SetPos(inPos);
	}

	return pItemModel;
}
