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
#include "map_model.h"
#include "object_mesh.h"
#include "file.h"
#include "statue.h"
#include "utility.h"

#include "statue_manager.h"
#include "enemy_manager.h"

//==============================================================
// 静的メンバ変数宣言
//==============================================================
CMap* CMap::m_map = nullptr;

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
CMap::CMap() :
	CTask(CTaskGroup::EPriority::LEVEL_SYSTEM)
{
	m_SpawnCnt = 0;
	m_characterList.clear();
	m_model.clear();
	m_mesh.clear();
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
HRESULT CMap::Init()
{
	MapChangeRelese();
	CStatueManager* manager = CStatueManager::GetInstance();
	m_statue.push_back(manager->RandomCreate());
	m_statue.push_back(manager->RandomCreate());
	m_statue.push_back(manager->RandomCreate());
	m_statue.push_back(manager->RandomCreate());
	m_statue.push_back(manager->CreateStatue(CStatueManager::BLOOD));
	m_statue.push_back(manager->CreateStatue(CStatueManager::LUCK));
	m_statue.push_back(manager->CreateStatue(CStatueManager::TELEPORTER));
	m_statue.push_back(manager->CreateStatue(CStatueManager::CHEST));
	m_statue.push_back(manager->CreateStatue(CStatueManager::COMBAT));

	for (int i = 0; i < 10; i++)
	{
		m_statue.push_back(manager->CreateStatue(CStatueManager::CHEST));
	}

	CMesh* sky = CMesh::Create();
	sky->SetSkyMesh();
	sky->SetTexture("SKY");

	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CMap::Uninit()
{
	m_statue.clear();
	m_mesh.clear();
	m_model.clear();
	m_characterList.clear();

	CTask::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CMap::Update()
{
	m_SpawnCnt++;

	// 一定時間ごとにランダムな敵をスポーンさせる。
	if (m_SpawnCnt >= 600)
	{
		m_SpawnCnt = 0;
		CEnemyManager::GetInstance()->RandomSpawn();
	}
}

//--------------------------------------------------------------
// 生成
//--------------------------------------------------------------
CMap* CMap::Create(std::string path)
{
	//キャラクター生成
	m_map = new CMap;

	if (m_map != nullptr)
	{//NULLチェック
	 //メンバ変数に代入
	 //初期化
		m_map->Load(path);
		m_map->Init();
	}

	return m_map;
}

//--------------------------------------------------------------
// 読込み
//--------------------------------------------------------------
void CMap::Load(std::string path)
{
	nlohmann::json map = LoadJson(path);

	int size = map["MODEL"].size();
	for (int i = 0; i < size; i++)
	{
		nlohmann::json model = map["MODEL"][i];
		D3DXVECTOR3 pos(model["POS"][0], model["POS"][1], model["POS"][2]);
		D3DXVECTOR3 rot(model["ROT"][0], model["ROT"][1], model["ROT"][2]);
		CMapModel* object = CMapModel::Create(pos, rot, D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		object->LoadModel(model["TAG"]);
		m_model.push_back(object);
	}

	size = map["MESH"].size();
	for (int i = 0; i < size; i++)
	{
		nlohmann::json mesh = map["MESH"][i];
		CMesh* object = CMesh::Create();
		object->SetY(mesh["VTX_HEIGHT"]);
		D3DXVECTOR3 pos(mesh["POS"][0], mesh["POS"][1], mesh["POS"][2]);
		object->SetPos(pos);
		object->SetOneMeshSize(D3DXVECTOR3(100.0f,100.0f,100.0f));

		m_mesh.push_back(object);
	}

	m_nextMapPath = map["NEXT_MAP"];
}

//--------------------------------------------------------------
// 違う関係のものに関数を行う
//--------------------------------------------------------------
void CMap::DoDifferentRelation(CCharacter::ERelation inRelation, std::function<void(CCharacter*)> inFunc)
{
	std::list<CCharacter*> charaList = GetCharacterList();

	for (CCharacter* chara : charaList)
	{// 攻撃範囲に敵がいるか判定する

		if (chara->IsDeleted())
		{
			continue;
		}

		if (chara->GetRelation() == inRelation)
		{
			continue;
		}

		inFunc(chara);
	}
}

