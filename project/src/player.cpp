//==============================================================
//
// プレイヤー
// Author : 髙野馨將
//
//==============================================================

// include
#include "player.h"
#include "application.h"
#include "objectX.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer(int nPriority)
{

}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	CObjectX* testX = CObjectX::Create(D3DXVECTOR3(15.0f, -15.0f, 0.0f));
	testX->LoadModel("BOX");
	testX->SetMoveRot(D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	testX->SetMaterialDiffuse(0, D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));
	testX->CalculationVtx();

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CPlayer::Uninit(void)
{

	CObject::Release();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CPlayer::Update(void)
{


	CObject::Update();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CPlayer::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用

	//現在のマテリアルを維持
	pDevice->GetMaterial(&matDef);

	//パーツのワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//パーツのモデルの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//パーツのモデルの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int i = 0; i < (int)m_apModel.size(); i++)
	{
		if (m_apModel[i]->GetParent() == nullptr)
		{
			m_apModel[i]->SetMtxWorld(m_mtxWorld);
		}
	}
}

//-----------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer;
	pPlayer = new CPlayer(CObject::PLAYER);
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->Init();

	return pPlayer;
}