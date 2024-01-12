//**************************************************************
//
// キツネのスキル(通常攻撃)
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _FOX_SKILL_H_	// このマクロ定義がされてなかったら
#define _FOX_SKILL_H_	// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// スキルクラス
//==============================================================
class CFoxSkill : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CFoxSkill();
	~CFoxSkill();

	// 静的メンバ関数
	static CFoxSkill* Create(CCharacter* chara);		// スキルの生成

	void InitAbility() override;		// スキルが始まるとき
	void AllWayAbility() override;		// スキル中
	void UninitAbility() override;		// スキル終了時
	void HitAbility(CCharacter* Target) override;	// スキルが当たった時の効果

private:		// メンバ変数

	D3DXVECTOR3 m_effectPos;
	float m_effectRot;
	int m_effectCnt;
};
#endif