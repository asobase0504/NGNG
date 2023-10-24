//**************************************************************
//
// 運の祭壇
// Author : 梶田大夢
//
//**************************************************************
#ifndef _STATUE_LUCK_H_			// このマクロ定義がされてなかったら
#define _STATUE_LUCK_H_			// 二重インクルード防止のマクロ定義

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
class CStatueLuck : public CStatue
{
public:
	// コンストラクタとデストラクタ
	explicit CStatueLuck(int nPriority = 3);
	~CStatueLuck();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Uninit() override;
	void	Update() override;
	void	Draw() override;

	// 静的メンバ関数
	static CStatueLuck *Create(D3DXVECTOR3 pos);			// 血の祭壇の生成

private:	// メンバ変数
	CPlayer* m_pPlayer;
	int m_nUseMoney;		// 初期必要お金数
	int m_nItemCount;		// アイテム数
	bool m_bChance;			// 成功確率
	bool m_bOnce;			// 一回処理用
};
#endif

