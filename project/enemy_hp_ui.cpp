//**************************************************************
//
// 敵の体力表示
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
// 定数
//--------------------------------------------------------------
const D3DXVECTOR3 CEnemy_HPUI::GAGE_SIZE	(10.0f, 1.0f, 0.0f);
const int CEnemy_HPUI::SUB_TIMING			(15);
const int CEnemy_HPUI::SUB_TIME				(10);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CEnemy_HPUI::CEnemy_HPUI() :
	m_pEnemy(nullptr),
	m_isDamege(false),
	m_subTimingCount(0),
	m_canSub(false),
	m_subTimeCount(0),
	m_perHP(0.0f),
	m_perDamage(0.0f),
	m_volumeSubPerDamage(0),	// 1フレームで削る量
	m_outline(nullptr),			// 背景(白)
	m_background(nullptr),		// 背景(黒)
	m_gageHP(nullptr),			// 現体力
	m_gageDamage(nullptr)		// 受けたダメージ
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

	m_outline = new CObjectPolygon3D();
	m_outline->Init();
	m_outline->SetBillboard(true);
	m_outline->SetSize(D3DXVECTOR3(GAGE_SIZE.x + 1.25f, GAGE_SIZE.y + 0.75f, 0.0f));
	m_outline->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_outline->SetPriority(CTaskGroup::LEVEL_3D_1);

	m_background = new CObjectPolygon3D();
	m_background->Init();
	m_background->SetBillboard(true);
	m_background->SetSize(D3DXVECTOR3(GAGE_SIZE.x + 1.0f, GAGE_SIZE.y + 0.5f, 0.0f));
	m_background->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_background->SetPriority(CTaskGroup::LEVEL_3D_1);

	m_gageDamage = new CObjectPolygon3D;
	m_gageDamage->Init();
	m_gageDamage->SetAnchor(CObjectPolygon3D::ANCHOR_LEFT);
	m_gageDamage->SetBillboard(true);
	m_gageDamage->SetSize(GAGE_SIZE);
	m_gageDamage->SetColor(D3DXCOLOR(0.8f, 0.1f, 0.1f, 1.0f));
	m_gageDamage->SetPriority(CTaskGroup::LEVEL_3D_1);

	m_gageHP = new CObjectPolygon3D;
	m_gageHP->Init();
	m_gageHP->SetAnchor(CObjectPolygon3D::ANCHOR_LEFT);
	m_gageHP->SetBillboard(true);
	m_gageHP->SetSize(GAGE_SIZE);
	m_gageHP->SetColor(D3DXCOLOR(0.9f, 0.9f, 0.4f, 1.0f));
	m_gageHP->SetPriority(CTaskGroup::LEVEL_3D_1);

	SetEndChildren(m_outline);
	SetEndChildren(m_background);
	SetEndChildren(m_gageDamage);
	SetEndChildren(m_gageHP);

	m_perDamage = 1.0f;
	m_perHP = 1.0f;
	m_volumeSubPerDamage = 0;
	m_subTimingCount = 0;
	m_canSub = false;
	m_isDamege = false;
	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CEnemy_HPUI::Update()
{
	CObject::Update();
	
	D3DXVECTOR3 size = m_pEnemy->GetSize();
	D3DXMATRIX mtx,mtxTrans,mtxRot;

	D3DXMatrixIdentity(&mtx);

	D3DXVECTOR3 move = D3DXVECTOR3(-10, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mtxTrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	D3DXMATRIX mtxPearent;
	D3DXMatrixIdentity(&mtxPearent);

	D3DXVECTOR3 rot = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera()->GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxPearent, &mtxPearent, &mtxRot);

	D3DXVECTOR3 pos = m_pEnemy->GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxPearent, &mtxPearent, &mtxTrans);

	D3DXMatrixMultiply(&mtx, &mtx, &mtxPearent);

	// 位置の更新
	m_outline->SetPos(D3DXVECTOR3(mtxPearent._41, pos.y + size.y, mtxPearent._43));
	m_background->SetPos(D3DXVECTOR3(mtxPearent._41, pos.y + size.y, mtxPearent._43));
	m_gageDamage->SetPos(D3DXVECTOR3(mtx._41, pos.y + size.y, mtx._43));
	m_gageHP->SetPos(D3DXVECTOR3(mtx._41, pos.y + size.y, mtx._43));

	float max = (float)m_pEnemy->GetHp()->GetMax();
	float current = (float)m_pEnemy->GetHp()->GetCurrent();

	if (current <= 0)
	{
		SetDisplay(false);
		current = 0;
	}

	float oldPer = m_perHP;
	m_perHP = current / max;

	if (oldPer != m_perHP)
	{
		m_isDamege = true;
		m_subTimingCount = 0;
	}

	if (m_isDamege)
	{
		m_subTimingCount++;
		if (m_subTimingCount > SUB_TIMING)
		{
			m_volumeSubPerDamage = (m_perDamage - m_perHP) / SUB_TIME;
			m_canSub = true;
		}
	}

	if (m_canSub)
	{
		m_subTimeCount++;

		m_perDamage -= m_volumeSubPerDamage;
		m_gageDamage->SetSize(D3DXVECTOR3(GAGE_SIZE.x * m_perDamage, GAGE_SIZE.y, 0.0f));
		if (m_subTimeCount >= SUB_TIME)
		{
			m_volumeSubPerDamage = 0;
			m_subTimeCount = 0;
			m_canSub = false;
			m_isDamege = false;
		}
	}
	m_gageHP->SetSize(D3DXVECTOR3(GAGE_SIZE.x * m_perHP, GAGE_SIZE.y, 0.0f));
}

//--------------------------------------------------------------
// 描画するか否か
//--------------------------------------------------------------
void CEnemy_HPUI::SetDisplay(bool display)
{
	m_outline->SetDisplay(display);
	m_background->SetDisplay(display);
	m_gageHP->SetDisplay(display);
	m_gageDamage->SetDisplay(display);
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
		pObject->SetEnemy(enemy);
		pObject->Init();
		pObject->SetPriority(CTaskGroup::LEVEL_DEBUG);
	}

	return pObject;
}
