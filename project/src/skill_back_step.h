//**************************************************************
//
// バックステップ
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKILL_BACK_STEP_H_			// このマクロ定義がされてなかったら
#define _SKILL_BACK_STEP_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// スキルクラス
//==============================================================
class CSkillBackStep : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CSkillBackStep();
	~CSkillBackStep();

	// 静的メンバ関数
	static CSkillBackStep* Create(CCharacter* chara);		// スキルの生成

	void InitAbility() override;					// スキルが始まるとき
	void AllWayAbility() override;					// スキル中
	void UninitAbility() override;					// スキル終了時
	void HitAbility(CCharacter* Target) override;	// スキルが当たった時の効果

private:	// メンバ変数
	int m_time;
};
#endif