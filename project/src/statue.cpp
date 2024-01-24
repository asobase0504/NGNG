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
#include "PlayerController.h"
#include "map.h"
#include "object_mesh.h"
#include "statue_manager.h"
#include "application.h"
#include "game.h"
#include "utility.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatue::CStatue()
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
	CSelectEntity::Init();
	return S_OK;
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CStatue::Init(const D3DXVECTOR3 & inPos, const D3DXVECTOR3 & inRot)
{
	m_pMark = nullptr;

	CSelectEntity::Init();

	m_collisionBox = CCollisionBox::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), inRot, D3DXVECTOR3(10.0f, 25.0f, 10.0f));
	m_collisionBox->SetMtxWorld(GetMtxWorld());
	m_collisionBox->SetParent(&m_pos);
	SetEndChildren(m_collisionBox);
	m_collisionCylinder->SetHeight(20.0f);
	m_collisionCylinder->SetLength(20.0f);

	UpMesh();

	// 向きの設定
	AddRot(D3DXVECTOR3(0.0f, FloatRandom(D3DX_PI, -D3DX_PI), 0.0f));

	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CStatue::Update()
{
	CSelectEntity::Update();

	if (m_pMark != nullptr)
	{
		D3DXVECTOR3 pos = GetPos();
		m_pMark->SetPos(D3DXVECTOR3(pos.x, pos.y + 120.0f, pos.z));
	}

#ifdef _DEBUG
#if 0
	CDebugProc::Print("StatueCollisionBox:pos(%f,%f,%f)\n", m_collisionBox->GetPosWorld().x, m_collisionBox->GetPosWorld().y, m_collisionBox->GetPosWorld().z);
	CDebugProc::Print("StatueCollisionCylinder:pos(%f,%f,%f)\n", m_collisionCylinder->GetPosWorld().x, m_collisionCylinder->GetPosWorld().y, m_collisionCylinder->GetPosWorld().z);
#endif
#endif // _DEBUG
}

//--------------------------------------------------------------
// タッチ
//--------------------------------------------------------------
bool CStatue::Touch()
{
	if (m_collisionCylinder == nullptr)
	{
		return false;
	}

	CInput* input = CInput::GetKey();
	if (input->Trigger(DIK_E))
	{
		CGame* game = (CGame*)CApplication::GetInstance()->GetModeClass();
		CPlayer* player = game->GetController()->GetToOrder();
		if (m_collisionCylinder->ToCylinder(player->GetCollision()))
		{
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------
// 向きの設定
//--------------------------------------------------------------
void CStatue::SetRot(const D3DXVECTOR3 & inRot)
{
	CSelectEntity::SetRot(inRot);
	m_collisionBox->SetRot(inRot);
}

//--------------------------------------------------------------
// 上に上げる処理
//--------------------------------------------------------------
void CStatue::UpMesh()
{
	CMap* map = CApplication::GetInstance()->GetMap();
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

}

//--------------------------------------------------------------
// マーカーの設置/タイプ設定
//--------------------------------------------------------------
void CStatue::SetMark(std::string inKey)
{
	D3DXVECTOR3 pos = GetPos();

	m_pMark = CObjectPolygon3D::Create(CTaskGroup::EPriority::LEVEL_2D_1);
	m_pMark->SetAnchor(CObjectPolygon3D::EAnchor::ANCHOR_CENTER);
	m_pMark->SetBillboard(true);
	m_pMark->SetSize(D3DXVECTOR3(20.0f,20.0f,0.0f));
	m_pMark->SetPos(D3DXVECTOR3(pos.x, pos.y + 120.0f, pos.z));
	m_pMark->SetColor(D3DXCOLOR(1.0f,1.0f,1.0f, 1.0f));
	m_pMark->SetTexture(inKey);
	SetEndChildren(m_pMark);
}

//--------------------------------------------------------------
// マーカーの削除
//--------------------------------------------------------------
void CStatue::DeleteMark()
{
	// マークの終了処理
	m_pMark->Uninit();
	m_pMark = nullptr;
}