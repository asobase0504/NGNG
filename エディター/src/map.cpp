//**************************************************************
// 
// マップの作成
// Author : Tomidokoro Tomoki
// 
//**************************************************************

//==============================================================
// include
//==============================================================
#include "map.h"

#include "application.h"
#include "renderer.h"
#include "input.h"
#include "file.h"
#include "utility.h"

#include "object_mesh.h"
#include "map_model.h"
#include "statue.h"
#include "statue_manager.h"
#include "enemy_manager.h"
#include "gold_nugget.h"

//debug
#include "item_manager.h"
#include "item_data_base.h"

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

	//CMesh* sky = CMesh::Create();
	//sky->SetSkyMesh();
	//sky->SetIsCulling(true);
	//sky->SetTexture("SKY");

	CObject2d* sky = CObject2d::Create();
	sky->SetSize(CApplication::CENTER_POS);
	sky->SetPos(CApplication::CENTER_POS);
	sky->SetColor(D3DXCOLOR(0.8f, 0.8f, 1.0f, 1.0f));

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	for (int i = 0; i < CItemDataBase::EItemType::ITEM_MAX; i++)
	{
		CItemManager::GetInstance()->CreateItem(D3DXVECTOR3(-2001 + i * 50.0f, 100.0f, 1000.0f), mtx, (CItemDataBase::EItemType)i);
	}
	//Save("data/test.json");
	
	return S_OK;
}

//--------------------------------------------------------------
// 終了
//--------------------------------------------------------------
void CMap::Uninit()
{
	m_mesh.clear();
	m_model.clear();
	m_characterList.clear();
	m_selectEntity.clear();

	CTask::Uninit();
}

//--------------------------------------------------------------
// 更新
//--------------------------------------------------------------
void CMap::Update()
{
	//m_SpawnCnt++;

	// 一定時間ごとにランダムな敵をスポーンさせる。
	if (m_SpawnCnt >= 600)
	{
		m_SpawnCnt = 0;
		SetEndChildren(CEnemyManager::GetInstance()->RandomSpawn());
	}
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
		SetEndChildren(object);
	}

	size = map["MESH"].size();
	nlohmann::json mesh = map["MESH"];
	CMesh* object = CMesh::Create();
	object->SetY(mesh["VTX_HEIGHT"]);
	D3DXVECTOR3 pos(mesh["POS"][0], mesh["POS"][1], mesh["POS"][2]);
	object->SetPos(pos);
	object->SetOneMeshSize(D3DXVECTOR3(100.0f,100.0f,100.0f));
	object->SetTexture("MESH_BG");
	m_mesh.push_back(object);
	SetEndChildren(object);

	int enemySize = map["ENEMY"][0].size();
	
	for (int i = 0; i < enemySize; i++)
	{
		bool isPop = map["ENEMY"][0][i];
		m_EnemyPopList.push_back(isPop);
	}
	
	//m_nextMapPath = map["NEXT_MAP"];
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

//--------------------------------------------------------------
// Save関数群
//--------------------------------------------------------------
void CMap::Save(std::string data)
{
	nlohmann::json JMap;//リストの生成
	int size = m_model.size();
	for (int i = 0; i < size; i++)
	{
		CMapModel* List = GetMapModel(i);
		JMap["MODEL"][i]["POS"] = { List->GetPos().x,List->GetPos().y ,List->GetPos().z };
		JMap["MODEL"][i]["ROT"] = { List->GetRot().x,List->GetRot().y ,List->GetRot().z };
		JMap["MODEL"][i]["TAG"] = List->GetKey();
		
	}
	for (int Mesh = 0; Mesh < GetNumMesh(); Mesh++)
	{
		CMesh* List = GetMapMesh(Mesh);
		JMap["MESH"]["POS"] = { List->GetPos().x,List->GetPos().y ,List->GetPos().z };
		for (int i = 0; i < List->GetY().size(); i++)
		{
			JMap["MESH"]["VTX_HEIGHT"][i] = List->GetY()[i];
		}
	}
	for (int i = 0; i < m_EnemyPopList.size(); i++)
	{
		JMap["ENEMY"] = { m_EnemyPopList };
	}
	

	auto jobj = JMap.dump();
	std::ofstream writing_file;
	const std::string pathToJSON = data.c_str();
	writing_file.open(pathToJSON, std::ios::out);
	writing_file << jobj << std::endl;
	writing_file.close();
}

