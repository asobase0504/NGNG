//**************************************************************
//
// ゲーム画面のヘッダー
// Author:Hamada Ryuuga
//
//**************************************************************
#ifndef _GAME_H_		//このマクロが定義されてなかったら
#define _GAME_H_		//2重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "mode.h"

//==============================================================
// マクロ宣言
//==============================================================

//==============================================================
// 前方宣言
//==============================================================
class CPlayerManager;
class CEnemyManager;
class CCameraGame;
class CLight;
class CMap;
class CPlayerController;
class CMapFade;
class ConnectManager;
class CDifficult;

//==============================================================
// ゲームクラス
//==============================================================
class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	CCameraGame* GetCamera() { return m_camera; }
	CPlayerController* GetController() { return m_controller; }
	CDifficult* GetDifficult() { return m_difficult; }

	void SetChangeMap();
	void ChangeMap(std::string);
private:
	CPlayerManager* m_player;	// プレイヤー
	CPlayerController* m_controller;	// コントローラー
	CEnemyManager* m_enemy;		// 敵
	CCameraGame* m_camera;
	CMap* m_map;
	CLight* m_light;
	CMapFade* m_mapFade;
	ConnectManager*m_tcp;
	CDifficult* m_difficult;
};
#endif