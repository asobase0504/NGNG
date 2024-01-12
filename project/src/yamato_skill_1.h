//**************************************************************
//
// スキル(通常攻撃)
// Author : 髙野馨將
//
//**************************************************************
#ifndef _YAMATO_SKILL_1_H_			// このマクロ定義がされてなかったら
#define _YAMATO_SKILL_1_H_			// 二重インクルード防止のマクロ定義

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
class CYamatoSkill_1 : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CYamatoSkill_1();
	~CYamatoSkill_1();

	// 静的メンバ関数
	static CYamatoSkill_1* Create(CCharacter* chara);		// スキルの生成

	void InitAbility() override;					// スキルが始まるとき
	void AllWayAbility() override;				// スキル中
	void UninitAbility() override;				// スキル中
	void HitAbility(CCharacter* Target) override;	// スキルが当たった時の効果

private:		// メンバ変数

	D3DXVECTOR3 m_effectPos;
	float m_effectRot;
	int m_effectCnt;
};
#endif