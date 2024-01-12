//**************************************************************
//
// 攻撃のRoad
// Author : 冨所知生
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "road.h"
#include "character.h"
#include "utility.h"
#include "application.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CRoad::CRoad()
{
	m_shooter = nullptr;
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CRoad::~CRoad()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CRoad::Init()
{
	CObjectPolygon3D::Init();
	SetAnchor(CObjectPolygon3D::ANCHOR_LEFT);
	m_col = GetColor();
	m_isuse = false;

	SetBillboard(false);

	return S_OK;
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CRoad::Update()
{
	CObjectPolygon3D::Update();

	if (m_target != nullptr && !m_target->IsDied() && m_shooter != nullptr)
	{
		D3DXVECTOR3 pos = m_shooter->GetPos();
		
		// 座標の設定
		SetPos(m_shooter->GetPos());

		// 距離と方向を求める
		float distance;
		D3DXVECTOR3 ShooterPos = m_shooter->GetPos();
		D3DXVECTOR3 TargetPos = m_target->GetPos();
		D3DXVECTOR3 Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

		D3DXVECTOR3 D3distance = ShooterPos - TargetPos;
		distance = D3DXVec3Length(&D3distance) * 0.5f;

		Rot.x = atan2f((ShooterPos.z - TargetPos.z), (ShooterPos.y - TargetPos.y));
		Rot.y = -atan2f((-ShooterPos.z - -TargetPos.z), (-ShooterPos.x - -TargetPos.x));

		NormalizeAngle(Rot.x);
		NormalizeAngle(Rot.y);

		SetSize(D3DXVECTOR3(distance, 1.0f, 0.0f));
		SetRot(Rot);
	}

	if (!m_isuse)
	{
		SetColor(D3DXCOLOR(m_col.r, m_col.b, m_col.g, 0.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(m_col.r, m_col.b, m_col.g, 1.0f));
	}
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CRoad::Draw()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// レンダーステートの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CObjectPolygon3D::Draw();

	// レンダーステートの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CRoad* CRoad::Create(D3DXCOLOR col)
{
	CRoad* pObject = nullptr;
	pObject = new CRoad();

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetColor(col);
	}

	return pObject;
}
