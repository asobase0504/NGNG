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
	void	Uninit() override;
	void	Update() override;

	// 静的メンバ関数
	virtual void InitAbility() = 0;							// スキルが始まるとき
	virtual void AllWayAbility() {}							// 持続中
	virtual void HitAbility(CCharacter* Target) = 0;		// スキルが当たった時の効果

protected:		// メンバ変数
	CCharacter*		m_apChara;			// キャラクターのインスタンス
	CCharacter::ERelation m_relation;
	CCollision*		m_Collision;		// 当たり判定

	std::string		m_Name;				// スキル名
	float			m_Duration;			// 効果時間
};
#endif