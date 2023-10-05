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
#include "object.h"

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;

//==============================================================
// プレイヤークラス
//==============================================================
class CPlayer : public CObject
{
public:
	// コンストラクタとデストラクタ
	explicit CPlayer(int nPriority = 3);
	~CPlayer();
	
	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// プレイヤーの生成

	// Setter
	void SetController(CController* inOperate);

private:
	void Move();				// 移動
	void Updatepos();			// 座標の更新

private:		// メンバ変数
	D3DXVECTOR3		m_pos;			// 位置
	D3DXVECTOR3		m_posold;		// 前回の位置

	D3DXVECTOR3		m_rot;			// 角度
	D3DXVECTOR3		m_rotDest;		// 目的の角度の保存

	D3DXVECTOR3		m_move;			// 移動量

	D3DXMATRIX		m_mtxWorld;					// ワールドマトリックス
	CController*	m_controller;				// 命令を出す人
	std::vector<CObjectX*>		m_apModel;		// モデルのインスタンス
};
#endif