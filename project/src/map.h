//**************************************************************
//
// マップのヘッダー
// Author:Tomidokoro Tomoki
//
//**************************************************************
#ifndef _MAP_H_		//このマクロが定義されてなかったら
#define _MAP_H_		//2重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "task.h"
#include "character.h"

//==============================================================
// マクロ宣言
//==============================================================

//==============================================================
// 前方宣言
//==============================================================
class CMesh;
class CMapModel;
class CSelectEntity;

//==============================================================
// マップクラス
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

	static CMap* GetMap(std::string inPath = "")
	{
		if (inPath != "")
		{
			if (m_map != nullptr)
			{
				m_map->Uninit();
			}

			m_map = new CMap;
			m_map->Load(inPath);
			m_map->Init();
		}

		return m_map;
	}

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
private:
	static CMap* m_map;

	std::string m_nextMapPath;	//次のマップ

	int m_SpawnCnt;	// エネミーの出現タイム

	// 存在するObject
	std::vector<CMapModel*> m_model;
	std::vector<CMesh*> m_mesh;
	std::list<CCharacter*> m_characterList;
	std::list<CSelectEntity*> m_selectEntity;
};
#endif