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
#include "objectX.h"
#include "object_mesh.h"
#include "file.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
CMap::CMap()
{
	m_apModels.clear();
	m_apMesh.clear();
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

}

//--------------------------------------------------------------
// ����
//--------------------------------------------------------------
CMap* CMap::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�L�����N�^�[����
	CMap* pMap = new CMap;

	if (pMap != nullptr)
	{//NULL�`�F�b�N
	 //�����o�ϐ��ɑ��
	 //������
		pMap->Init();
	}

	return pMap;
}

void CMap::Load(std::string path)
{
	nlohmann::json map = LoadJson(path);

	int size = map["MODEL"].size();
	for (int i = 0; i < size; i++)
	{
		nlohmann::json model = map["MODEL"][i];
		D3DXVECTOR3 pos(model["POS"][0], model["POS"][1], model["POS"][2]);
		CObjectX* object = CObjectX::Create(pos);
		D3DXVECTOR3 rot(model["ROT"][0], model["ROT"][1], model["ROT"][2]);
		object->SetRot(rot);
		object->LoadModel(model["TAG"]);
		m_apModels.push_back(object);
	}

	size = map["MESH"].size();
	for (int i = 0; i < size; i++)
	{
		nlohmann::json mesh = map["MESH"][i];
		CMesh* object = CMesh::Create();
		D3DXVECTOR3 pos(mesh["POS"][0], mesh["POS"][1], mesh["POS"][2]);
		object->SetPos(pos);
		object->SetOneMeshSize(D3DXVECTOR3(100.0f,100.0f,100.0f));

		m_apMesh.push_back(object);
	}
}
