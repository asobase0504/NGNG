//**************************************************************
//
// 像管理
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
// 前方宣言
//==============================================================
class CCollisionBox;

//==============================================================
// 敵管理クラス
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
		MAX
	};

	// コンストラクタとデストラクタ
	~CStatueManager();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	CStatue* CreateStatue(D3DXVECTOR3 pos, EType type);			// 像の生成

	CStatue* GetStatue() { return m_pStatue; }
	CCollisionBox* GetStatueBox() { return m_pStatue->GetCollisionBox(); }

private:		// メンバ変数
	CStatue* m_pStatue;
};
#endif

