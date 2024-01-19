//**************************************************************
//
// テレポーターの祭壇
// Author : 梶田大夢
//
//**************************************************************
#ifndef _STATUE_TELEPORTER_H_			// このマクロ定義がされてなかったら
#define _STATUE_TELEPORTER_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "statue.h"

//==============================================================
// 前方宣言
//==============================================================
class CEnemy;
class CCollisionBox;
class CCollisionCylinder;

//==============================================================
// テレポータークラス
//==============================================================
class CStatueTeleporter : public CStatue
{
public:
	static const int CHARGE_TIME;
public:
	// コンストラクタとデストラクタ
	explicit CStatueTeleporter(int nPriority = 3);
	~CStatueTeleporter();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Update() override;

	bool Select(CCharacter* selectCharacter) override;

	// 静的メンバ関数
	static CStatueTeleporter *Create(D3DXVECTOR3 pos);			// テレポーターの生成

private:	// メンバ変数
	CEnemy* m_pEnemy;
	int m_time;
	bool m_bOnce;
	bool m_btimeAdd;
	bool m_isBossDead;
};
#endif


