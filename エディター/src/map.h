//**************************************************************
//
// �}�b�v�̃w�b�_�[
// Author:Tomidokoro Tomoki
//
//**************************************************************
#ifndef _MAP_H_		//���̃}�N������`����ĂȂ�������
#define _MAP_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//==============================================================
// include
//==============================================================
#include "task.h"
#include "character.h"

//==============================================================
// �}�N���錾
//==============================================================

//==============================================================
// �O���錾
//==============================================================
class CMesh;
class CMapModel;
class CSelectEntity;

//==============================================================
// �}�b�v�N���X
//==============================================================
class CMap : public CTask
{
private:
public:
	CMap();
	~CMap();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void Load(std::string path);
	void Save(std::string data);
	static CMap* GetMap(std::string inPath = "")
	{
		if (inPath != "")
		{
			if (m_map != nullptr)
			{
				m_map = nullptr;
			}

			m_map = new CMap;
			m_map->Load(inPath);
			m_map->Init();
		}

		return m_map;
	}

	void SetMapModel(CMapModel* model) { m_model.push_back(model); }
	CMapModel* GetMapModel(int inNum) { return m_model[inNum]; }
	int GetNumModel() { return m_model.size(); }

	CMesh* GetMapMesh(int inNum) { return m_mesh[inNum]; }
	int GetNumMesh() { return m_mesh.size(); }


	void InSelectEntityList(CSelectEntity* inselectEntity) { m_selectEntity.push_back(inselectEntity); }
	std::list<CSelectEntity*> GetSelectEntityList() { return m_selectEntity; }
	void RemoveSelectEntityList(CSelectEntity* entity) { m_selectEntity.remove(entity); }

	void InCharacterList(CCharacter* inCharacter) { m_characterList.push_back(inCharacter); }
	const std::list<CCharacter*> GetCharacterList() const { return m_characterList; }
	void  SetCharacterList(std::list<CCharacter*> inList) { m_characterList = inList; }
	void DoDifferentRelation(CCharacter::ERelation,std::function<void(CCharacter*)>);

	std::string GetNextMapPath() { return m_nextMapPath; }

	bool GetEnemyPopList(int index) { return m_EnemyPopList[index]; }
	void EnemyPopList(std::vector<bool> list)
	{
		m_EnemyPopList = list;
	}

private:
	static CMap* m_map;

	std::string m_nextMapPath;	//���̃}�b�v

	int m_SpawnCnt;	// �G�l�~�[�̏o���^�C��

	// ���݂���Object
	std::vector<CMapModel*> m_model;
	std::vector<CMesh*> m_mesh;
	std::list<CCharacter*> m_characterList;
	std::list<CSelectEntity*> m_selectEntity;

	std::vector<bool> m_EnemyPopList;




//	void EnemyPopList();

	
};
#endif