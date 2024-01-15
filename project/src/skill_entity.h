//**************************************************************
//
// スキル
// Author : 髙野馨將
//
//**************************************************************
#ifndef _SKILL_ENTITY_H_			// このマクロ定義がされてなかったら
#define _SKILL_ENTITY_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "task.h"
#include "character.h"

//==============================================================
// 前方宣言
//==============================================================
class CCharacter;
class CCollision;

//==============================================================
// スキルクラス
//==============================================================
class CSkillEntity : public CTask
{
public:
	// コンストラクタとデストラクタ
	explicit CSkillEntity(int nPriority = 3);
	~CSkillEntity();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Update() override;

	// 静的メンバ関数
	virtual void InitAbility() = 0;						// スキルが始まるとき
	virtual void AllWayAbility() {}						// 持続中
	virtual void UninitAbility() {}						// 終了
	virtual void HitAbility(CCharacter* Target) {};		// スキルが当たった時の効果

protected:	// プライベート関数
	void Collision();
protected:	// メンバ変数
	CCharacter* m_apChara;			// キャラクターのインスタンス
	CCharacter::ERelation m_relation;
	std::list<CCollision*> m_collision;		// 当たり判定

	std::string m_Name;		// スキル名
	int m_Duration;			// 効果時間
	int m_maxDuration;		// 持続する時間の保管
	int m_Interval;			// 多段ヒットの場合次の当たり判定を出現させるまでの時間
	bool m_isSkill;			// スキル発動中かどうか

	bool m_isHitClear;		// 衝突時当たり判定を消すか否か
};
#endif