//**************************************************************
// 
// マップの作成
// Author : Tomidokoro Tomoki
// 
//**************************************************************

//==============================================================
// include
//==============================================================
#include "application.h"
#include "renderer.h"
#include "map.h"
#include "input.h"
#include "objectX.h"
#include "object_mesh.h"
#include "file.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CMap::CMap()
{
	m_apModels.clear();
	m_apMesh.clear();
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
CMap::~CMap()
{

}

//--------------------------------------------------------------
// 初期化
//--------------------------------------------------------------
HRESULT CMap::Init(void)
{
	m_apModels.resize(1);
	m_apMesh.resize(1);
	m_apModels[0] = CObjectX::Create(m_pos);
	m_apModels[0]->LoadModel("BOX");

	m_apMesh[0] = CMesh::Create();
	m_apMesh[0]->SetMesh(50);

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CMap::Uninit(void)
{
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CMap::Update(void)
{

}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CMap* CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//キャラクター生成
	CMap* pMap = new CMap;

	if (pMap != nullptr)
	{//NULLチェック
	 //メンバ変数に代入
	 //初期化
		pMap->Init();
	}

	return pMap;
}