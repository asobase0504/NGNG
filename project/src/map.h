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

//==============================================================
// マクロ宣言
//==============================================================

//==============================================================
// 前方宣言
//==============================================================
class CMesh;
class CMapModel;

//==============================================================
// マップクラス
//==============================================================
class CMap : public CTask
{
public:
	CMap();
	~CMap();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	// 静的メンバ関数
	static CMap *Create();			// マップの生成

	void Load(std::string path);

	static CMap* GetMap() { return m_map; }

	CMapModel* GetMapModel(int inNum) { return m_mapModel[inNum]; }
	int GetNumModel() { return m_mapModel.size(); }

	CMesh* GetMapMesh(int inNum) { return m_mesh[inNum]; }
	int GetNumMesh() { return m_mesh.size(); }

private:
	static CMap* m_map;
	std::vector<CMapModel*> m_mapModel;
	std::vector<CMesh*> m_mesh;
};
#endif