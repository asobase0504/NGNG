//**************************************************************
//
// ポリゴンバレット
// Author : 冨所知生
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "enemy_hp_ui.h"
#include "character.h"
#include "utility.h"
#include "application.h"
#include "collision.h"
#include "collision_cylinder.h"
#include "abnormal.h"
#include "abnormal_data_base.h"
#include "player_manager.h"
#include "game.h"
#include "application.h"
#include "camera_game.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CEnemy_HPUI::CEnemy_HPUI()
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CEnemy_HPUI::~CEnemy_HPUI()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CEnemy_HPUI::Init()
{
	CObject::Init();

	m_background = new CObjectPolygon3D();
	m_background->Init();
	m_background->SetPriority(CTaskGroup::LEVEL_2D_UI);
	m_background->SetAnchor(CObjectPolygon3D::ANCHOR_LEFT);
	m_background->SetBillboard(true);
	m_background->SetSize(D3DXVECTOR3(11.0f, 2.0f, 0.0f));
	m_background->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_background->SetPriority(CTaskGroup::LEVEL_2D_2);

	m_gage = new CObjectPolygon3D;
	m_gage->Init();
	m_gage->SetPriority(CTaskGroup::LEVEL_DEBUG);
	m_gage->SetAnchor(CObjectPolygon3D::ANCHOR_LEFT);
	m_gage->SetBillboard(true);
	m_gage->SetSize(D3DXVECTOR3(10.0f, 1.0f, 0.0f));
	m_gage->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetEndChildren(m_gage);
	SetEndChildren(m_background);
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CEnemy_HPUI::Update()
{
	CObject::Update();
	
	D3DXVECTOR3 pos = m_pEnemy->GetPos();
	D3DXVECTOR3 size = m_pEnemy->GetSize();
	D3DXMATRIX mtx,mtxTrans,mtxRot;

	D3DXMatrixIdentity(&mtx);

	D3DXVECTOR3 move = D3DXVECTOR3(-10, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mtxTrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	D3DXVECTOR3 rot = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera()->GetRot();

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	m_gage->SetPos(D3DXVECTOR3(mtx._41, pos.y + size.y, mtx._43));

	m_background->SetPos(D3DXVECTOR3(mtx._41, pos.y + size.y, mtx._43));

	float max = (float)m_pEnemy->GetHp()->GetMax();
	float current = (float)m_pEnemy->GetHp()->GetCurrent();

	if (current <= 0)
	{
		m_background->SetDisplay(false);
		m_gage->SetDisplay(false);
		current = 0;
	}

	float per = current / max;

	m_gage->SetSize(D3DXVECTOR3(10.0f * per, 1.0f, 0.0f));
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CEnemy_HPUI* CEnemy_HPUI::Create(CCharacter* enemy)
{
	CEnemy_HPUI* pObject = nullptr;
	pObject = new CEnemy_HPUI();

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetEnemy(enemy);
		pObject->SetPriority(CTaskGroup::LEVEL_DEBUG);
	}

	return pObject;
}
