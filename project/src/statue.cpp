//**************************************************************
//
// 像
// Author: 梶田 大夢
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "statue.h"
#include "collision_box.h"
#include "player_manager.h"
#include "player.h"
#include "map.h"
#include "object_mesh.h"
#include "statue_manager.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatue::CStatue() :
	CObjectX(CTaskGroup::EPriority::LEVEL_3D_1),
	m_modelData("BOX"),
	m_player(nullptr)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatue::~CStatue()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CStatue::Init()
{
	CObjectX::Init();

	D3DXMATRIX mtx = GetMtxWorld();
	m_collisionBox = CCollisionBox::Create(GetPos(), GetRot(),D3DXVECTOR3(10.0f, 10.0f, 10.0f), mtx);
	m_collisionCylinder = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f);

	LoadModel(m_modelData);

	return S_OK;
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CStatue::Init(const D3DXVECTOR3 & inPos, const D3DXVECTOR3 & inRot)
{
	CObjectX::Init();
	LoadModel(m_modelData);

	m_collisionBox = CCollisionBox::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), inRot, D3DXVECTOR3(10.0f, 25.0f, 10.0f), GetMtxWorld());
	m_collisionBox->SetParent(&m_pos);
	m_collisionCylinder = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 20.0f);
	m_collisionCylinder->SetParent(&m_pos);

	CMap* map = CMap::GetMap();
	D3DXVECTOR3 pos = GetPos();

	// 上に上げる処理
	CCollisionCylinder* pCylinder = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f);
	pCylinder->SetParent(&m_pos);

	for (int i = 0; i < map->GetNumMesh(); i++)
	{
		bool hit = pCylinder->ToMesh(map->GetMapMesh(i)->GetCollisionMesh());

		if (hit)
		{// 押し出した位置
			float extrusion = ((CCollisionCylinder*)pCylinder)->GetPosWorld().y;
			SetPos(D3DXVECTOR3(pos.x, extrusion, pos.z));
		}
	}
	pCylinder->Uninit();

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CStatue::Uninit()
{
	if (m_collisionBox != nullptr)
	{
		m_collisionBox->Uninit();
		m_collisionBox = nullptr;
	}
	if (m_collisionCylinder != nullptr)
	{
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;
	}
	
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CStatue::Update()
{
	CObjectX::Update();

	m_collisionBox->SetMtxWorld(GetMtxWorld());

#ifdef _DEBUG
#if 0
	CDebugProc::Print("StatueCollisionBox:pos(%f,%f,%f)\n", m_collisionBox->GetPosWorld().x, m_collisionBox->GetPosWorld().y, m_collisionBox->GetPosWorld().z);
	CDebugProc::Print("StatueCollisionCylinder:pos(%f,%f,%f)\n", m_collisionCylinder->GetPosWorld().x, m_collisionCylinder->GetPosWorld().y, m_collisionCylinder->GetPosWorld().z);
#endif
#endif // _DEBUG
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CStatue::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatue* CStatue::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3 & inRot)
{
	CStatue* pStatue = nullptr;
	pStatue = new CStatue;

	if (pStatue != nullptr)
	{
		pStatue->Init(inPos,inRot);
	}

	return pStatue;
}

bool CStatue::Touch(CPlayer* pPlayer)
{
	if (m_collisionCylinder->ToCylinder((CCollisionCylinder*)pPlayer->GetCollision()))
	{
		return true;
	}

	return false;
}