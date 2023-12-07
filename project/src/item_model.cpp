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
CItemModel::CItemModel()
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
	LoadModel("BOX");
	CSelectEntity::Init();

	return S_OK;
}

//--------------------------------------------------------------
// 初期化(オーバーロード)
//--------------------------------------------------------------
HRESULT CItemModel::Init(int inId)
{
	CSelectEntity::Init();
	
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	D3DXVec3TransformCoord(&move, &move, &m_mtx);

	SetMove(D3DXVECTOR3(move.x,move.y,-move.z));

	CItem *item = CItemDataBase::GetInstance()->GetItemData((CItemDataBase::EItemType)inId);

	LoadModel(item->GetModel());

	m_collisionCylinder->SetHeight(20.0f);
	m_collisionCylinder->SetLength(20.0f);
	m_collisionHit = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f,20.0f);
	m_collisionHit->SetParent(&m_pos);

	m_ID = inId;
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CItemModel::Update()
{
	if (m_collisionHit != nullptr)
	{
		bool isGround = false;
		CMap* map = CMap::GetMap();

		for (int i = 0; i < map->GetNumMesh(); i++)
		{
			if (m_collisionHit->ToMesh(map->GetMapMesh(i)->GetCollisionMesh()))
			{// 押し出した位置
				D3DXVECTOR3 extrusion = m_collisionHit->GetPosWorld();
				SetPos(extrusion);
				isGround = true;
			}
		}

		if (isGround)
		{
			m_collisionHit->Uninit();
			m_collisionHit = nullptr;
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			AddMove(D3DXVECTOR3(0.0f, -0.1f, 0.0f));
		}
	}

	CSelectEntity::Update();
}

//--------------------------------------------------------------
// 選択したとき
//--------------------------------------------------------------
bool CItemModel::Select(CCharacter * selectCharacter)
{
	selectCharacter->TakeItem(m_ID);
	CMap::GetMap()->RemoveSelectEntityList(this);
	Uninit();
	return false;
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
