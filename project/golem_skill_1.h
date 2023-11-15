//**************************************************************
//
// スキル
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _GOLEM_SKILL_1_H_		// このマクロ定義がされてなかったら
#define _GOLEM_SKILL_1_H_		// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "skill_entity.h"

//==============================================================
// 前方宣言
//==============================================================
class CObjectPolygon3D;
class CRoad;
class CBullet;
class CCollision;

//==============================================================
// スキルクラス
//==============================================================
class CGolemSkill_1 : public CSkillEntity
{
public:
	// コンストラクタとデストラクタ
	explicit CGolemSkill_1();
	~CGolemSkill_1();

	void Uninit();

	// 静的メンバ関数
	static CGolemSkill_1 *Create(CCharacter* chara);	// スキルの生成

	// スキル
	void InitAbility() override;					// 始まるとき
	void AllWayAbility() override;					// 持続中
	void HitAbility(CCharacter* Target) override;	// 当たった時の効果

private:		// メンバ変数
	CRoad* m_road;

	CBullet* m_bullet;
	CObjectPolygon3D* m_bulletDesign;

	CCharacter* m_aimCharacter;

	bool m_isCharge;
	int m_chargeTime;
};
#endif