//**************************************************************
//
// 血の祭壇
// Author : 梶田大夢
//
//**************************************************************
#ifndef _STATUE_BLOOD_H_			// このマクロ定義がされてなかったら
#define _STATUE_BLOOD_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "statue.h"

//==============================================================
// マクロ宣言
//==============================================================

//==============================================================
// 前方宣言
//==============================================================
class CPlayer;
class CCollisionBox;
class CCollisionCylinder;

//==============================================================
// 敵クラス
//==============================================================
class CStatueBlood : public CStatue
{
public:
	// コンストラクタとデストラクタ
	explicit CStatueBlood(int nPriority = 3);
	~CStatueBlood();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	static CStatueBlood *Create(D3DXVECTOR3 pos);			// 血の祭壇の生成

private:	// メンバ変数
	CPlayer* m_pPlayer;
	bool m_bOnce;
};
#endif
