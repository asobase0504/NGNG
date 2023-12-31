﻿//**************************************************************
//
// ポリゴンバレット
// Author : 冨所知生
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "bullet.h"
#include "character.h"
#include "utility.h"
#include "application.h"
#include "collision.h"
#include "collision_cylinder.h"
#include "abnormal.h"
#include "abnormal_data_base.h"
#include "player.h"
#include "player_manager.h"
#include "map.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CBullet::CBullet() : m_life(100)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CBullet::Init()
{
	CObjectPolygon3D::Init();
	SetAnchor(CObjectPolygon3D::ANCHOR_CENTER);
	SetBillboard(true);
	SetSize(D3DXVECTOR3(10.0f,10.0f,0.0f));
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CBullet::Uninit()
{
	CObjectPolygon3D::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CBullet::Update()
{
	CObjectPolygon3D::Update();

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&move,&GetMove());
	move *= m_speed;

	// 移動
	AddPos(move);

	m_life--;

	if (m_life <= 0)
	{
		Uninit();
	}
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CBullet::Draw()
{
	CObjectPolygon3D::Draw();
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float speed)
{
	CBullet* pObject = nullptr;
	pObject = new CBullet();

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(pos);
		pObject->SetMove(move);
		pObject->SetSpeed(speed);
	}

	return pObject;
}
