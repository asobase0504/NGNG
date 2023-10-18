//**************************************************************
//
// スキルデータベース
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKILL_DATA_BASE_H_			// このマクロ定義がされてなかったら
#define _SKILL_DATA_BASE_H_			// 二重インクルード防止のマクロ定義

#include <unordered_map>

//--------------------------------------------------------------
// 前方宣言
//--------------------------------------------------------------
class CCharacter;

//==============================================================
// 敵の行動パターンデータベース
//==============================================================
class CSkillDataBase
{
public:
	using ABILITY = std::function<void(CCharacter*)>;

	struct BASE
	{
		int		CT;				// クールタイム
		int		stock;			// ストック
		int		duration;		// 効果時間
		float	damage;			// ダメージ量
		float	KnockBack;		// ノックバック量
	};

	struct SKILL_INFO
	{
		BASE baseInfo;
		ABILITY ability;
		ABILITY abilityHit;
	};

	enum SKILL_TYPE
	{
		YAMATO_ATTACK
	};

private:
	// コンストラクタとデストラクタ
	explicit CSkillDataBase();
	static CSkillDataBase* m_instance;
public:
	static CSkillDataBase* GetInstance();
	~CSkillDataBase();
	static void Uninit();
private:
	void Init();
public:
	SKILL_INFO GetInfo(std::string tag) { return m_skillDataBase[tag]; }
	ABILITY GetAbility(std::string tag) { return m_skillDataBase[tag].ability; }
	ABILITY GetHitAbility(std::string tag) { return m_skillDataBase[tag].abilityHit; }
	int GetCT(std::string tag) { return m_skillDataBase[tag].baseInfo.CT; }
	int GetStock(std::string tag) { return m_skillDataBase[tag].baseInfo.stock; }
	int GetDuration(std::string tag) { return m_skillDataBase[tag].baseInfo.duration; }
	float GetDamage(std::string tag) { return m_skillDataBase[tag].baseInfo.damage; }
	float GetKnockBack(std::string tag) { return m_skillDataBase[tag].baseInfo.KnockBack; }

private:	// メンバ変数
	std::unordered_map<std::string, SKILL_INFO> m_skillDataBase;
};
#endif