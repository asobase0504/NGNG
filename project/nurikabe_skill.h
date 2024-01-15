//**************************************************************
//
// ぬりかべ
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _NURIKABE_SKILL_H_			// このマクロ定義がされてなかったら
#define _NURIKABE_SKILL_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// 前方宣言
//==============================================================
class CCharacter;

//==============================================================
// スキルクラス
//==============================================================
class CNurikabeSkill : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CNurikabeSkill();
	~CNurikabeSkill();

	// 静的メンバ関数
	static CNurikabeSkill* Create(CCharacter* chara);		// スキルの生成

	void InitAbility() override;					// スキルが始まるとき
	void AllWayAbility() override;					// スキル中
	void UninitAbility() override;					// スキル終了時
	void HitAbility(CCharacter* Target) override;	// スキルが当たった時の効果

private:	// メンバ変数
	int m_time;
	CCharacter* m_aimCharacter;	// 狙う相手
};
#endif