//**************************************************************
//
// 敵
// Author : 梶田大夢
//
//**************************************************************
#ifndef _ENEMY_H_			// このマクロ定義がされてなかったら
#define _ENEMY_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "character.h"

//==============================================================
// マクロ宣言
//==============================================================
#define MAX_SPEED	(0.3f)

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;
class CCollisionSphere;

//==============================================================
// 敵クラス
//==============================================================
class CEnemy : public CCharacter
{
public:
	// コンストラクタとデストラクタ
	explicit CEnemy(int nPriority = 3);
	~CEnemy();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	static CEnemy *Create(D3DXVECTOR3 pos);			// プレイヤーの生成
	CCollisionSphere* GetSphere() { return m_collision; }

private:
	void Move();		// 移動

private:	// メンバ変数
	CCollisionSphere* m_collision;
};
#endif