//**************************************************************
//
// 運の祭壇
// Author : 梶田大夢
//
//**************************************************************

// include
#include "statue_luck.h"
#include "character.h"
#include "collision_cylinder.h"
#include "item_manager.h"
#include "input.h"
#include "utility.h"
#include "procedure3D.h"

namespace
{
std::array<float, CItemDataBase::RARITY_MAX> rate = { 0.05f,0.1f,0.2f,0.65f };
};

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CStatueLuck::CStatueLuck()
{

}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CStatueLuck::~CStatueLuck()
{

}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CStatueLuck::Init()
{
	// 初期化処理
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	m_nUseMoney = 10;
	m_costUI = CProcedure3D::Create(pos, D3DXVECTOR3(4.0f, 4.0f, 0.0f), m_nUseMoney);
	SetEndChildren(m_costUI);
	m_costUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	CStatue::Init(pos,rot);
	LoadModel("STATUE_LUCK");

	m_nItemCount = 0;
	m_uiText = "運を試す [$" + std::to_string(m_nUseMoney) + "]";

	return S_OK;
}

//--------------------------------------------------------------
// 選択
//--------------------------------------------------------------
bool CStatueLuck::Select(CCharacter * selectCharacter)
{
	CStatus<int>* money = selectCharacter->GetMoney();

	if (money->GetCurrent() < m_nUseMoney)
	{
		return false;
	}

	// プレイヤーお金を調整して設定
	money->AddCurrent(-m_nUseMoney);

	D3DXVECTOR3 pos(m_pos.x, m_pos.y + 30.0f, m_pos.z);
	int answer = CItemManager::GetInstance()->CreateRandomItemRarityRate(pos, GetMtxRot(), rate);

	switch (answer)
	{
	case 0:	// レア
	case 1:	// アンコモン
	case 2:	// コモン
		m_nItemCount++;
		break;
	case 3:	// ハズレ
		break;
	default:
		assert(false);
		break;
	}

	// 次回ガチャする時用に必要お金数を増やして設定しておく
	int randomNumber = rand() % 10;
	m_nUseMoney += randomNumber;

	m_costUI->SetNumber(m_nUseMoney);

	m_uiText = "運を試す [$" + std::to_string(m_nUseMoney) + "]";

	if (m_nItemCount >= 2)
	{
		m_collisionCylinder->Uninit();
		m_collisionCylinder = nullptr;
		m_costUI->Uninit();
		m_costUI = nullptr;
	}

	return true;
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CStatueLuck* CStatueLuck::Create(D3DXVECTOR3 pos)
{
	CStatueLuck* pStatuechest;
	pStatuechest = new CStatueLuck;
	pStatuechest->SetPos(pos);
	pStatuechest->Init();

	return pStatuechest;
}

//--------------------------------------------------------------
// 位置
//--------------------------------------------------------------
void CStatueLuck::SetPos(const D3DXVECTOR3 & inPos)
{
	if (m_costUI != nullptr)
	{
		m_costUI->SetPos(inPos);

		D3DXVECTOR3 vector = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
		D3DXMATRIX mtxRot;
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXVec3TransformCoord(&vector, &vector, &mtxRot);
		m_costUI->AddPos(vector);
		m_costUI->AddPos(D3DXVECTOR3(0.0f,10.0f,0.0f));
	}
	CStatue::SetPos(inPos);
}
