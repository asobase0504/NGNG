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
#include "road.h"

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
	CObject::Init();

	m_apModel.resize(1);
	m_apModel[0] = CObjectX::Create(m_pos);
	m_apModel[0]->LoadModel("BOX");
	m_road = CRoad::Create(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	m_hp.Init(100);
	m_hp.SetCurrent(50);
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
	m_attackSpeed.Init(1.0f);
	m_attackSpeed.SetCurrent(1.0f);
	m_defense.Init(100);
	m_defense.SetCurrent(100);
	m_criticalRate.Init(0.0f);
	m_criticalRate.SetCurrent(0.0f);
	m_criticalDamage.Init(2.0f);
	m_criticalDamage.SetCurrent(2.0f);
	m_movePower.Init(2.0f);
	m_movePower.SetCurrent(1.0f);
	m_jumpPower.Init(3.0f);
	m_jumpPower.SetCurrent(3.0f);
	m_jumpCount.Init(1);
	m_jumpCount.SetCurrent(0);
	m_money.Init(100);
	m_money.SetCurrent(100);
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
	// 更新処理
	CObject::Update();

	if (m_hp.GetCurrent() <= 0)
	{
		// 死亡処理
	}
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

//--------------------------------------------------------------
// 位置の設定
//--------------------------------------------------------------
void CCharacter::SetPos(const D3DXVECTOR3 & inPos)
{
	std::vector<CObjectX*> objectX = GetModel();
	if (objectX.size() > 0)
	{
		GetModel()[0]->SetPos(inPos);
	}

	CObject::SetPos(inPos);
}

void CCharacter::SetRot(const D3DXVECTOR3 & inRot)
{
	if (m_apModel.size() > 0)
	{
		GetModel()[0]->SetRot(inRot);
	}

	CObject::SetRot(inRot);
}

//--------------------------------------------------------------
// ダメージ
//--------------------------------------------------------------
void CCharacter::Damage(const int inDamage)
{
	int dmg = inDamage;

	// ダメージ計算
	CStatus<int>* hp = GetHp();

	// 防御力算出
	int def = m_defense.CalStatus();

	dmg -= def;

	if (dmg <= 0)
	{
		dmg = 0;
	}

	hp->AddCurrent(-dmg);
}

//--------------------------------------------------------------
// 攻撃
//--------------------------------------------------------------
void CCharacter::Attack(CCharacter* pEnemy, float SkillMul)
{
	// プレイヤーのダメージを計算
	int Damage = CalDamage(SkillMul);
	// エネミーにダメージを与える。
	pEnemy->Damage(Damage);
}

void CCharacter::Move()
{
}

//--------------------------------------------------------------
// ダメージ計算関数
//--------------------------------------------------------------
int CCharacter::CalDamage(float SkillAtkMul)
{// 攻撃力 * 

	int CalDamage = m_attack.CalStatus() * SkillAtkMul;

	return CalDamage;
}