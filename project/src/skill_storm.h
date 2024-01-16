//**************************************************************
//
// ストーム
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKILL_STORM_H_			// このマクロ定義がされてなかったら
#define _SKILL_STORM_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// 前方宣言
//==============================================================
class CObjectPolygon3D;

//==============================================================
// スキルクラス
//==============================================================
class CSkillStorm : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CSkillStorm();
	~CSkillStorm();

	// 静的メンバ関数
	static CSkillStorm* Create(CCharacter* chara);		// スキルの生成

	void InitAbility() override;					// スキルが始まるとき
	void AllWayAbility() override;					// スキル中
	void UninitAbility() override;					// スキル終了時
	void HitAbility(CCharacter* Target) override;	// スキルが当たった時の効果

private:	// メンバ変数
	int m_timer;
	CObject* m_bullet;
	CObjectPolygon3D* m_effectBG;
};
#endif