//**************************************************************
//
// Object
// Author : Hamada Ryuuga
// AUthor : Yuda Kaito
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "object_polygon3d.h"
#include "application.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "renderer.h"
#include "texture.h"

//==============================================================
// 頂点情報
//==============================================================
const D3DXVECTOR3 CObjectPolygon3D::m_Vtx[ANCHOR_MAX][4] =
{
	{
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	},
	{
		D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(+2.0f, -1.0f, 0.0f),
		D3DXVECTOR3(0.0f, +1.0f, 0.0f),
		D3DXVECTOR3(+2.0f, +1.0f, 0.0f),
	}
};

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CObjectPolygon3D::CObjectPolygon3D(CTaskGroup::EPriority list) :
	CObject(list,CTaskGroup::EPushMethod::PUSH_CURRENT),
	m_vtxBuff(nullptr)
{
	D3DXMatrixIdentity(&m_mtxWorld);
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CObjectPolygon3D::~CObjectPolygon3D()
{
}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CObjectPolygon3D::Init()
{
	SetType(CObject::EType::POLYGON);
	SetBillboard(false);

	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetInstance()->GetDevice();	// デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_vtxBuff,
		NULL);

	VERTEX_3D* pVtx;	// 頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点カラー設定
	for (int i = 0; i < 4; i++)
	{
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	m_vtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CObjectPolygon3D::Uninit()
{
	// 破棄
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}
	Release();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CObjectPolygon3D::Update()
{
}

//--------------------------------------------------------------
// 描画
//--------------------------------------------------------------
void CObjectPolygon3D::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CRenderer::GetInstance()->GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans, mtxView;	;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bBill)
	{// ビルボードの使用
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// カメラの逆行列を設定
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}
	else
	{
		// 向きを反映							↓rotの情報を使って回転行列を作る
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);		// 行列掛け算関数		第二引数 * 第三引数 を　第一引数に格納
	}

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの取得
	CTexture* pTexture = CTexture::GetInstance();

	// テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_textureKey));

	// αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ライトを無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//ポリゴンの形
		0,										//頂点の開始場所
		4);

	// ライトを有効	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//カリングの設定を元に戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CObjectPolygon3D* CObjectPolygon3D::Create(CTaskGroup::EPriority list)
{
	CObjectPolygon3D* pObject = nullptr;
	pObject = new CObjectPolygon3D(list);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//--------------------------------------------------------------
// セットテクスチャ(2d)
//--------------------------------------------------------------
void CObjectPolygon3D::SetTex(PositionVec4 Tex)
{
	VERTEX_3D *pVtx; //頂点へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(Tex.P0, Tex.P2);
	pVtx[1].tex = D3DXVECTOR2(Tex.P1, Tex.P2);
	pVtx[2].tex = D3DXVECTOR2(Tex.P0, Tex.P3);
	pVtx[3].tex = D3DXVECTOR2(Tex.P1, Tex.P3);

	//頂点バッファをアンロック
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// 位置の設定
//--------------------------------------------------------------
void CObjectPolygon3D::SetPos(const D3DXVECTOR3& inPos)
{
	CObject::SetPos(inPos);

	// マトリックスの計算
	GiftMtx(&m_mtxWorld, m_pos, m_rot);
}

//--------------------------------------------------------------
// 向きの設定
//--------------------------------------------------------------
void CObjectPolygon3D::SetRot(const D3DXVECTOR3& inRot)
{
	CObject::SetRot(inRot);

	// マトリックスの計算
	GiftMtx(&m_mtxWorld, m_pos, m_rot);
}

//--------------------------------------------------------------
// 大きさの設定
//--------------------------------------------------------------
void CObjectPolygon3D::SetSize(const D3DXVECTOR3 &size)
{
	CObject::SetSize(size);

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// 頂点情報の設定
	//------------------------
	for (int i = 0; i < 4; ++i)
	{
		pVtx[i].pos.x = m_Vtx[m_anchor][i].x * GetSize().x;
		pVtx[i].pos.y = m_Vtx[m_anchor][i].y * GetSize().y;
		pVtx[i].pos.z = m_Vtx[m_anchor][i].z * GetSize().z;
	}

	//頂点バッファをアンロックする
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// 色の設定
//--------------------------------------------------------------
void CObjectPolygon3D::SetColor(const D3DXCOLOR& Collar)
{
	CObject::SetColor(Collar);

	VERTEX_3D *pVtx; //頂点へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXCOLOR color(GetColor());

	//テクスチャの座標設定
	//頂点カラーの設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//頂点バッファをアンロック
	m_vtxBuff->Unlock();
}
