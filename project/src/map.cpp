//**************************************************************
// 
// �}�b�v�̍쐬
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
// �ÓI�����o�ϐ��錾
//==============================================================
CMap* CMap::m_map = nullptr;

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CMap::CMap() :
	CTask(CTaskGroup::EPriority::LEVEL_SYSTEM)
{
	m_SpawnCnt = 0;
	m_model.clear();
	m_mesh.clear();
}

//--------------------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------------------
CMap::~CMap()
{

}

//--------------------------------------------------------------
// ������
//--------------------------------------------------------------
HRESULT CMap::Init()
{
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

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CMap::Uninit()
{
	for (CStatue* statue : m_statue)
	{
		statue->Uninit();
		statue = nullptr;
	}
	for (CMesh* mesh : m_mesh)
	{
		mesh->Uninit();
		mesh = nullptr;
	}
	for (CMapModel* model : m_model)
	{
		model->Uninit();
		model = nullptr;
	}
	for (CEnemy* enemy : m_enemy)
	{
		enemy->Uninit();
		enemy = nullptr;
	}
	m_statue.clear();
	m_mesh.clear();
	m_model.clear();
	m_enemy.clear();

	CTask::Uninit();
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CMap::Update()
{
	m_SpawnCnt++;

	// ��莞�Ԃ��ƂɃ����_���ȓG���X�|�[��������B
	if (m_SpawnCnt >= 600)
	{
		m_SpawnCnt = 0;
		InEnemyList(CEnemyManager::GetInstance()->RandomSpawn());
	}
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CMap* CMap::Create(std::string path)
{
	//�L�����N�^�[����
	m_map = new CMap;

	if (m_map != nullptr)
	{//NULL�`�F�b�N
	 //�����o�ϐ��ɑ��
	 //������
		m_map->Load(path);
		m_map->Init();
	}

	return m_map;
}

//--------------------------------------------------------------
// �Ǎ���
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

void CMap::InEnemyList(D3DXVECTOR3, int)
{
}

void CMap::InEnemyList(int)
{
}
