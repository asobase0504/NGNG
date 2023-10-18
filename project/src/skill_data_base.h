//**************************************************************
//
// スキルデータベース
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _SKILL_DATA_BASE_H_			// このマクロ定義がされてなかったら
#define _SKILL_DATA_BASE_H_			// 二重インクルード防止のマクロ定義

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
		int CT;
		int stock;
	};

	struct SKILL_INFO
	{
		BASE baseInfo;
		ABILITY ability;
		ABILITY abilityHit;
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
	SKILL_INFO GetInfo(std::string tag) { return m_dates[tag]; }
	ABILITY GetAbility(std::string tag) { return m_dates[tag].ability; }
	ABILITY GetHitAbility(std::string tag) { return m_dates[tag].abilityHit; }
	int GetCT(std::string tag) { return m_dates[tag].baseInfo.CT; }
	int GetStack(std::string tag) { return m_dates[tag].baseInfo.stock; }

private:	// メンバ変数

	std::unordered_map<std::string, SKILL_INFO> m_dates;
};
#endif