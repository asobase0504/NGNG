//**************************************************************
//
// ポリゴンバレット
// Author : 冨所知生
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "ui_3D.h"
#include "utility.h"
#include "application.h"
#include "game.h"
#include "camera_game.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CUI3D::CUI3D()
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CUI3D::~CUI3D()
{
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CUI3D::Update()
{
	CObject::Update();

	D3DXVECTOR3 pos = *m_targetPos;
	D3DXMATRIX mtx, mtxTrans, mtxRot;

	D3DXMatrixIdentity(&mtx);

	D3DXVECTOR3 move = D3DXVECTOR3(m_shift.x, 0.0f, m_shift.z);
	D3DXMatrixTranslation(&mtxTrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	D3DXVECTOR3 rot = ((CGame*)CApplication::GetInstance()->GetModeClass())->GetCamera()->GetRot();

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	SetPos(D3DXVECTOR3(mtx._41, pos.y + m_shift.y, mtx._43));
}
