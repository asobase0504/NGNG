//**************************************************************
//
// 敵
// Author : 梶田大夢
//
//**************************************************************
#ifndef _ENEMY_H_			// このマクロ定義がされてなかったら
#define _ENEMY_H_			// 二重インクルード防止のマクロ定義

//==============================================================
// include
//==============================================================
#include "character.h"
#include "enemy_data_base.h"

//==============================================================
// マクロ宣言
//==============================================================
#define MAX_SPEED	(0.3f)

//==============================================================
// 前方宣言
//==============================================================
class CObjectX;
class CController;
class CCollisionBox;
class CCollisionSphere;
class CEnemyDataBase;
class CEnemy_HPUI;

//==============================================================
// 敵クラス
//==============================================================
class CEnemy : public CCharacter
{
public:

	// AI状態
	enum EAIState
	{
		WANDER,		// 彷徨う
		STAY,		// 待機
		COMBAT		// 戦闘状態
	};

	using ACTIVITY_FUNC = std::function<void(CEnemy*)>;
public:
	// コンストラクタとデストラクタ
	explicit CEnemy();
	~CEnemy();

	//プロトタイプ宣言
	HRESULT	Init() override;
	void	Update() override;

	// 攻撃カウントの加算
	void SetAttackCnt(int Cnt) { m_AttackCnt = Cnt; }
	void AddAttackCnt(int Cnt) { m_AttackCnt += Cnt; }
	int GetAttackCnt() { return m_AttackCnt; }

	// 死亡時の処理
	void Died() override;

private:
	virtual void Move() {};		// 移動

private:	// メンバ変数
	int				m_AttackCnt;
	CEnemy_HPUI*	m_pEHPUI;
	int				m_dropMoney;

	int m_diedCount;
};
#endif