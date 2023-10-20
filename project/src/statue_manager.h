//**************************************************************
//
// ^像管理
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
class CObjectX;
class CCollisionBox;

//==============================================================
// 像管理クラス
//==============================================================
class CStatueManager : public CTask
{
public:	// シングルトン用のインスタンス
	static CStatueManager* GetInstance();
private:
	CStatueManager();
	static CStatueManager* m_statueManager;

public:
	// コンストラクタとデストラクタ
	~CStatueManager();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	CStatue* CreateStatue(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 像の生成

	// ゲッター
	CStatue* GetPlayer() { return m_pStatue; }
	const D3DXVECTOR3& GetPlayerPos() { return m_pStatue->GetPos(); }
	CCollisionBox* GetStatueBox() { return m_pStatue->GetCollisionBox(); }

private:		// メンバ変数
	CStatue *m_pStatue;
};
#endif

