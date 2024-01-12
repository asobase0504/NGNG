//**************************************************************
//
// スキル(マーセナリーのR)
// Author : 髙野馨將
//
//**************************************************************
#ifndef _YAMATO_SKILL_4_H_			// このマクロ定義がされてなかったら
#define _YAMATO_SKILL_4_H_			// 二重インクルード防止のマクロ定義

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
class CYamatoSkill_4 : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CYamatoSkill_4();
	~CYamatoSkill_4();

	// 静的メンバ関数
	static CYamatoSkill_4	*Create(CCharacter* chara);					// スキルの生成

	void InitAbility() override;					// スキルが始まるとき
	void AllWayAbility() override;					// 持続中
	void UninitAbility() override;					// 終了
	void HitAbility(CCharacter* Target) override;	// スキルが当たった時の効果

private:	// メンバ変数
	int m_Time;		// 時間
};
#endif