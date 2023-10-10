//**************************************************************
//
// キャラクター
// Author : 梶田大夢
//
//**************************************************************
#ifndef _CHARACTER_H_			// このマクロ定義がされてなかったら
#define _CHARACTER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "object.h"

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;

//==============================================================
// プレイヤークラス
//==============================================================
class CCharacter : public CObject
{
public:
	// コンストラクタとデストラクタ
	explicit CCharacter(int nPriority = 3);
	~CCharacter();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	static CCharacter *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// プレイヤーの生成

private:		// メンバ変数
	std::vector<CObjectX*>		m_apModel;		// モデルのインスタンス
	D3DXMATRIX		m_mtxWorld;					// ワールドマトリックス
};
#endif
