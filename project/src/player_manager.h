//**************************************************************
//
// プレイヤー管理
// Author : 梶田大夢
//
//**************************************************************
#ifndef _PLAYER_MANAGER_H_			// このマクロ定義がされてなかったら
#define _PLAYER_MANAGER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "task.h"
#include "player.h"

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;
class CPlayer;
class CCollisionCylinder;

//==============================================================
// プレイヤー管理クラス
//==============================================================
class CPlayerManager : public CTask
{
public:	// シングルトン用のインスタンス
	static CPlayerManager* GetInstance();
private:
	CPlayerManager();
	static CPlayerManager* m_playerManager;

public:
	// コンストラクタとデストラクタ
	~CPlayerManager();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	CPlayer* CreatePlayer(D3DXVECTOR3 pos);			// プレイヤーの生成

	// ゲッター
	CPlayer* GetPlayer() { return m_pPlayer; }
	const D3DXVECTOR3& GetPlayerPos() { return m_pPlayer->GetPos(); }

private:		// メンバ変数
	CPlayer* m_pPlayer;
};
#endif
