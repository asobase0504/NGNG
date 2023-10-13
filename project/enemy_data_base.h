//**************************************************************
//
// 敵の行動パターンデータベース
// Author : Yuda Kaito
//
//**************************************************************
#ifndef _ENEMY_DATA_BASE_H_			// このマクロ定義がされてなかったら
#define _ENEMY_DATA_BASE_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// 敵の行動パターンデータベース
//==============================================================
class CEnemyDataBase
{
public:
	enum ACTIVITY_STATE
	{
		ACTIVITY_IDLE = 0,
		ACTIVITY_MAX
	};

	using ACTIVITY_FUNC = void(CEnemyDataBase::*)();

public:
	// コンストラクタとデストラクタ
	explicit CEnemyDataBase();
	~CEnemyDataBase();

	ACTIVITY_FUNC GetActivityFunc(ACTIVITY_STATE inState) { return m_activityFunc[inState]; }
private:
	//　スキルのステート関数
	void Activity_Idel();

private:	// メンバ変数
	static const ACTIVITY_FUNC m_activityFunc[];
};
#endif