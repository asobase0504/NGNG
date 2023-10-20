//**************************************************************
//
// キャラクター
// Author : 梶田大夢
//
//**************************************************************

// include
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "application.h"
#include "objectX.h"
#include "PlayerController.h"
#include "collision_sphere.h"

#include "status.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CCharacter::CCharacter(int nPriority) : m_haveItem{}
{
	m_apModel.clear();
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CCharacter::~CCharacter()
{

}

//--------------------------------------------------------------
// 初期化処理
//--------------------------------------------------------------
HRESULT CCharacter::Init()
{
	m_apModel.resize(1);
	m_apModel[0] = CObjectX::Create(m_pos);
	m_apModel[0]->LoadModel("BOX");

	m_collision.push_back(CCollisionSphere::Create(m_pos,100.0f));

	m_hp.Init(100);
	m_hp.SetCurrent(100);
	m_addHp.Init(100);
	m_addHp.SetCurrent(100);
	m_addHpSubTime.Init(100);
	m_addHpSubTime.SetCurrent(100);
	m_barrier.Init(100);
	m_barrier.SetCurrent(100);
	m_barrierRePopTime.Init(100);
	m_barrierRePopTime.SetCurrent(100);
	m_attack.Init(100);
	m_attack.SetCurrent(100);
	m_defense.Init(100);
	m_defense.SetCurrent(100);
	m_criticalRate.Init(100);
	m_criticalRate.SetCurrent(100);
	m_criticalDamage.Init(100);
	m_criticalDamage.SetCurrent(100);
	m_movePower.Init(2.0f);
	m_movePower.SetCurrent(2.0f);
	m_jumpPower.Init(100);
	m_jumpPower.SetCurrent(3.0f);
	m_jumpCount.Init(1);
	m_jumpCount.SetCurrent(0);
	return S_OK;
}

//--------------------------------------------------------------
// 終了処理
//--------------------------------------------------------------
void CCharacter::Uninit(void)
{
	// 破棄処理
	CObject::Release();
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void CCharacter::Update(void)
{
	// 座標の更新処理
	UpdatePos();

	// 更新処理
	CObject::Update();
}

//--------------------------------------------------------------
// 描画処理
//--------------------------------------------------------------
void CCharacter::Draw(void)
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

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CCharacter* CCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//キャラクター生成
	CCharacter* pCharacter = new CCharacter;

	if (pCharacter != nullptr)
	{//NULLチェック
	 //メンバ変数に代入
		//初期化
		pCharacter->Init();
	}

	return pCharacter;
}

void CCharacter::Attack()
{
}

void CCharacter::Move()
{
}

//--------------------------------------------------------------
// 座標の更新
//--------------------------------------------------------------
void CCharacter::UpdatePos()
{
	// 座標の取得
	D3DXVECTOR3 pos = GetPos();

	SetPosOld(pos);			// 前回の位置の保存
	pos += GetMove();		// 位置の更新

	// 座標の設定
	SetPos(pos);
}