//**************************************************************
//
// スキル(回転切り)
// Author : 髙野馨將
//
//**************************************************************
#ifndef _YAMATO_SKILL_3_H_			// このマクロ定義がされてなかったら
#define _YAMATO_SKILL_3_H_			// 二重インクルード防止のマクロ定義

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
class CYamatoSkill_3 : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CYamatoSkill_3();
	~CYamatoSkill_3();

	// 静的メンバ関数
	static CYamatoSkill_3	*Create(CCharacter* chara);					// スキルの生成

	void InitAbility() override;					// スキルが始まるとき
	void AllWayAbility() override;					// 持続中
	void HitAbility(CCharacter* Target) override;	// スキルが当たった時の効果
	void UninitAbility() override;					// 終了

private:		// メンバ変数
	int m_time;
};
#endif