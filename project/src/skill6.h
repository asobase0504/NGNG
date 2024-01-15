//**************************************************************
//
// スキル(カウンター)
// Author : 髙野馨將
//
//**************************************************************
#ifndef _SKILL6_H_			// このマクロ定義がされてなかったら
#define _SKILL6_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// 前方宣言
//==============================================================
class CCharacter;
class CCollision;

//==============================================================
// スキルクラス
//==============================================================
class CSkill6 : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CSkill6(int nPriority = 3);
	~CSkill6();

	// 静的メンバ関数
	static CSkill6	*Create(CCharacter* chara);					// スキルの生成

	void InitAbility() override;										// スキルが始まるとき
	void AllWayAbility() override;										// 持続中
	void UninitAbility() override;										// 終了
	void HitAbility(CCharacter* Target) override;						// スキルが当たった時の効果

private:		// メンバ変数	
};
#endif