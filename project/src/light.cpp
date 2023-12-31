//**************************************************************
// 
// ライトの作成
// Author : Hamada Ryuuga
// 
//**************************************************************

//==============================================================
// include
//==============================================================
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "input.h"

//==============================================================
// 定数定義
//==============================================================
const int CLight::LIGTH_MAX = 5;

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CLight::CLight(CTaskGroup::EPriority inPriority) :
	CTask(inPriority, CTaskGroup::EPushMethod::PUSH_TOP)
{
	SetRole(ROLE_LIGHT);
	m_light.clear();
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CLight::~CLight()
{

}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CLight::Init(void)
{
	m_light.resize(LIGTH_MAX);

	// ライトの設定
	D3DXCOLOR color(1.0f, 1.0f, 1.0f, 1.0f);

	Set(D3DLIGHT_DIRECTIONAL, color, D3DXVECTOR3(0.32f, -0.49f, 0.93f), 0);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CLight::Uninit(void)
{
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CLight::Update(void)
{
}

//--------------------------------------------------------------
// 設定
//--------------------------------------------------------------
void CLight::Set(D3DLIGHTTYPE type,D3DXCOLOR col, D3DXVECTOR3 vec, int nNum)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;		// ライトの方向ベクトル

	m_light[nNum].Type = type;	// ライトの種類を設定 ( 平行光源 )
	m_light[nNum].Diffuse = col;	// ライトの拡散光を設定 ( ライトの色 )

	vecDir = vec;	// ライトの方向を設定

	// 正規化する ( 大きさ 1 のベクトルにする )
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[nNum].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(nNum, &m_light[nNum]);

	// ライトを有効にする
	pDevice->LightEnable(nNum, true);
}
