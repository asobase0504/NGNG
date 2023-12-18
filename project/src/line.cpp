//**************************************************************
//
// ライン描画処理(line.h)
// Author : 唐﨑結斗
// 概要 : ライン生成を行う
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "line.h"
#include "renderer.h"
#include "application.h"


bool CLine::m_alldisplay = true;

//--------------------------------------------------------------
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : 2Dオブジェクトを生成する
//--------------------------------------------------------------
CLine* CLine::Create()
{
	// オブジェクトインスタンス
	CLine *pLine = nullptr;

	// メモリの解放
	pLine = new CLine;

	// メモリの確保ができなかった
	assert(pLine != nullptr);

	// 数値の初期化
	pLine->Init();

	// インスタンスを返す
	return pLine;
}

//--------------------------------------------------------------
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//--------------------------------------------------------------
CLine::CLine() :
	CObject(CTaskGroup::EPriority::LEVEL_3D_1)
{
	m_vtxBuff = nullptr;						// 頂点バッファ
	m_mtxWorld = {};							// ワールドマトリックス
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 大きさ
	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 始点
	m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 終点
}

//--------------------------------------------------------------
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//--------------------------------------------------------------
CLine::~CLine()
{
}

//--------------------------------------------------------------
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//--------------------------------------------------------------
HRESULT CLine::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();		//デバイスへのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,									// 頂点ファーマット
		D3DPOOL_MANAGED,
		&m_vtxBuff,
		NULL);

	assert(m_vtxBuff != nullptr);

	// ポリゴン情報の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 大きさ

	// 頂点座標の設定
	SetVtx();

	// 色の設定
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//--------------------------------------------------------------
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//--------------------------------------------------------------
void CLine::Uninit()
{
	//頂点バッファを破棄
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();

		m_vtxBuff = nullptr;
	}

	CObject::Uninit();
}

//--------------------------------------------------------------
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//--------------------------------------------------------------
void CLine::Update()
{
	CObject::Update();
	m_pos = *m_targetPos;
	m_rot = *m_targetRot;
	SetVtx();
}

//--------------------------------------------------------------
// 描画
// Author : 唐﨑結斗
// 概要 : 2D描画を行う
//--------------------------------------------------------------
void CLine::Draw()
{
	if (!m_isDisplay || !m_alldisplay)
	{
		return;
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();		//デバイスへのポインタ

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	D3DXMatrixIdentity(&m_mtxWorld);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);		// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// Zテストを使用する
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// Zテストの設定
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);

	// αテストを使用する
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// αテストの設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ライトを無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ライン描画
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	// ライトを有効	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Zテストの終了
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// αテストの終了
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// テクスチャの解除
	pDevice->SetTexture(0, nullptr);
}

//--------------------------------------------------------------
// 頂点座標などの設定
// Author : 唐﨑結斗
// 概要 : 3D頂点座標、rhw、頂点カラーを設定する
//--------------------------------------------------------------
void CLine::SetVtx()
{
	//頂点情報へのポインタを生成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = m_start;
	pVtx[1].pos = m_goal;

	// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点バッファをアンロック
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// 頂点カラーの設定
// Author : 唐﨑結斗
// 概要 : 頂点カラーを設定する
//--------------------------------------------------------------
void CLine::SetColor(const D3DXCOLOR& color)
{
	CObject::SetColor(color);

	//頂点情報へのポインタを生成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;

	//頂点バッファをアンロック
	m_vtxBuff->Unlock();
}

//--------------------------------------------------------------
// 頂点カラーの設定
// Author : 唐﨑結斗
// 概要 : 頂点カラーを設定する
//--------------------------------------------------------------
void CLine::SetLine(D3DXVECTOR3 start, D3DXVECTOR3 goal)
{
	// 始点
	m_start = start;

	// 終点
	m_goal = goal;

	// 頂点座標の設定
	SetVtx();
}
