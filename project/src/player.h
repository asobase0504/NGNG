//**************************************************************
//
// プレイヤー
// Author : 髙野馨將
//
//**************************************************************
#ifndef _PLAYER_H_			// このマクロ定義がされてなかったら
#define _PLAYER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "character.h"

#include "collision_cylinder.h"

//==============================================================
// マクロ宣言
//==============================================================
#define DASH_SPEED	(3.0f)

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;
class CCollisionCyinder;

//==============================================================
// プレイヤークラス
//==============================================================
class CPlayer : public CCharacter
{
public:
	// コンストラクタとデストラクタ
	explicit CPlayer(int nPriority = 3);
	~CPlayer();
	
	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;

	// 静的メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos);			// プレイヤーの生成

	// Setter
	void SetController(CController* inOperate);
	CCollisionCyinder* GetCylinder() { return m_collisionCyinder; }

	void SetPos(const D3DXVECTOR3& inPos);

private:
	void Move();	// 移動
	void Jump();	// ジャンプ
	void Dash();	// ダッシュ

private:		// メンバ変数
	bool			m_isjump;		// ジャンプしているかどうか
	bool			m_isdash;		// ダッシュしているかどうか

	CController*	m_controller;	// 命令を出す人
	CCollisionCyinder* m_collisionCyinder;
};
#endif