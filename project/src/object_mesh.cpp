//**************************************************************
//
// メッシュ設定(まっすぐ)
// Author:hamada ryuuga
//
//**************************************************************

//==============================================================
// include
//==============================================================
#include "object_mesh.h"
#include "application.h"
#include "collision_mesh.h"
#include "player.h"
#include "player_manager.h"
#include "utility.h"

//==============================================================
// 定数
//==============================================================
const float CMesh::MOUNTAIN(50.0f);
const float CMesh::RADIUS(1000.0f);
const int CMesh::START_HORIZONTAL(30);
const int CMesh::START_VERTICAL(15);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CMesh::CMesh(CTaskGroup::EPriority nPriority) :
	CObjectPolygon3D(CTaskGroup::EPriority::LEVEL_3D_1),
	m_xsiz(0),			// X軸の面数
	m_zsiz(0),			// Y軸の面数
	m_vtxCountX(0),		// X軸の辺の頂点数
	m_vtxCountZ(0),		// Y軸の辺の頂点数
	m_vtx(0),			// 頂点数
	m_index(0),			// インデックス
	m_polygonCount(0),
	m_isCollision(true),
	m_collisionMesh(nullptr),
	m_sphereRange(D3DXVECTOR2(0.0f, 0.0f)),		// 球の描画範囲
	m_fRadius(0.0f),// 半径
	m_isCulling(false)
{
	m_meshSize = { 100.0f,0.0f,100.0f };
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CMesh::~CMesh()
{
}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CMesh::Init()
{
	// 初期化処理
	m_vtxBuff = nullptr;		// 頂点バッファーへのポインタ
	m_idxBuff = nullptr;		// インデックスバッファ

	// 初期値の設定
	m_sphereRange = D3DXVECTOR2(D3DX_PI * 2.0f, D3DX_PI * 0.5f);
	m_fRadius = RADIUS;

	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CMesh::Uninit()
{
	// バッファーの解放
	if (m_idxBuff != nullptr)
	{
		m_idxBuff->Release();
		m_idxBuff = nullptr;
	}

	CObjectPolygon3D::Uninit();
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CMesh::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	//-------------------------------------------------
	// シェーダの設定
	//-------------------------------------------------
	extern LPD3DXEFFECT pEffect;		// シェーダー

	if (pEffect == nullptr)
	{
		assert(false);
		return;
	}

	if (m_TimeCnt > 0)
	{
		m_TimeCnt--;
	}
	if (m_TimeCnt <= m_TimeTarget)
	{
		m_TimeCnt++;
	}

	// ワイヤーフレーム
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	//ライト設定falseにするとライトと食らわない
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (m_isCulling)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファ設定
	pDevice->SetIndices(m_idxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの取得
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(GetTexture()));

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_vtx, 0, m_polygonCount);

	//テクスチャの設定
	pDevice->SetTexture(0, nullptr);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//--------------------------------------------------------------
// Create関数
//--------------------------------------------------------------
CMesh* CMesh::Create()
{
	CMesh* pObject = new CMesh;

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//--------------------------------------------------------------
// 当たり判定
// Author: hamada ryuuga
// Aythor: Yuda Kaito
//--------------------------------------------------------------
bool CMesh::Collision(D3DXVECTOR3* pPos)
{
	bool bIsLanding = false;
	const int nTri = 3;

	// 頂点座標をロック
	VERTEX_3D* pVtx = nullptr;
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファのロック
	WORD* pIdx;
	m_idxBuff->Lock(0, 0, (void**)&pIdx, 0);

	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DXMATRIX mtxWorld;

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&mtxWorld);

	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 行列掛け算関数(第2引数×第3引数を第１引数に格納)
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	for (int nCnt = 0; nCnt < m_polygonCount; nCnt++)
	{
		D3DXVECTOR3 posLineVec[nTri];

		posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
		posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
		posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{//縮退ポリゴンを省き
			continue;
		}

		for (int i = 0; i < nTri; i++)
		{//ベクトル３座標をマトリックスで変換する（乗算）
			D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
		}

		int  LineCout = 0;

		for (int i = 0; i < nTri; i++)
		{
			//ベクトルS2 V2												
			D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

			//ベクトル現在のPOSと始点までの距離
			D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

			//外積計算//辺１
			float vecLine = Vec2Cross(&vecPos, &vecWall);

			//三角の中に入ってるときの判定向きによって右側か左側か違うため判定を二つ用意する
			if (((nCnt & 1) == 0 && vecLine >= 0.0f) || ((nCnt & 1) != 0 && vecLine <= 0.0f))
			{
				LineCout++;
			}
			else
			{
				break;
			}
		}
		if (LineCout == nTri)
		{
			D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
			D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

			D3DXVECTOR3 Normal;
			//AとBの法線を求めるやつ
			D3DXVec3Cross(&Normal, &V1, &V2);

			//vecB をノーマライズして、長さ 1にする。
			D3DXVec3Normalize(&Normal, &Normal);

			D3DXVECTOR3 VecA = *pPos - posLineVec[0];
			//プレイヤーの位置補正
			SwitchCollision(true);
			OnHit();

			if (m_isCollision)
			{
				pPos->y = (posLineVec[0].y - (Normal.x*(pPos->x - posLineVec[0].x) + Normal.z*(pPos->z - posLineVec[0].z)) / Normal.y) + 10.0f;
			}
		}
	}
	// 頂点座標をアンロック
	m_vtxBuff->Unlock();
	// 頂点インデックスをアンロック
	m_idxBuff->Unlock();

	return bIsLanding;
}

//--------------------------------------------------------------
// メッシュの作成
// Author:hamada ryuuga
//--------------------------------------------------------------
bool CMesh::CreateMesh(D3DXVECTOR3* pPos)
{
	bool bIsLanding = false;

	VERTEX_3D* pVtx = nullptr;

	const int nTri = 3;

	// 頂点座標をロック
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスバッファのロック
	WORD* pIdx;
	m_idxBuff->Lock(0, 0, (void**)&pIdx, 0);

	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DXMATRIX mtxWorld;

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&mtxWorld);

	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	// 行列掛け算関数(第2引数×第3引数を第１引数に格納)
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	for (int nCnt = 0; nCnt < m_polygonCount; nCnt++)
	{
		D3DXVECTOR3 posLineVec[nTri];

		posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
		posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
		posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{//縮退ポリゴンを省き
			continue;
		}

		for (int i = 0; i < nTri; i++)
		{//ベクトル３座標をマトリックスで変換する（乗算）
			D3DXVec3TransformCoord(&posLineVec[i], &posLineVec[i], &mtxWorld);
		}

		int  LineCout = 0;

		for (int i = 0; i < nTri; i++)
		{
			//ベクトルS2 V2												
			D3DXVECTOR3 vecWall = posLineVec[(i + 1) % nTri] - posLineVec[i];

			//ベクトル現在のPOSと始点までの距離
			D3DXVECTOR3 vecPos = *pPos - posLineVec[i];

			//外積計算//辺１
			float vecLine = Vec2Cross(&vecPos, &vecWall);

			//三角の中に入ってるときの判定
			if ((nCnt % 2 == 0 && vecLine > 0.0f) ||
				(nCnt % 2 != 0 && vecLine < 0.0f))
			{
				LineCout++;
			}
			else
			{
				break;
			}
		}
	}

	// 頂点座標をアンロック
	m_vtxBuff->Unlock();
	// 頂点座標をアンロック
	m_idxBuff->Unlock();

	CMesh::SetVtxMeshLight();

	return bIsLanding;
}

void CMesh::SetY(std::vector<std::vector<float>> inY)
{
	SetVtxMeshSize(inY[0].size(), inY.size());	// サイズ決定
	SetVtxMeshLight();		// 法線設定

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int i = 0; i < (int)inY.size(); i++)
	{
		for (int j = 0; j < (int)inY[i].size(); j++)
		{
			// 座標の補正
			int size = j + i * (int)inY[i].size();
			pVtx[size].pos.y += inY[i][j] + FloatRandom(-10.0f,10.0f);
		}
	}

	// 頂点座標をアンロック
	m_vtxBuff->Unlock();

	SetVtxMeshLight();		// 法線設定
}

//--------------------------------------------------------------
// メッシュの作成
// Author:hamada ryuuga
//--------------------------------------------------------------
void CMesh::SetVtxMesh(VERTEX_3D* pVtx, WORD* pIdx,int nCnt,bool isUp)
{
	int sign = isUp ? 1 : -1;

	for (int i = 0; i < 3; i++)
	{
		int index = pIdx[nCnt + i];

		pVtx[index].pos.y += (MOUNTAIN * sign);
	}
}

//--------------------------------------------------------------
// 面の数を設定
//--------------------------------------------------------------
void CMesh::SetVtxMeshSize(int sizeX,int sizeZ)
{
	//CMesh::Uninit();
	//NotRelease();

	m_vtxCountX = sizeX;	// 頂点数
	m_vtxCountZ = sizeZ;	// 頂点数
	m_xsiz = sizeX - 1;		// 面の数
	m_zsiz = sizeZ - 1;		// 面の数

	// 頂点数
	m_vtx = m_vtxCountX * m_vtxCountZ;	// 頂点数を使ってるよ

	// インデックス数
	m_index = (2 * m_vtxCountX * m_zsiz + 2 * (m_zsiz - 1));

	m_polygonCount = m_index - 2;

	// 頂点バッファーの解放
	if (m_vtxBuff != nullptr)
	{
		m_vtxBuff->Release();
		m_vtxBuff = nullptr;
	}

	if (m_idxBuff != nullptr)
	{
		m_idxBuff->Release();
		m_idxBuff = nullptr;
	}

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_vtxBuff,
		NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_idxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int i = 0; i < m_vtx; i++)
	{
		float posx = (float)((i % m_vtxCountX));
		float posz = ((i / m_vtxCountX)) * -1.0f;

		float texU = (i % m_vtxCountX);
		float texV = (i / m_vtxCountZ);

		// メッシュを真ん中にする補正
		//m_pos = (D3DXVECTOR3(-(posx - 1) * m_meshSize.x * 0.5f, 0.0f, -posz * m_meshSize.z * 0.5f)) + m_pos;

		// 座標の補正
		pVtx[i].pos += D3DXVECTOR3(posx * m_meshSize.x - m_meshSize.x * m_vtxCountX * 0.5f, 0.0f, posz * m_meshSize.z + m_meshSize.z * m_vtxCountZ * 0.5f);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 頂点カラーの設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// 頂点座標をアンロック
	m_vtxBuff->Unlock();

	D3DXVECTOR3 pos = GetPos();
	m_collisionMesh = CCollisionMesh::Create(m_polygonCount, m_vtxBuff, m_idxBuff, m_mtxWorld, m_vtxCountX, m_vtxCountZ);
}

//--------------------------------------------------------------
// 法線とIndexの成立
//--------------------------------------------------------------
void CMesh::SetVtxMeshLight()
{
	VERTEX_3D* pVtx = nullptr;
	//インデックスバッファのロック
	WORD* pIdx;

	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_idxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int z = 0; z < m_zsiz; z++)
	{
		int linetop = z * (m_vtxCountX * 2 + 2);
		for (int x = 0; x < m_vtxCountX; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = (WORD)(x + (z * m_vtxCountX));
			pIdx[nIdxData] = (WORD)(pIdx[nIdxData + 1] + m_vtxCountX);
		}
		//縮退ポリゴン設定
		if (z < m_xsiz - 1)
		{
			pIdx[m_vtxCountX * 2 + 0 + linetop] = (WORD)(m_xsiz + m_vtxCountX*z);
			pIdx[m_vtxCountX * 2 + 1 + linetop] = (WORD)(m_vtxCountX * 2 + m_vtxCountX * z);
		}
	}

	//---------------------------------------
	//ここから法線
	//---------------------------------------

	//三角の頂点数
	const int nTri = 3;

	D3DXVECTOR3 posLineVec[nTri];//ベクトル

	for (int nCnt = 0; nCnt < m_polygonCount; nCnt++) // プリミティブの数だけまわす。
	{
		//ベクトルを求める
		posLineVec[0] = pVtx[pIdx[nCnt + 0]].pos;
		posLineVec[1] = pVtx[pIdx[nCnt + 1]].pos;
		posLineVec[2] = pVtx[pIdx[nCnt + 2]].pos;

		if ((pIdx[nCnt + 0] == pIdx[nCnt + 1]) ||
			(pIdx[nCnt + 0] == pIdx[nCnt + 2]) ||
			(pIdx[nCnt + 2] == pIdx[nCnt + 1]))
		{
			continue;
		}

		D3DXVECTOR3 V1 = posLineVec[1] - posLineVec[0];
		D3DXVECTOR3 V2 = posLineVec[2] - posLineVec[0];

		D3DXVECTOR3 Normal;

		if (nCnt % 2 == 0)
		{
			//AとBの法線を求めるやつ
			D3DXVec3Cross(&Normal, &V1, &V2);
		}
		else
		{
			//BとAの法線を求めるやつ
			D3DXVec3Cross(&Normal, &V2, &V1);
		}

		//Normalをノーマライズして、長さ 1にする。
		D3DXVec3Normalize(&Normal, &Normal);

		for (int i = 0; i < nTri; i++)
		{//法線計算
			pVtx[pIdx[nCnt + i]].nor += Normal;
		}
	}

	for (int nCnt = 0; nCnt < m_vtx; nCnt++)
	{
		//norをノーマライズして、長さ 1にする。
		D3DXVec3Normalize(&pVtx[nCnt].nor, &pVtx[nCnt].nor);
	}

	// 頂点座標をアンロック
	m_vtxBuff->Unlock();
	m_idxBuff->Unlock();
}

//--------------------------------------------------------------
// メッシュ枚数の決定
//--------------------------------------------------------------
void CMesh::SetSkyMesh()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	m_xsiz = START_HORIZONTAL;
	m_zsiz = START_VERTICAL;

	int xLine = m_xsiz + 1;
	int yLine = m_zsiz + 1;

	// 頂点数を計算
	m_vtx = xLine * yLine;

	// インデックス数を計算
	m_index = ((xLine * 2) * m_zsiz) + ((m_zsiz - 1) * 2);

	// ポリゴン数を計算
	m_polygonCount = (m_xsiz * m_zsiz * 2) + ((m_zsiz - 1) * 4);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_vtxBuff,
		NULL);

	VERTEX_3D *pVtx = NULL;		// 頂点情報へのポインタ

	// 頂点バッファをロック
	m_vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int y = 0; y < yLine; y++)
	{
		for (int x = 0; x < xLine; x++)
		{// 変数宣言
			int nCntVtx = x + (y *  xLine);
			float fRot = (m_sphereRange.x / START_HORIZONTAL) * x;					// Y軸の角度の設定
			float fHalfRot = (m_sphereRange.y / START_VERTICAL) * y;				// 半球のZ軸の角度の半分

			// 高さと半径の設定
			D3DXVECTOR2 radius = D3DXVECTOR2(sinf(fHalfRot) * m_fRadius, cosf(fHalfRot) * m_fRadius);

			// 頂点座標の設定
			pVtx[nCntVtx].pos.x = sinf(fRot) * radius.y;
			pVtx[nCntVtx].pos.z = cosf(fRot) * radius.y;
			pVtx[nCntVtx].pos.y = radius.x;

			// ワールド座標にキャスト
			WorldCastVtx(pVtx[nCntVtx].pos, GetPos(), GetRot());

			// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
			pVtx[nCntVtx].nor.x = pVtx[nCntVtx].pos.x;
			pVtx[nCntVtx].nor.z = pVtx[nCntVtx].pos.z;
			pVtx[nCntVtx].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[nCntVtx].nor, &pVtx[nCntVtx].nor);

			// 頂点カラーの設定
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			float fUTex = (1.0f / m_xsiz) * x;
			float fVTex = (1.0f / m_zsiz) * y;

			// テクスチャ座標の設定
			pVtx[x + (y * xLine)].tex = D3DXVECTOR2(fUTex, fVTex);
		}
	}

	// 頂点バッファのアンロック
	m_vtxBuff->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(
		sizeof(VERTEX_3D) * m_index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_idxBuff,
		NULL);

	WORD *pIdx = NULL;		// インデックス情報へのポインタ

	// インデックスバッファをロック
	m_idxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	for (int x = 0, y = 0; y < m_zsiz; x++, y++)
	{
		for (; x < (xLine * (y + 1)) + y; x++)
		{
			pIdx[x * 2] = (WORD)(x - y + xLine);
			pIdx[(x * 2) + 1] = (WORD)(x - y);
			x = x;
		}

		if (y < m_zsiz - 1)
		{// これで終わりじゃないなら
			pIdx[x * 2] = (WORD)(x - (y + 1));
			pIdx[(x * 2) + 1] = (WORD)((x * 2) - (y * (m_xsiz + 3)));
			x = x;
		}
	}

	// インデックスバッファをアンロックする
	m_idxBuff->Unlock();
}

//--------------------------------------------------------------
// 1つのメッシュのサイズ設定
//--------------------------------------------------------------
void CMesh::SetOneMeshSize(D3DXVECTOR3 IsSize)
{
	m_meshSize = IsSize;
}
