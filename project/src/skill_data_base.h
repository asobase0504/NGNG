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
class CCollision;

//==============================================================
// 敵の行動パターンデータベース
//==============================================================
class CSkillDataBase
{
public:
	using HIT_ABILITY = std::function<bool(CCharacter*, CCharacter*)>;
	using ABILITY = std::function<bool(CCharacter*)>;

	struct BASE
	{
		int				CT;				// クールタイム
		int				stock;			// ストック数
		float			damage;			// ダメージ量
		float			knockback;		// ノックバック量
		float			duration;		// 持続時間
		float			interval;		// 多段ヒットの場合次の当たり判定を出現させるまでの時間
		D3DXVECTOR3		size;			// 当たり判定の大きさ
	};

	struct SKILL_INFO
	{
		BASE baseInfo;
		ABILITY ability;
		HIT_ABILITY abilityHit;
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
	SKILL_INFO	GetInfo(std::string tag) { return m_dates[tag]; }
	ABILITY		GetAbility(std::string tag) { return m_dates[tag].ability; }
	HIT_ABILITY	GetHitAbility(std::string tag) { return m_dates[tag].abilityHit; }
	int			GetCT(std::string tag) { return m_dates[tag].baseInfo.CT; }
	int			GetStack(std::string tag) { return m_dates[tag].baseInfo.stock; }
	float		GetDamage(std::string tag) { return m_dates[tag].baseInfo.damage; }
	float		GetKnockBack(std::string tag) { return m_dates[tag].baseInfo.knockback; }
	float		GetDuration(std::string tag) { return m_dates[tag].baseInfo.duration; }
	float		GetInterval(std::string tag) { return m_dates[tag].baseInfo.interval; }
	D3DXVECTOR3 GetSize(std::string tag) { return m_dates[tag].baseInfo.size; }

private:	// メンバ変数
	CCollision *m_Collision;
	std::unordered_map<std::string, SKILL_INFO> m_dates;
};
#endif