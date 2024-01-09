//**************************************************************
//
// スキル(通常攻撃)
// Author : 髙野馨將
//
//**************************************************************
#ifndef _GASYADOKURO_SUMMON_SKILL_H_			// このマクロ定義がされてなかったら
#define _GASYADOKURO_SUMMON_SKILL_H_			// 二重インクルード防止のマクロ定義

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
class CGasyadokuroSummonSkill : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CGasyadokuroSummonSkill();
	~CGasyadokuroSummonSkill();

	// 静的メンバ関数
	static CGasyadokuroSummonSkill* Create(CCharacter* chara);		// スキルの生成

	void InitAbility() override;					// スキルが始まるとき
	void AllWayAbility() override;					// スキル中

private:		// メンバ変数

	D3DXVECTOR3 m_effectPos;
	float m_effectRot;
	int m_effectCnt;
};
#endif