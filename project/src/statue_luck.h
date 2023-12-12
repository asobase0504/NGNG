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
class CProcedure3D;

//==============================================================
// 敵クラス
//==============================================================
class CStatueLuck : public CStatue
{
public:
	// コンストラクタとデストラクタ
	explicit CStatueLuck();
	~CStatueLuck();

	//プロトタイプ宣言
	HRESULT	Init() override;

	bool Select(CCharacter* selectCharacter) override;

	// 静的メンバ関数
	static CStatueLuck *Create(D3DXVECTOR3 pos);	// 運の祭壇の生成

	void SetPos(const D3DXVECTOR3& inPos) override;

private:	// メンバ変数
	int m_nUseMoney;		// 初期必要お金数
	int m_nItemCount;		// アイテム数
	CProcedure3D* m_useMoneyUI;	// 必要金額を3D空間状に描画
};
#endif

