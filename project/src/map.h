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
class CStatue;
class CEnemy;

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

	// 静的メンバ関数
	static CMap *Create(std::string);			// マップの生成

	void Load(std::string path);

	static CMap* GetMap() { return m_map; }

	CMapModel* GetMapModel(int inNum) { return m_model[inNum]; }
	int GetNumModel() { return m_model.size(); }

	CMesh* GetMapMesh(int inNum) { return m_mesh[inNum]; }
	int GetNumMesh() { return m_mesh.size(); }

	const std::list<CStatue*> GetStatueList() const { return m_statue; }

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
	std::list<CStatue*> m_statue;
};
#endif