//**************************************************************
//
// 僁E
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

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatue::CStatue(CTaskGroup::EPriority list) :
	m_modelData("BOX")
{
}

//--------------------------------------------------------------
// チE��トラクタ
//--------------------------------------------------------------
CStatue::~CStatue()
{
}

//--------------------------------------------------------------
// 初期匁E
//--------------------------------------------------------------
HRESULT CStatue::Init()
{
	CObjectX::Init();
	m_collisionBox = CCollisionBox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRot(),D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	m_collisionCylinder = CCollisionCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f);
	LoadModel(m_modelData);

	return S_OK;
}

//--------------------------------------------------------------
// 終亁E
//--------------------------------------------------------------
void CStatue::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CStatue::Update()
{
	m_collisionBox->SetPos(GetPos());
	m_collisionCylinder->SetPos(GetPos());

	bool a = CPlayerManager::GetInstance()->GetPlayerCylinder()->ToBox(m_collisionBox, true);

	if (a)
	{
		// 押し�Eした位置
		D3DXVECTOR3 extrusion = CPlayerManager::GetInstance()->GetPlayerCylinder()->GetExtrusion();
		CPlayerManager::GetInstance()->GetPlayer()->SetPos(D3DXVECTOR3(extrusion));
		CPlayerManager::GetInstance()->GetPlayerCylinder()->SetPos(D3DXVECTOR3(extrusion));

		CPlayerManager::GetInstance()->GetPlayer()->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	CObjectX::Update();

#ifdef _DEBUG
	CDebugProc::Print("StatueCollisionBox�E�pos(%f,%f,%f)\n", m_collisionBox->GetPos().x, m_collisionBox->GetPos().y, m_collisionBox->GetPos().z);
	CDebugProc::Print("StatueCollisionCylinder�E�pos(%f,%f,%f)\n", m_collisionCylinder->GetPos().x, m_collisionCylinder->GetPos().y, m_collisionCylinder->GetPos().z);
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
// 生�E
//--------------------------------------------------------------
CStatue* CStatue::Create(const D3DXVECTOR3& inPos, const D3DXVECTOR3& inRot)
{
	CStatue* pStatue = nullptr;
	pStatue = new CStatue;

	if (pStatue != nullptr)
	{
		pStatue->Init();
		pStatue->SetPos(inPos);
		pStatue->m_collisionBox = CCollisionBox::Create(inPos, inRot, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		pStatue->m_collisionCylinder = CCollisionCylinder::Create(inPos,15.0f, 15.0f);
	}

	return pStatue;
}

bool CStatue::Touch(CPlayer* pPlayer)
{
	if (m_collisionCylinder->ToCylinder(pPlayer->GetCylinder()))
	{
		return true;
	}

	return false;
}