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
private:
	explicit CEnemyDataBase();
	static CEnemyDataBase* m_instance;
	void Init();
public:
	CEnemyDataBase* GetInstance();
	~CEnemyDataBase();

	static void Uninit();
public:
	ACTIVITY_FUNC GetActivityFunc(std::string inState) { return m_activityFunc[inState]; }
private:
	
private:	// メンバ変数
	static std::unordered_map<std::string,ACTIVITY_FUNC> m_activityFunc;
};
#endif