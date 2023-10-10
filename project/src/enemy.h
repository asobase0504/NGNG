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
// 前方宣言
//==============================================================
class CObjectX;
class CController;

//==============================================================
// プレイヤークラス
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
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// プレイヤーの生成

private:
	void Updatepos();			// 座標の更新

private:		// メンバ変数
	D3DXVECTOR3		m_posold;		// 前回の位置
	D3DXVECTOR3		m_move;			// 移動量
};
#endif