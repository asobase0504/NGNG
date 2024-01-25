//**************************************************************
//
// モードクラスのヘッダー
// Author:Yuda Kaito
//
//**************************************************************
#ifndef _MODE_H_		//このマクロが定義されてなかったら
#define _MODE_H_		//2重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "task.h"

class CCamera;
class CLight;

class CMap;
class CMapFade;

//==============================================================
// ゲームクラス
//==============================================================
class CMode : public CTask
{
public:
	CMode() : CTask(CTaskGroup::LEVEL_SYSTEM, CTaskGroup::EPushMethod::PUSH_CURRENT), m_map(nullptr){ SetRole(ROLE_MODE); }
	~CMode() override {}

	virtual HRESULT Init() override = 0;
	virtual void Update() override = 0;
	virtual void Draw() override {};

	CMap* GetMap() { return m_map; }
	void CreateMap(std::string inPath);
	void ChangeMap();

	CMapFade* GetMapFade() { return m_mapFade; }

	CCamera* GetCamera() { return m_camera; }

protected:
	CCamera* m_camera;
	CLight* m_light;
private:
	CMap* m_map;
	CMapFade* m_mapFade;
};
#endif