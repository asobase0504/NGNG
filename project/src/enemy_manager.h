//**************************************************************
//
// 敵管理
// Author : 梶田大夢
//
//**************************************************************
#ifndef _ENEMY_MANAGER_H_			// このマクロ定義がされてなかったら
#define _ENEMY_MANAGER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "task.h"
#include "enemy.h"
#include "enemy_data_base.h"

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;
class CEnemy;
class CCollisionBox;

//==============================================================
// 敵管理クラス
//==============================================================
class CEnemyManager : public CTask
{
public:	// シングルトン用のインスタンス
	static CEnemyManager* GetInstance();
private:
	CEnemyManager();
	static CEnemyManager* m_enemyManager;

public:
	// コンストラクタとデストラクタ
	~CEnemyManager();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;

	// 静的メンバ関数
	CEnemy* CreateEnemy(D3DXVECTOR3 pos, CEnemyDataBase::EEnemyType type, int level);			// エネミーの生成
	// ランダムスポーン
	CEnemy* RandomSpawn();

private:		// メンバ変数
};
#endif