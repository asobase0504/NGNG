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

#include "statue_manager.h"

//==============================================================
// �ÓI�����o�ϐ��錾
//==============================================================
CMap* CMap::m_map = nullptr;

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CMap::CMap()
{
	m_mapModel.clear();
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
HRESULT CMap::Init(void)
{
	Load("data/FILE/map/map01.json");

	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f), CStatueManager::BLOOD);
	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f), CStatueManager::LUCK);
	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f), CStatueManager::CHEST);
	CStatueManager::GetInstance()->CreateStatue(D3DXVECTOR3(0.0f, 10.0f, 0.0f), CStatueManager::COMBAT);

	return S_OK;
}

//--------------------------------------------------------------
// �I��
//--------------------------------------------------------------
void CMap::Uninit(void)
{
}

//--------------------------------------------------------------
// �X�V
//--------------------------------------------------------------
void CMap::Update(void)
{
	m_map;
}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CMap* CMap::Create()
{
	//�L�����N�^�[����
	m_map = new CMap;

	if (m_map != nullptr)
	{//NULL�`�F�b�N
	 //�����o�ϐ��ɑ��
	 //������
		m_map->Init();
	}

	return m_map;
}

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
		m_mapModel.push_back(object);
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
}
