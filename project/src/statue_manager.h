//**************************************************************
//
// 像生成管理
// Author : 梶田大夢
//
//**************************************************************
#ifndef _STATUE_MANAGER_H_			// このマクロ定義がされてなかったら
#define _STATUE_MANAGER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "task.h"
#include "statue.h"

//==============================================================
// 像生成クラス
//==============================================================
class CStatueManager : public CTask
{
public:	// シングルトン用のインスタンス
	static CStatueManager* GetInstance();
private:
	CStatueManager();
	static CStatueManager* m_statueManager;

public:
	enum EType
	{
		NONE = 0,
		BLOOD,
		CHEST,
		LUCK,
		COMBAT,
		TELEPORTER,
		MAX
	};

	// コンストラクタとデストラクタ
	~CStatueManager();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;

	// 生成プロセス
	CStatue* CreateStatue(D3DXVECTOR3 pos,int type);	// 像の生成
	CStatue* CreateStatue(int type);					// 像の生成
	CStatue* RandomCreate();			// ランダムな像生成
	CStatue* RandomCreateChest();		// 宝箱ランダム生成

private:		// メンバ変数
};
#endif

