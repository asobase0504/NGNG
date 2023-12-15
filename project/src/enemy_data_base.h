//**************************************************************
//
// 敵の行動パターンデータベース
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _ENEMY_DATA_BASE_H_			// このマクロ定義がされてなかったら
#define _ENEMY_DATA_BASE_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// 前方宣言
//==============================================================
class CEnemy;

//==============================================================
// 敵の行動パターンデータベース
//==============================================================
class CEnemyDataBase
{
public:
	using ACTIVITY_FUNC = std::function<void(CEnemy*)>;

	enum EActivityPattern
	{
		PATTERN_STANDBY,
		PATTERN_AIR_GO,
		PATTERN_AIR_KEEP_DISTANCE,
		PATTERN_GROUND_GO,
		PATTERN_GROUND_KEEP_DISTANCE,
		PATTERN_GROUND_GO_ATTACK,
		PATTERN_GOLEM,
		PATTERN_GOLEM_LASER,
		MAX_PATTERN
	};

	enum EEnemyType
	{
		SKELTON,
		MAX_TYPE
	};

private:
	explicit CEnemyDataBase();
	static CEnemyDataBase* m_instance;
	void Init();
public:
	static CEnemyDataBase* GetInstance();
	~CEnemyDataBase();

	static void Uninit();
public:
	ACTIVITY_FUNC GetActivityFunc(EActivityPattern inState) { return m_activityFunc[inState]; }
private:
	
private:	// メンバ変数
	std::vector<ACTIVITY_FUNC> m_activityFunc;

};
#endif