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

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;
class CEnemy;

//==============================================================
// プレイヤークラス
//==============================================================
class CEnemyManager : public CTask
{
public:	// シングルトン用のインスタンス
	static CEnemyManager* GetInstance();
private:
	CEnemyManager();
	static CEnemyManager* m_enemyManager;

public:
	enum EType
	{
		NONE = 0,
		SKELETON,
		MAX
	};

	// コンストラクタとデストラクタ
	~CEnemyManager();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	void CreateEnemy(D3DXVECTOR3 pos, EType type);			// プレイヤーの生成

private:		// メンバ変数
	EType m_type;
	CEnemy *m_pEnemy;
};
#endif