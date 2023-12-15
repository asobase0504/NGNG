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
// 前方宣言
//==============================================================
class CProcedure3D;

//==============================================================
// 敵クラス
//==============================================================
class CStatueBlood : public CStatue
{
public:
	// コンストラクタとデストラクタ
	explicit CStatueBlood();
	~CStatueBlood();

	//プロトタイプ宣言
	HRESULT	Init() override;

	bool Select(CCharacter* selectCharacter) override;

	// 静的メンバ関数
	static CStatueBlood *Create(D3DXVECTOR3 pos);			// 血の祭壇の生成

	void SetPos(const D3DXVECTOR3& inPos) override;

private:	// メンバ変数
	float m_hpSubRate;	// HPを削る割合

};
#endif
